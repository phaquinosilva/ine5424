#include <utility/ostream.h>

#include<utility/elf.h>

#include <syscall/stub_loader.h>
#include <syscall/stub_thread.h>
#include <utility/load_app.h>

#include <syscall/stub_segment.h>

using namespace EPOS;

OStream cout;

int main(int argc, char** argv)
{
    cout << "Loader!" << endl;    

    cout << "Argc: " << argc << endl;
    cout << "Argv: " << argv << " / " << reinterpret_cast<unsigned int> (argv) << endl;

    Stub_Loader * sld = new Stub_Loader();
    cout << "Carregando aplicações:" << endl;

    int tam_proximo_app = 0;
    int tam_app = 0;
    int off_set = 0;
    int i = 1;
    unsigned int addr = reinterpret_cast<unsigned int> (argv);

    if (argc)
    do {
        tam_app = *(reinterpret_cast<int*> (addr + off_set));
        sld -> new_app(off_set, addr);
        
        tam_proximo_app = *(reinterpret_cast<int*> (addr + off_set + tam_app + 4));
        off_set = tam_app + 4;

        cout << "Aplicação[" << i << "](" << tam_app << ") caregada, proxima tem tamanho:" << tam_proximo_app << endl;
        i++;
    } while (tam_proximo_app);

    cout << "Fim Loader!" << endl;
    return 0;
}
