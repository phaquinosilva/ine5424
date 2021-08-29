// EPOS Task Test Program

#include <time.h>
#include <process.h>

using namespace EPOS;

OStream cout;

int print_mmu_translation(Task * this_task)
{
    cout << "Printing Task MMU Information:" << endl;
    
    cout << "My address space's page directory is located at "
         << reinterpret_cast<void *>(CPU::pdp()) << "" << endl;
         
    cout << "Printing Code MMU Information:" << endl;
    CPU::Log_Addr current_task_code_init = this_task->code();
    cout << MMU::Translation(current_task_code_init) << endl;

    cout << "Printing Data MMU Information:" << endl;
    CPU::Log_Addr current_task_data_init = this_task->data();
    cout << MMU::Translation(current_task_data_init) << endl;

    return 0;
}

int func_task(void)
{   
    cout << "I'm the created task and I'll print my info" << endl;
    print_mmu_translation(Task::self());
    cout << "I will now suspend myself until I receive a Timer Interrupt" << endl;
    Task::self()->main()->suspend();
    cout << "I'm the created task and now I'll finish" << endl;
    return 0;
}

int main()
{
    cout << "Test task context switching at a Timer Interrupt\n" << endl;
    
    cout << "This is my information:" << endl;
    Task * current_task = Task::self();
    print_mmu_translation(current_task);

    cout << "I will now perform a manual fork and create another task with the same code and data segments..." << endl;

    
    unsigned int cs_size = current_task->code_segment()->size();
    Segment * code_segment = new (SYSTEM) Segment(cs_size, Segment::Flags::SYS);
    CPU::int_disable();
    CPU::Log_Addr tmp_code = current_task->address_space()->attach(code_segment);
    memcpy(tmp_code, current_task->code(), cs_size);
    current_task->address_space()->detach(code_segment);
    CPU::int_enable();
    
    unsigned int ds_size = current_task->data_segment()->size();
    Segment * data_segment = new (SYSTEM) Segment(ds_size, Segment::Flags::SYS);
    CPU::int_disable();
    CPU::Log_Addr tmp_data = current_task->address_space()->attach(data_segment);
    memcpy(tmp_data, current_task->data(), ds_size);
    current_task->address_space()->detach(data_segment);
    CPU::int_enable();
    Task * new_task = new (SYSTEM) Task(code_segment, data_segment, &func_task);

    cout << "I will now cause a timer interrupt!" << endl;
    

    cout << "I'll now yield so it can print its information" << endl;
    
    new_task->main()->resume();

    cout << "All tasks done, bye!" << endl;

    return 0;
}

