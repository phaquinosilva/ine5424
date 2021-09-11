// // EPOS Kernel Binding

// #include <syscall/agent.h>

// // Framework class attributes
// __BEGIN_SYS

// // The order of components in Agent::_handlers must match the respective Type<Component>::ID
// Agent::Member Agent::_handlers[] = {&Agent::handle_thread,
//                                     &Agent::handle_task,
//                                     &Agent::handle_active,
//                                     &Agent::handle_address_space,
//                                     &Agent::handle_segment,
//                                     &Agent::handle_mutex,
//                                     &Agent::handle_semaphore,
//                                     &Agent::handle_condition,
//                                     &Agent::handle_clock,
//                                     &Agent::handle_alarm,
//                                     &Agent::handle_chronometer,
//                                     &Agent::handle_utility};

// __END_SYS

// __USING_SYS;
// extern "C" { void _exec(void * m) { reinterpret_cast<Agent *>(m)->exec(); } }


// /usr/bin/arm-none-eabi-ld: /home/gabriel/programas/grupo_L_ine5424/ine5424/lib/libarch_raspberry_pi3.a(armv7_cpu_syscalled.o): in function `EPOS::S::CPU::syscalled()':
// armv7_cpu_syscalled.cc:(.text._ZN4EPOS1S3CPU9syscalledEv+0x0): multiple definition of `_software_interrupt'; /home/gabriel/programas/grupo_L_ine5424/ine5424/lib/libmach_raspberry_pi3.a(raspberry_pi3_ic.o):raspberry_pi3_ic.cc:(.text._ZN4EPOS1S2IC18software_interruptEv+0x0): first defined here
// /usr/bin/arm-none-eabi-ld: /home/gabriel/programas/grupo_L_ine5424/ine5424/lib/libsys_raspberry_pi3.a(condition.o): in function `EPOS::S::Condition::~Condition()':
// condition.cc:(.text._ZN4EPOS1S9ConditionD2Ev+0x14): undefined reference to `EPOS::S::Thread::wakeup_all(EPOS::S::U::Ordered_Queue<EPOS::S::Thread, EPOS::S::RM, EPOS::S::U::List_Elements::Doubly_Linked_Scheduling<EPOS::S::Thread, EPOS::S::RM> >*)'
// /usr/bin/arm-none-eabi-ld: /home/gabriel/programas/grupo_L_ine5424/ine5424/lib/libsys_raspberry_pi3.a(condition.o): in function `EPOS::S::Condition::wait()':
// condition.cc:(.text._ZN4EPOS1S9Condition4waitEv+0x10): undefined reference to `EPOS::S::Thread::sleep(EPOS::S::U::Ordered_Queue<EPOS::S::Thread, EPOS::S::RM, EPOS::S::U::List_Elements::Doubly_Linked_Scheduling<EPOS::S::Thread, EPOS::S::RM> >*)'
// /usr/bin/arm-none-eabi-ld: /home/gabriel/programas/grupo_L_ine5424/ine5424/lib/libsys_raspberry_pi3.a(condition.o): in function `EPOS::S::Condition::signal()':
// condition.cc:(.text._ZN4EPOS1S9Condition6signalEv+0x10): undefined reference to `EPOS::S::Thread::wakeup(EPOS::S::U::Ordered_Queue<EPOS::S::Thread, EPOS::S::RM, EPOS::S::U::List_Elements::Doubly_Linked_Scheduling<EPOS::S::Thread, EPOS::S::RM> >*)'
// /usr/bin/arm-none-eabi-ld: /home/gabriel/programas/grupo_L_ine5424/ine5424/lib/libsys_raspberry_pi3.a(condition.o): in function `EPOS::S::Condition::broadcast()':
// condition.cc:(.text._ZN4EPOS1S9Condition9broadcastEv+0x10): undefined reference to `EPOS::S::Thread::wakeup_all(EPOS::S::U::Ordered_Queue<EPOS::S::Thread, EPOS::S::RM, EPOS::S::U::List_Elements::Doubly_Linked_Scheduling<EPOS::S::Thread, EPOS::S::RM> >*)'
// /usr/bin/arm-none-eabi-ld: /home/gabriel/programas/grupo_L_ine5424/ine5424/lib/libsys_raspberry_pi3.a(mutex.o): in function `EPOS::S::Mutex::~Mutex()':
// mutex.cc:(.text._ZN4EPOS1S5MutexD2Ev+0x14): undefined reference to `EPOS::S::Thread::wakeup_all(EPOS::S::U::Ordered_Queue<EPOS::S::Thread, EPOS::S::RM, EPOS::S::U::List_Elements::Doubly_Linked_Scheduling<EPOS::S::Thread, EPOS::S::RM> >*)'
// /usr/bin/arm-none-eabi-ld: /home/gabriel/programas/grupo_L_ine5424/ine5424/lib/libsys_raspberry_pi3.a(mutex.o): in function `EPOS::S::Mutex::lock()':
// mutex.cc:(.text._ZN4EPOS1S5Mutex4lockEv+0x44): undefined reference to `EPOS::S::Thread::sleep(EPOS::S::U::Ordered_Queue<EPOS::S::Thread, EPOS::S::RM, EPOS::S::U::List_Elements::Doubly_Linked_Scheduling<EPOS::S::Thread, EPOS::S::RM> >*)'
// /usr/bin/arm-none-eabi-ld: /home/gabriel/programas/grupo_L_ine5424/ine5424/lib/libsys_raspberry_pi3.a(mutex.o): in function `EPOS::S::Mutex::unlock()':
// mutex.cc:(.text._ZN4EPOS1S5Mutex6unlockEv+0x30): undefined reference to `EPOS::S::Thread::wakeup(EPOS::S::U::Ordered_Queue<EPOS::S::Thread, EPOS::S::RM, EPOS::S::U::List_Elements::Doubly_Linked_Scheduling<EPOS::S::Thread, EPOS::S::RM> >*)'
// /usr/bin/arm-none-eabi-ld: /home/gabriel/programas/grupo_L_ine5424/ine5424/lib/libsys_raspberry_pi3.a(semaphore.o): in function `EPOS::S::Semaphore::~Semaphore()':
// semaphore.cc:(.text._ZN4EPOS1S9SemaphoreD2Ev+0x14): undefined reference to `EPOS::S::Thread::wakeup_all(EPOS::S::U::Ordered_Queue<EPOS::S::Thread, EPOS::S::RM, EPOS::S::U::List_Elements::Doubly_Linked_Scheduling<EPOS::S::Thread, EPOS::S::RM> >*)'
// /usr/bin/arm-none-eabi-ld: /home/gabriel/programas/grupo_L_ine5424/ine5424/lib/libsys_raspberry_pi3.a(semaphore.o): in function `EPOS::S::Semaphore::p()':
// semaphore.cc:(.text._ZN4EPOS1S9Semaphore1pEv+0x40): undefined reference to `EPOS::S::Thread::sleep(EPOS::S::U::Ordered_Queue<EPOS::S::Thread, EPOS::S::RM, EPOS::S::U::List_Elements::Doubly_Linked_Scheduling<EPOS::S::Thread, EPOS::S::RM> >*)'
// /usr/bin/arm-none-eabi-ld: /home/gabriel/programas/grupo_L_ine5424/ine5424/lib/libsys_raspberry_pi3.a(semaphore.o): in function `EPOS::S::Semaphore::v()':
// semaphore.cc:(.text._ZN4EPOS1S9Semaphore1vEv+0x40): undefined reference to `EPOS::S::Thread::wakeup(EPOS::S::U::Ordered_Queue<EPOS::S::Thread, EPOS::S::RM, EPOS::S::U::List_Elements::Doubly_Linked_Scheduling<EPOS::S::Thread, EPOS::S::RM> >*)'
// make[3]: *** [makefile:29: system_builtin_raspberry_pi3] Error 1
