#ifndef __load_app_h
#define __load_app_h

#include <process.h>
#include <architecture.h>
#include <machine.h>
#include <utility/elf.h>

__BEGIN_UTIL

int load_app(int off_set, unsigned int addr) {
    typedef CPU::Log_Addr Log_Addr;
    db<Task>(ERR) << "********Load_app::off_set(" << off_set << ") ,addr(" << addr << ")********" << endl;
    unsigned int tamanho = *(reinterpret_cast<int*> (addr + off_set));
    db<Task>(ERR) << "Tamanho arquivo: " << tamanho << endl;

    ELF * app_elf = reinterpret_cast<ELF *>(addr + off_set + 4);

    unsigned int entry = 0;
    unsigned int app_code = ~0U;
    unsigned int app_code_size = 0;
    unsigned int app_data = ~0U;
    unsigned int app_data_size = 0;

    if(!app_elf->valid()) {
        db<Task>(TRC) << "APP ELF image is corrupted!" << endl;
    } else {
        db<Task>(TRC) << "We good" << endl;
    }

    entry = app_elf->entry();
    app_code = app_elf->segment_address(0);
    if(app_code != MMU::align_directory(app_code)) {
        Machine::panic();
    }

    db<Task>(TRC) << "app code :" << hex << app_code << endl;

    app_code_size = app_elf->segment_size(0);

    // if this has data segment
    if(app_elf->segments() > 1) {
        for(int i = 1; i < app_elf->segments(); i++) {
            if(app_elf->segment_type(i) != PT_LOAD)
                continue;
            // if(app_elf->segment_address(i) < app_data)
            if(app_data == ~0U)
                app_data = app_elf->segment_address(i);
            app_data_size += app_elf->segment_size(i);
        }
    }

    db<Task>(TRC) << "LINE 52 - app_data_size :" << hex << app_data_size << endl;

    // TODO @cross this might be very wrong because app_data never changes
    if(app_data == ~0U) {
        db<Setup>(WRN) << "APP ELF image has no data segment!" << endl;
        app_data = MMU::align_page(Memory_Map::APP_DATA); 
        // app_data += MMU::align_page(Traits<Application>::HEAP_SIZE);
    }
    if(Traits<System>::multiheap) { // Application heap in data segment
        app_data_size = MMU::align_page(app_data_size);
        app_data_size += MMU::align_page(Traits<Application>::STACK_SIZE);
        app_data_size += MMU::align_page(Traits<Application>::HEAP_SIZE);
    }


    typedef int (Main)(); // TODO @cross se pah ta faltando o argc e argv aqui
    // typedef int (Main)(argc, argv); // TODO @cross se pah ta faltando o argc e argv aqui
    Main * main = reinterpret_cast<Main *>(entry);

    // argc = ...;
    // argv = ...;


    // Address_Space* as = new (SYSTEM) Address_Space(MMU::current());
    //Segment* cs = new (SYSTEM) Segment(Log_Addr(app_code), app_code_size, Segment::Flags::APP);
    Segment* cs = new (SYSTEM) Segment(app_code_size, Segment::Flags::APP);
    //Segment* ds = new (SYSTEM) Segment(Log_Addr(app_data), app_data_size, Segment::Flags::APP);
    Segment* ds = new (SYSTEM) Segment(app_data_size, Segment::Flags::APP);

    // cout << "Attaching data segment..." << endl;
    CPU::int_disable();
    Log_Addr code = Task::self()->address_space()->attach(cs); // o prox endereço eh 0x8020
    Log_Addr data = Task::self()->address_space()->attach(ds); // 0 1 --> 2 3
    Log_Addr aux_data = data;
    CPU::int_enable();
    
    // aqui eh hora de copiar entao tem que ser igual da task que ta rodando
    //      mas dps a gente quer nos outros lugarex 0x8000 e 0x8040

    // app_code = app_elf->segment_address(0);

    if(app_elf->load_segment(0, code) < 0) { // 0x8020
        db<Setup>(ERR) << "Application code segment was corrupted during SETUP!" << endl;
        Machine::panic();
    }
    for(int i = 1; i < app_elf->segments(); i++) {
        if(app_elf->load_segment(i, data) < 0) {
            db<Setup>(ERR) << "Application data segment was corrupted during SETUP!" << endl;
            Machine::panic();
        }
        data += app_elf->segment_size(i);
    }

    Task::self()->address_space()->detach(cs, code);
    Task::self()->address_space()->detach(ds, aux_data);

    db<Task>(TRC) << "app_code_size :" << hex << app_code_size << endl;
    db<Task>(TRC) << "app_data_size :" << hex << app_data_size << endl;
    db<Task>(TRC) << "HEAP_SIZE :" << hex << Traits<Application>::HEAP_SIZE << endl;

    new (SYSTEM) Task(cs, ds, main, app_code, app_data);


    db<Task>(ERR) << "************End::Load_app:************" << endl;
    return (*reinterpret_cast<int*> (addr + off_set + tamanho + 4));

    /*
        app_loader <-- argc argv que sao os elf tudo.
            |
            |-- app 1 (pode ter argc argv ou nao)
            |
            |-- app 2 ()

            // extra_segment
     */

}
__END_UTIL

#endif
