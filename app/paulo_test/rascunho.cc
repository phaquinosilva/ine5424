// Fork Test

#include <memory.h>

using namespace EPOS;

const unsigned CODE_SIZE = 10000;
const unsigned DATA_SIZE = 100000;

int main()
{    
    OStream cout;

    cout << "Fork test" << endl;

    // // @cross
    // // To be used
    // m = Thread::self();
    // Task * task0 = Task::self();
    // Address_Space * as0 = task0->address_space();
    // cout << "My address space's page directory is located at " << as0->pd() << endl;

    cout << "My address space's page directory is located at "
         << reinterpret_cast<void *>(CPU::pdp()) << "" << endl;
    Address_Space self(MMU::current());

    cout << "Creating two extra data segments:" << endl;
    Segment * code_segment = new (SYSTEM) Segment(CODE_SIZE, Segment::Flags::SYS);
    Segment * data_segment = new (SYSTEM) Segment(DATA_SIZE, Segment::Flags::SYS);
    cout << "  extra segment 1 => " << CODE_SIZE << " bytes, done!" << endl;
    cout << "  extra segment 2 => " << DATA_SIZE << " bytes, done!" << endl;



    // @cross
    // os cara tao atachando direito no self?
    // isso funciona igual a: "Task * task0 = Task::self();" -- ?
    // bom, vamo assumir que esses attach tao funcionando por hora.
    cout << "Attaching segments:" << endl;
    CPU::Log_Addr * extra1 = self.attach(code_segment);
    // Log_Addr ustack = Task::self()->address_space()->attach(_user_stack);
    // _code(_as->attach(_cs))
    CPU::Log_Addr * extra2 = self.attach(data_segment);
    cout << "  extra segment 1 => " << extra1 << " done!" << endl;
    cout << "  extra segment 2 => " << extra2 << " done!" << endl;

    // cout << "Clearing segments:";
    // memset(extra1, 0, CODE_SIZE);
    // memset(extra2, 0, DATA_SIZE);
    // cout << "  done!" << endl;

    // TODO to copiando pra onde?
    // eh um array de bytes mesmo? O.O

    // TODO o pedro ta falando pra fazer um de cada vez,
    // ao inves de fazer os 2 juntos em attach, copy, dettach.
    //  ta mas se eu vou copiar os contents...
    //  ... eu vou ter que colar tambem
    //  do contrario nao tem nexo memo

    cout << "Copying segments:";
    memcpy(copyto1, extra1, CODE_SIZE);
    memcpy(copyto2, extra2, DATA_SIZE);
    cout << "  done!" << endl;


    cout << "Detaching segments:";
    self.detach(code_segment);
    self.detach(data_segment);
    cout << "  done!" << endl;

    cout << "Deleting segments:";
    delete code_segment;
    delete data_segment;
    cout << "  done!" << endl;

    cout << "I'm done, bye!" << endl;

    return 0;
}
