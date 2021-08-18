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

    // Task * current_task = Task::self();

    cout << "My address space's page directory is located at "
         << reinterpret_cast<void *>(CPU::pdp()) << "" << endl;
    Address_Space self(MMU::current());

    cout << "Creating code and data segments for the first task:" << endl;
    Segment * code_segment = new (SYSTEM) Segment(CODE_SIZE, Segment::Flags::SYS);
    Segment * data_segment = new (SYSTEM) Segment(DATA_SIZE, Segment::Flags::SYS);
    cout << "  extra segment 1 => " << CODE_SIZE << " bytes, done!" << endl;
    cout << "  extra segment 2 => " << DATA_SIZE << " bytes, done!" << endl;

    cout << "Creating code and data segments for the second task (which will be overwritten)..." << endl;
    // @cross nao sei se ta certo inicializar isso e depois sobreescrever
    //          eu tentei nao inicializar, mas ai ele reclamava tambem.
    Segment * code_segment_2 = new (SYSTEM) Segment(CODE_SIZE, Segment::Flags::SYS);;
    Segment * data_segment_2 = new (SYSTEM) Segment(DATA_SIZE, Segment::Flags::SYS);;

    //@cross: checar a ordem de enable e disable

    // Code attach, copying and dettaching
    cout << "Disabling Interruptions..." << endl;
    CPU::int_disable();
    cout << "Attaching code segment..." << endl;
    CPU::Log_Addr * code_addr = self.attach(code_segment);
    cout << "Copying code segment..." << endl;
    memcpy(code_segment_2, code_addr, CODE_SIZE);
    cout << "Detaching code segment..." << endl;
    self.detach(code_segment);
    cout << "Enabling Interruptions again..." << endl;
    CPU::int_enable();

    // Data attach, copying and dettaching
    cout << "Disabling Interruptions..." << endl;
    CPU::int_disable();
    cout << "Attaching data segment..." << endl;
    CPU::Log_Addr * data_addr = self.attach(data_segment);
    cout << "Copying data segment..." << endl;
    memcpy(data_segment_2, data_addr, DATA_SIZE);
    cout << "Detaching data segment..." << endl;
    self.detach(data_segment);
    cout << "Enabling Interruptions again..." << endl;
    CPU::int_enable();

    cout << "Deleting segments from the first fork";
    delete code_segment;
    delete data_segment;
    cout << "  done!" << endl;
    // Handmade fork
    // @cross nao sei se precisa desse system
    
    print_mmu_translation();
    
    new (SYSTEM) Task(code_segment_2, data_segment_2, &print_mmu_translation);
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
