// EPOS Component Declarations

#ifndef __stub_segment_h
#define __stub_segment_h

#include <architecture.h>
#include <syscall/message.h>
#include <memory.h>

__BEGIN_API

__USING_UTIL

class Stub_Shared_Segment
{
private:
    int id;
    typedef _SYS::Message Message;
    typedef _SYS::Shared_Segment Shared_Segment;
    typedef _SYS::Segment Segment;

public:

    Stub_Shared_Segment(){}

    void set_id(int _id) {id = _id;}
    
    Stub_Shared_Segment(unsigned int port, unsigned int bytes, const Flags & flags) {
        Message * msg = new Message(0, Message::ENTITY::SHARED_SEGMENT, Message::SHARED_SEGMENT_CREATE, port, bytes, flags);
        msg->act();
        id = msg->result();
    }

    Shared_Segment * get_sseg(unsigned int port) {
        Message * msg = new Message(0, Message::ENTITY::SHARED_SEGMENT, Message::SHARED_SEGMENT_GET_SSEG, port);
        msg->act();
        return msg->result();
    }
    
};

__END_API

#endif
