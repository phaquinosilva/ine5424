// Fork Test

#include <memory.h>
#include <process.h>

using namespace EPOS;
OStream cout;

const unsigned CODE_SIZE = 10000;
const unsigned DATA_SIZE = 100000;


int print_mmu_translation()
{
    cout << "Printing Task MMU Information:" << endl;

    Task * this_task = Task::self();

    cout << "Printing Code MMU Information:" << endl;
    CPU::Log_Addr current_task_code_init = this_task->code();
    cout << MMU::Translation(current_task_code_init) << endl;

    cout << "Printing Data MMU Information:" << endl;
    CPU::Log_Addr current_task_data_init = this_task->data();
    cout << MMU::Translation(current_task_data_init) << endl;
    // Address_Space * as = new (SYSTEM) Address_Space(MMU::current());
    // ?

    // Eh por isso que tu precisa da referencia pra task principal la em cima
    // Ta, mas aqui a gente vai ter as duas parada rodando, e eu nao sei
    // se ambas vao printar no mesmo terminal.
    // current_task->resume();

    // @cross isso funciona?
    // Task::self()->suspend();

    return 0;
}

int main()
{    

    cout << "Fork test" << endl;

    cout << "My address space's page directory is located at "
         << reinterpret_cast<void *>(CPU::pdp()) << "" << endl;
    Address_Space self(MMU::current());

    // cout << "Creating code and data segments for the first task:" << endl;
    // Segment * code_segment;
    // Segment * data_segment;

    // cout << "Creating code and data segments for the second task (which will be overwritten)..." << endl;
    
    // // // @cross nao sei se ta certo inicializar isso e depois sobreescrever
    // // //          eu tentei nao inicializar, mas ai ele reclamava tambem.
    // Segment * code_segment_2;
    // Segment * data_segment_2;

    //@cross: checar a ordem de enable e disable

    Task * current_task = Task::self();
    cout << "Attaching code segment..." << endl;
    unsigned int cs_size = current_task->code_segment()->size();
    Segment * code_segment = new (SYSTEM) Segment(cs_size, Segment::Flags::SYS);
    CPU::int_disable();
    CPU::Log_Addr tmp_code = current_task->address_space()->attach(cs);
    memcpy(tmp_code, current_task->code(), cs_size);
    current_task->address_space()->detach(code_segment);
    CPU::int_enable();

    cout << "Attaching data segment..." << endl;
    unsigned int ds_size = current_task->data_segment()->size();
    Segment * data_segment = new (SYSTEM) Segment(ds_size, Segment::Flags::SYS);
    CPU::int_disable();
    CPU::Log_Addr tmp_data = current_task->address_space()->attach(ds);
    memcpy(tmp_data, current_task->data(), ds_size);
    current_task->address_space()->detach(data_segment);
    CPU::int_enable();

    cout << "EL GRANDE BOLOVO" << endl << endl;
    cout << "EL GRANDE BOLOVO" << endl << endl;

    print_mmu_translation();
    
    new (SYSTEM) Task(code_segment, data_segment, &print_mmu_translation);
    // Task * new_task = new (SYSTEM) Task(code_segment_2, data_segment_2, &print_mmu_translation);

    Thread::self()->yield();

    cout << "I'm done, bye!" << endl;

    return 0;
}
