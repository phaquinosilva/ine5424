
#ifndef __syscall_message_h
#define __syscall_message_h

#include <system.h>

__BEGIN_SYS


class SyscallMessage
{
public:
    //@pedro: I suppose these are all the stubs we'll need
    enum {
        // CREATE,
        // CREATE1,
        // CREATE2,
        // CREATE3,
        // CREATE4,
        // CREATE5,
        // CREATE6,
        // CREATE7,
        // CREATE8,
        // CREATE9,
        // DESTROY,
        // SELF,

        THREAD,
        THREAD_STATE,
        THREAD_PRIORITY,
        THREAD_PRIORITY1,
        THREAD_JOIN,
        THREAD_PASS,
        THREAD_SUSPEND,
        THREAD_RESUME,
        THREAD_YIELD,
        THREAD_EXIT,
        THREAD_WAIT_NEXT,

        // TASK_ADDRESS_SPACE,
        // TASK_CODE_SEGMENT,
        // TASK_DATA_SEGMENT,
        // TASK_CODE,
        // TASK_DATA,
        // TASK_MAIN,

        // ADDRESS_SPACE_PD,
        // ADDRESS_SPACE_ATTACH1,
        // ADDRESS_SPACE_ATTACH2,
        // ADDRESS_SPACE_DETACH1,
        // ADDRESS_SPACE_DETACH2,
        // ADDRESS_SPACE_PHYSICAL,

        // SEGMENT_SIZE,
        // SEGMENT_PHY_ADDRESS,
        // SEGMENT_RESIZE,
        // CREATE_SEGMENT_IN_PLACE,
        // CREATE_HEAP_IN_PLACE,

        // SYNCHRONIZER_LOCK,
        // SYNCHRONIZER_UNLOCK,
        // SYNCHRONIZER_P,
        // SYNCHRONIZER_V,
        // SYNCHRONIZER_WAIT,
        // SYNCHRONIZER_SIGNAL,
        // SYNCHRONIZER_BROADCAST,

        // ALARM_DELAY,
        // ALARM_GET_PERIOD,
        // ALARM_SET_PERIOD,
        // ALARM_FREQUENCY,

        // COMMUNICATOR_SEND,
        // COMMUNICATOR_REPLY,
        // COMMUNICATOR_RECEIVE,

        // PRINT,

        UNDEFINED = -1
    };
    typedef int Type;

public:
    SyscallMessage(const char * text): _text(text) {}
    SyscallMessage(const Type & type): _type(type) {}

    Type type() { return _type; }
    void type(Type type) { _type = type; }

    const char * text() { return _text; }

private:
    void * caller;
    Type _type;
    const char * _text;
};

__END_SYS

#endif
