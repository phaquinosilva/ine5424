// EPOS ARMv7 System Call Function Implementation

#include <architecture/armv7/armv7_cpu.h>
#include <machine/ic.h>

__BEGIN_SYS

void CPU::syscall(void * message)
{
    // TODO @cross: erase comment
    // Isso é do guto
    CPU::r1(reinterpret_cast<CPU::Reg>(message));
    CPU::svc();

    // // TODO @cross: isso eh nosso, se pah tem que guardar contexto aqui
    // //                  ver se ta em outro lugar.
    // //                   na real, parece que o syscalled ta cuidando disso sussa.
    // ASM("push {lr}\n");

    // CPU::r0(reinterpret_cast<CPU::Reg>(message));
    // ASM("svc   0x0");

    // ASM("pop {lr}\n");
}

__END_SYS
