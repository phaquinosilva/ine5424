#include <architecture/armv7/armv7_cpu.h>

__BEGIN_SYS
void CPU::syscall(void * message) {
    ASM("push {lr}\n");
    CPU::r0(reinterpret_cast<Reg>(message));
    ASM("svc 0x0");
    ASM("pop {lr}\n");
}
__END_SYS