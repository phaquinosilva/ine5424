#include <utility/ostream.h>
#include <utility/elf.h>
#include <architecture.h>
#include <system.h>
#include <time.h>
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

    cout << "Loading beginned" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    // unsigned end = ((unsigned)&argv < Application::APP_DATA) ? Application::APP_DATA : (unsigned)MMU::align_page(&_end);
    // unsigned end = ((unsigned)&argv < Application::APP_DATA) ? Application::APP_DATA : (unsigned)MMU::align_page(&argv);
    // int * extras = static_cast<int*>(MMU::align_page(end) + Application::HEAP_SIZE);
    
    unsigned HEAP_SIZE = 16 * 1024;
    unsigned end = (unsigned)MMU::align_page(&argv);
    int * extras = static_cast<int*>(MMU::align_page(end) + HEAP_SIZE);
    // cout << "end=" << end << endl;
    // cout << "Extras is located at addr=" << extras << endl;

        // TODO fazer o WHILE de varios app.
    // for (int app_size = *extras; app_size; extras += app_size/4, app_size = *reinterpret_cast<int*>(extras)) {
    // while

    
    ELF * app_elf = reinterpret_cast<ELF *>(++extras);
    if (!app_elf->valid()) {
        cout << "Skipping corrupted App" << endl;
    } else {
        cout << "This Elf was actually valid :D !" << endl;
    }
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;




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
