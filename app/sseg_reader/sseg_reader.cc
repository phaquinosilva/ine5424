// #include <utility/ostream.h>

#include <syscall/stub_shared_segment.h>
#include <syscall/stub_segment.h>
#include <syscall/stub_task.h>

using namespace EPOS;

OStream cout;

typedef long unsigned int Log_Addr;
typedef long unsigned int Phy_Addr;

int main()
{
    cout << "Reader begins" << endl;
    
    // TODO resolver com argc e argv esse port
    unsigned int port = 1;

    // Shared_Segment * sseg = new Shared_Segment(port, 1024, MMU::Flags::APPD);
    Stub_Shared_Segment * sseg = new Stub_Shared_Segment(port, 1024);

    Phy_Addr phy_addr = sseg->phy_address();
    cout << "phy_addr_reader=" << phy_addr << endl;

    Log_Addr sseg_log_addr = Stub_Task::active()->address_space()->attach(reinterpret_cast<Stub_Segment *>(sseg));
    cout << "sseg_log_addr_reader=" << sseg_log_addr << endl;

    long unsigned int * a = sseg_log_addr;    
    cout << "reader pointer: " << *a << endl;

    char * letters = reinterpret_cast<char *>(a + sizeof(long unsigned int));
    cout << "letters:" << endl;
    for(int i=0;i<23;i++){
        cout << letters[i];
    }
    
    cout << "Reader is finishing" << endl;
    Stub_Task::active()->address_space()->detach(reinterpret_cast<Stub_Segment *>(sseg));

    delete sseg; 

    return 0;
}
