// Fork Test

#include <memory.h>
#include <process.h>

using namespace EPOS;
OStream cout;

const unsigned CODE_SIZE = 20000;
const unsigned DATA_SIZE = 200000;


int print_mmu_translation()
{
    cout << "Printing Task MMU Information:" << endl;

    Task * current_task = Task::self();

    cout << "Printing Code MMU Information:" << endl;
    CPU::Log_Addr current_task_code_init = current_task->code();
    cout << MMU::Translation(current_task_code_init) << endl;

    cout << "Printing Data MMU Information:" << endl;
    CPU::Log_Addr current_task_data_init = current_task->data();
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

    // @corss ???
    Address_Space self(MMU::current());

    // Segment * cs = new (SYSTEM) Segment(CODE_SIZE, Segment::Flags::SYS);
    // Segment * ds = new (SYSTEM) Segment(DATA_SIZE, Segment::Flags::SYS);

    cout << "Creating code and data segments for the first task:" << endl;
    Segment * cs;
    Segment * ds;
    cout << "  extra segment 1 => " << CODE_SIZE << " bytes, done!" << endl;
    cout << "  extra segment 2 => " << DATA_SIZE << " bytes, done!" << endl;

    // cout << "Creating code and data segments for the second task (which will be overwritten)..." << endl;
    // // @cross nao sei se ta certo inicializar isso e depois sobreescrever
    // //          eu tentei nao inicializar, mas ai ele reclamava tambem.
    // Segment * code_segment_2 = new (SYSTEM) Segment(CODE_SIZE, Segment::Flags::SYS);;
    // Segment * data_segment_2 = new (SYSTEM) Segment(DATA_SIZE, Segment::Flags::SYS);;

    //@cross: checar a ordem de enable e disable

    Task * c_task = Task::self();
    cout << "Attaching code segment..." << endl;
    unsigned int cs_size = c_task->code_segment()->size();
    cs = new (SYSTEM) Segment(cs_size, Segment::Flags::SYS);
    CPU::int_disable();
    CPU::Log_Addr tmp_code = c_task->address_space()->attach(cs);
    memcpy(tmp_code, c_task->code(), cs_size);
    c_task->address_space()->detach(cs);
    CPU::int_enable();

    cout << "Attaching data segment..." << endl;
    unsigned int ds_size = c_task->data_segment()->size();
    ds = new (SYSTEM) Segment(ds_size, Segment::Flags::SYS);
    CPU::int_disable();
    CPU::Log_Addr tmp_data = c_task->address_space()->attach(ds);
    memcpy(tmp_data, c_task->data(), ds_size);
    c_task->address_space()->detach(ds);
    CPU::int_enable();


    cout << "Deleting segments from the first fork";
    delete cs;
    delete ds;
    cout << "  done!" << endl;
    // Handmade fork
    // @cross nao sei se precisa desse system
    
    print_mmu_translation();
    
    new (SYSTEM) Task(tmp_code, tmp_data, &print_mmu_translation);
    // Task * new_task = new (SYSTEM) Task(code_segment_2, data_segment_2, &print_mmu_translation);

    // @cross
    // a gnete usa isso?
    // Thread::self()->yield();


    // call thread.dispatch()

    // these are tasks, do I need thread?
    // dispatch(current_task, new_task);
    //  ^ aparentemente nao ujsa isso

    // Thread::self()->yield();

    cout << "I'm done, bye!" << endl;

    return 0;
}
