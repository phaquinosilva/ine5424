// EPOS Component Declarations

#ifndef __stub_loader_h
#define __stub_loader_h

#include <architecture.h>
#include <syscall/message.h>
#include <syscall/stub_task.h>

__BEGIN_API

__USING_UTIL

class Stub_Loader
{
private:
    int id;
    typedef _SYS::Message Message;

public:
    Stub_Loader(){}

    int new_app(int off_set, unsigned int addr) {
        Message * msg = new Message(0, Message::ENTITY::LOADER, Message::LOADER_NEW_APP, off_set, addr);
        msg->act();
         
        return msg->result();
    }


};

__END_API

#endif