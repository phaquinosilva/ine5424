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
    // cout << "My address space's page directory is located at "
        //  << reinterpret_cast<void *>(MMU::pd()) << "" << endl;

    cout << "Printing Code MMU Information:" << endl;
    CPU::Log_Addr current_task_code_init = this_task->code();
    cout << MMU::Translation(current_task_code_init) << endl;

    cout << "Printing Data MMU Information:" << endl;
    CPU::Log_Addr current_task_data_init = this_task->data();
    cout << MMU::Translation(current_task_data_init) << endl;

    return 0;
}

int main()
{    
    cout << "Test task context switching at a Thread::dispatch()\n" << endl;

    Task * current_task = Task::self();
    cout << "Attaching code segment..." << endl;
    unsigned int cs_size = current_task->code_segment()->size();
    Segment * code_segment = new (SYSTEM) Segment(cs_size, Segment::Flags::SYS);
    CPU::int_disable();
    CPU::Log_Addr tmp_code = current_task->address_space()->attach(code_segment);
    memcpy(tmp_code, current_task->code(), cs_size);
    current_task->address_space()->detach(code_segment);
    CPU::int_enable();

    cout << "Attaching data segment..." << endl;
    unsigned int ds_size = current_task->data_segment()->size();
    Segment * data_segment = new (SYSTEM) Segment(ds_size, Segment::Flags::SYS);
    CPU::int_disable();
    CPU::Log_Addr tmp_data = current_task->address_space()->attach(data_segment);
    memcpy(tmp_data, current_task->data(), ds_size);
    current_task->address_space()->detach(data_segment);
    CPU::int_enable();

    print_mmu_translation();
    
    new (SYSTEM) Task(code_segment, data_segment, &print_mmu_translation);

    Thread::self()->yield();

    cout << "I'm done, bye!" << endl;

    return 0;
}
