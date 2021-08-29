// EPOS RISC-V 32 System Call Function Implementation

#include <architecture/armv7/armv7_cpu.h>
#include <machine/ic.h>

__BEGIN_SYS

// TODO @cross
// ORIGINALMENTE RETIRADO DO rv32
// ok, essas duas ASM call sao extremamente especificas
// acho que agora eh a hora que eu vou ler a wiki de syscall e descobrir EAECOMOFAS

void CPU::syscall(void * message)
{
    CPU::r0(reinterpret_cast<CPU::Reg>(message));
    ASM("svc   0x0");
    // CPU::ecall();
}

__END_SYS
