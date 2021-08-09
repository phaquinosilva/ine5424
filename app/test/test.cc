// EPOS Segment Test Program

#include <memory.h>
#include <process.h>

using namespace EPOS;

const unsigned ES1_SIZE = 10000;
const unsigned ES2_SIZE = 100000;

int main()
{
    OStream cout;

    cout << "Segment test" << endl;

    cout << "My address space's page directory is located at "
         << reinterpret_cast<void *>(CPU::pdp()) << "" << endl;
    Address_Space * as = Task::self()->address_space();

    cout << "Creating two extra data segments:" << endl;
    Segment * es1 = new (SYSTEM) Segment(ES1_SIZE, WHITE, Segment::Flags::SYS);
    Segment * es2 = new (SYSTEM) Segment(ES2_SIZE);
    cout << "  extra segment 1 => " << ES1_SIZE << " bytes, done!" << endl;
    cout << "  extra segment 2 => " << ES2_SIZE << " bytes, done!" << endl;

    cout << "Attaching segments:" << endl;
    CPU::Log_Addr * extra1 = as->attach(es1);
    CPU::Log_Addr * extra2 = as->attach(es2);
    cout << "  extra segment 1 => " << extra1 << " done!" << endl;
    cout << "  extra segment 2 => " << extra2 << " done!" << endl;

    cout << "Clearing segments:";
    memset(extra1, 0, ES1_SIZE);
    memset(extra2, 0, ES2_SIZE);
    cout << "  done!" << endl;

    cout << "Detaching segments:";
    as->detach(es1);
    as->detach(es2);
    cout << "  done!" << endl;

    cout << "Deleting segments:";
    delete es1;
    delete es2;
    cout << "  done!" << endl;

    cout << "I'm done, bye!" << endl;

    return 0;
}
