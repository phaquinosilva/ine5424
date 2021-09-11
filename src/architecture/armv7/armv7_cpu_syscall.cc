// EPOS ARMv7 System Call Function Implementation

#include <architecture/armv7/armv7_cpu.h>
#include <machine/ic.h>

__BEGIN_SYS

void CPU::syscall(void * message)
{
    // // TODO @cross: erase comment
    // // Isso é do guto
    // CPU::r1(reinterpret_cast<CPU::Reg>(message));
    // CPU::svc();

    // // TODO @cross: isso eh nosso, se pah tem que guardar contexto aqui
    // //                  ver se ta em outro lugar.
    // //                   na real, parece que o syscalled ta cuidando disso sussa.
    // ASM("push {lr}\n");

    // CPU::r0(reinterpret_cast<CPU::Reg>(message));
    // ASM("svc   0x0");

    // ASM("pop {lr}\n");

    // TODO @cross dosguri

    ASM(
        //Salvando contexto
        "push {lr}  \n"
        "push {r0, r12}  \n"
        //Chamando sycall
        "mov r0, %0 \n"
        "mov r12, sp \n"  // salvar tmp sp_usr
        "mrs sp, sp_usr \n" // carregar sp_svc
        "msr sp_usr, r12 \n"// salvar sp_usr

        "SVC 0x0    \n"

        "mov r12, sp \n"  //salvar tmp sp_svc
        "mrs sp, sp_usr \n" //carregar sp_usr
        "msr sp_usr, r12 \n" //salver_sp_svc

        //Retornando contexto
        "pop {r0, r12}   \n"
        "pop {lr}   \n"
        "" :: "r"(message)
    );
}

__END_SYS
