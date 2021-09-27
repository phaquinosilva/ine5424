// #include <utility/ostream.h>
#include <memory.h>
#include <process.h>

#include <syscall/stub_shared_segment.h>
#include <syscall/stub_segment.h>

using namespace EPOS;

OStream cout;

typedef long unsigned int Log_Addr;

int main()
{
    cout << "Reader begins" << endl;
    
    // TODO resolver com argc e argv esse port
    unsigned int port = 1;

    // Shared_Segment * sseg = new Shared_Segment(port, 1024, MMU::Flags::APPD);
    Stub_Shared_Segment * sseg = new Stub_Shared_Segment(port, 1024);

    _SYS::CPU::Log_Addr sseg_log_addr = _SYS::Stub_Task::self()->address_space()->attach(reinterpret_cast< Stub_Segment *>(sseg));
    cout << "sseg_log_addr_reader=" << sseg_log_addr << endl;

    long unsigned int * a = sseg_log_addr;    
    cout << "reader pointer: " << *a << endl;

    char * letters = reinterpret_cast<char *>(a + sizeof(long unsigned int));
    cout << "letters:" << endl;
    for(int i=0;i<24;i++){
        cout << letters[i];
    }
    
    cout << "Reader is finishing" << endl;
    // _SYS::Task::self()->address_space()->detach(reinterpret_cast< _SYS::Segment *>(sseg));

    delete sseg; 

    return 0;
}
