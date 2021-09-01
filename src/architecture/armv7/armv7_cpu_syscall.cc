// EPOS RISC-V 32 System Call Function Implementation

#include <architecture/armv7/armv7_cpu.h>
#include <machine/ic.h>

__BEGIN_SYS

void CPU::syscall(void * message)
{
    // TODO: checar se isso é o suficiente pra guardar o contexto
    ASM("push {lr}\n");

    CPU::r0(reinterpret_cast<CPU::Reg>(message));
    ASM("svc   0x0");

    ASM("pop {lr}\n");
}

__END_SYS
