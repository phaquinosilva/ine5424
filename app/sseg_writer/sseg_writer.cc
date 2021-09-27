#include <utility/ostream.h>
#include <process.h>
#include <memory.h>
// #include <utility/elf.h>
// #include <architecture.h>
// #include <system.h>
#include <time.h>

#include <syscall/stub_shared_segment.h>
#include <syscall/stub_task.h>
#include <syscall/stub_segment.h>

using namespace EPOS;

OStream cout;

typedef long unsigned int Log_Addr;

int main()
{
    cout << "Writer begins" << endl;
    
    // TODO resolver com argc e argv esse port
    unsigned int port = 1;

    // Criar shared segment stub
    Stub_Shared_Segment * sseg = new Stub_Shared_Segment(port, 1024);
    
    // Log_Addr sseg_log_addr = Stub_Task::active()->address_space()->attach(reinterpret_cast<Stub_Segment *>(sseg));
    _SYS::CPU::Log_Addr sseg_log_addr = Stub_Task::self()->address_space()->attach(reinterpret_cast< Stub_Segment *>(sseg));
    cout << "sseg_log_addr_writer=" << sseg_log_addr << endl;
    
    long unsigned int * a = sseg_log_addr;    
    cout << "writer pointer: " << *a << endl;
    
    char * letters = reinterpret_cast<char *>(a + sizeof(long unsigned int));
    char all_letters[40] = "Test Message to be Read";

    for(int i=0;i<24;i++){
        letters[i] = all_letters[i];
    }
    
    cout << "writer is finishing" << endl;
    // Stub_Task::active()->address_space()->detach(reinterpret_cast<Stub_Segment *>(sseg));
    // Log_Addr sseg_log_addr = _SYS::Task::self()->address_space()->attach(reinterpret_cast<Stub_Segment *>(sseg));

    // _SYS::Task::self()->address_space()->detach(reinterpret_cast< _SYS::Segment *>(sseg));
    delete sseg;

    return 0;
}
