#include <utility/ostream.h>

#include<utility/elf.h>

#include <syscall/stub_loader.h>
#include <syscall/stub_thread.h>
#include <utility/load_app.h>

#include <syscall/stub_segment.h>

using namespace EPOS;

OStream cout;

int main(int argc, char** argv)
{
    cout << "Loader!" << endl;    

    cout << "Argc: " << argc << endl;
    cout << "Argv: " << argv << " / " << reinterpret_cast<unsigned int> (argv) << endl;

    Stub_Loader * sld = new Stub_Loader();
    cout << "Carregando aplicações:" << endl;

    int tam_proximo_app = 0;
    int tam_app = 0;
    int off_set = 0;
    int i = 1;
    unsigned int addr = reinterpret_cast<unsigned int> (argv);

    if (argc)
    do {
        tam_app = *(reinterpret_cast<int*> (addr + off_set));
        sld -> new_app(off_set, addr);
        /*ELF * app_elf = reinterpret_cast<ELF *>(addr + off_set + 4);
        if(!app_elf->valid()) {
            cout << "APP ELF image is corrupted!" << endl;
        } else {
            cout << "We good" << endl;
        }
            //Load segments
        if(app_elf->load_segment(0) < 0) {
            cout << "Application code segment was corrupted during SETUP!" << endl;
        }
            cout << "We load_segment0" << endl;
        
        for(int i = 1; i < app_elf->segments(); i) {
            if(app_elf->load_segment(i) < 0) {
                cout << "Application data segment was corrupted during SETUP!" << endl;
            }
        }
            cout << "We load_segment1" << endl;

        unsigned int app_entry = 0;
        unsigned int app_code = ~0U;
        unsigned int app_data = ~0U;;
        unsigned int app_code_size = 0;
        unsigned int app_data_size = 0;

        app_entry = app_elf->entry();
        app_code = app_elf->segment_address(0);

        app_code_size = app_elf->segment_size(0);
        for(int i = 1; i < app_elf->segments(); i) {
            if(app_elf->segment_type(i) != 1)
                continue;
            if(app_elf->segment_address(i) < app_data)
                app_data = app_elf->segment_address(i);

            app_data_size = app_elf->segment_size(i);
        }        

        //typedef int (Main)(int, int);
        typedef int (Main)();
        typedef _SYS::CPU::Log_Addr Log_Addr;
        cout << "Criando Task..." << endl;

        Main * main = reinterpret_cast<Main *>(app_entry);
        Stub_Segment* cs = new Stub_Segment(Log_Addr(app_code), app_code_size); //Segment::Flags::APPC);
        Stub_Segment* ds = new Stub_Segment(Log_Addr(app_data), app_data_size); //Segment::Flags::APPC);
        Log_Addr code = app_code;
        Log_Addr data = app_data;

        */
        /*Task * t = Task::self();
        Main * main = reinterpret_cast<Main *>(app_entry);
        Address_Space* as = new (SYSTEM) Address_Space();
        Segment* cs = new (SYSTEM) Segment(app_code_size, Segment::Flags::APP);
        Segment* ds = new (SYSTEM) Segment(app_data_size, Segment::Flags::APP);
        Log_Addr code = t -> address_space() -> attach(cs);
        Log_Addr data = t -> address_space() -> attach(ds);
        memcpy(code, reinterpret_cast<void*> (app_code), app_code_size);
        memcpy(data, reinterpret_cast<void*> (app_data), app_data_size);
        t -> address_space() -> detach(ds);
        t -> address_space() -> detach(ds);
        code = as -> attach(cs, code);
        data = as -> attach(ds, data);*/
        
        /*
        cout << "Criando Task...1" << endl;
        new Stub_Task(cs, ds, main, code, data);
        */

        
        tam_proximo_app = *(reinterpret_cast<int*> (addr + off_set + tam_app + 4));
        off_set = tam_app + 4;


        cout << "Aplicação[" << i << "](" << tam_app << ") caregada, proxima tem tamanho:" << tam_proximo_app << endl;
        i++;
    } while (tam_proximo_app);

    cout << "Fim Loader!" << endl;
    return 0;
}
