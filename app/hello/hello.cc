#include <utility/ostream.h>
#include <syscall/stub_thread.h>

using namespace EPOS;

OStream cout;

int main()
{
    cout << endl << "*********************************" << endl;
    cout << endl << "           Hello world!          " << endl;
    cout << endl << "*********************************" << endl;
    return 0;
}
