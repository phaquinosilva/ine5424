// EPOS Application Binding

#include <utility/spin.h>
#include <utility/ostream.h>
#include <architecture/cpu.h>
#include <system.h>
#include <stubs/stub_thread.h>

__BEGIN_SYS
__END_SYS


// Global objects
__BEGIN_SYS
OStream kerr;
__END_SYS


// Bindings
extern "C" {
    void _panic() { _API::Stub_Thread::exit(-1); }
    void _exit(int s) { _API::Stub_Thread::exit(s); for(;;); }

    // TODO @cross: try not to use this
    // void __exit() { _API::Stub_Thread::exit(_SYS::CPU::fr()); }

    // Utility methods that differ from kernel and user space.
    // Heap
    static _UTIL::Simple_Spin _heap_spin;
    void _lock_heap() { _heap_spin.acquire(); }
    void _unlock_heap() { _heap_spin.release();}
}

__USING_SYS;
extern "C" {
    void _syscall(void * m) { CPU::syscall(m); }
    void _print(const char * s) {
        // TODO @cross remove this
        // Message msg(Id(UTILITY_ID, 0), Message::PRINT, reinterpret_cast<unsigned int>(s));
        Message msg(Message::ENTITY::DISPLAY, Message::PRINT, s);
        msg.act();
    }
}
