#include <utility/ostream.h>
#include <utility/handler.h>

#include <process.h>
#include <synchronizer.h>
#include <time.h>

using namespace EPOS;

OStream cout;

int test_thread() {
    Thread::exit(3145);
    return 3145;
}

int suspended_print() {
    cout << "suspended_print()" << endl;
    return '*';
}

int print_echo()
{
    cout << "print_echo()" << endl;
    return 0;
}

int main()
{    
    cout << "Testing Syscalls!" << endl;
    
    // Test Syscall 
    int val = 42;
    CPU::syscall((void*) &val);
    cout << "dummy syscall called with success" << endl;

    // Test Thread
    cout << "Thread:" << endl;
    Thread * t = new Thread(&test_thread);
    cout << "   t: self=" << t << ", state=" << t->state() << ", priority=" << t->priority() << endl; 
    cout << "   M: self=" << Thread::self() << ", state=" << Thread::self()->state() << ", priority=" << Thread::self()->priority() << endl;     
    cout << "t returned with code=" << t->join() << endl;

    Thread * suspended = new Thread(&suspended_print);
    suspended->suspend();

    return 0;
}
