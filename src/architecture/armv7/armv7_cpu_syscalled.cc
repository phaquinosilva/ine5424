// EPOS IA32 CPU System Call Entry Implementation

#include <architecture/armv7/armv7_cpu.h>

extern "C" { void _exec(void *); }

__BEGIN_SYS

void CPU::syscalled()
{
    // TODO checar se tem coisa faltando pra salvar/carregar contexto
    // TODO esse codigo nao roda, a gente tem que adaptar isso pra Agent e eu nao sei como
    // Agent agent = Agent(reinterpret_cast<Message*>(CPU::r0()));

    ASM("push {r1-r12}  \n");

    // CPU::r0(reinterpret_cast<CPU::Reg>(message));
    CPU::r0();

    ASM("pop {r1-r12}  \n");
}

__END_SYS
