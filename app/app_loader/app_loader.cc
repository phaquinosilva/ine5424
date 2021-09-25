#include <utility/ostream.h>
#include <syscall/stub_fork.h>

using namespace EPOS;

OStream cout;

int main(int argc, char ** argv)
{
    unsigned argc_2 = (unsigned) argc;

    cout << "======= ESSE EH O ARGC DA MASSA =======" << "\n";
    cout << argc_2 << "\n";
    cout << "======= ESSE EH O ARGV DA MASSA =======" << "\n";
    cout << argv << "\n";

    // cout << "======= ESSE EH O ARGC DA MASSA =======" << "\n" << endl;
    // cout << argc_2 << "\n" << endl;
    // cout << "======= ESSE EH O ARGV DA MASSA =======" << "\n" << endl;
    // cout << argv << "\n" << endl;
    // cout << "Hello world!" << endl;
    int r;
    r = fork();
    cout << "HAHAHA FUNCIONOU : " << r << endl;
    cout << "HOHOHO FUNCIONOU : " << r << endl;
    // cout << "======= ESSE EH O ARGC DA MASSA =======" << "\n" << endl;
    // cout << argc_2 << "\n" << endl;
    // cout << "======= ESSE EH O ARGV DA MASSA =======" << "\n" << endl;
    // cout << argv << "\n" << endl;

    return 0;
}
