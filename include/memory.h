// EPOS Memory Declarations

#ifndef __memory_h
#define __memory_h

#include <architecture.h>

__BEGIN_SYS


class Address_Space: MMU::Directory
{
    friend class Init_System;   // for Address_Space(pd)
    friend class Thread;        // for Address_Space(pd)
    friend class Scratchpad;    // for Address_Space(pd)
    friend class Task;          // for activate()

//private:
public:
    using MMU::Directory::activate;

public:
    typedef CPU::Phy_Addr Phy_Addr;
    typedef CPU::Log_Addr Log_Addr;

public:
    Address_Space();
    Address_Space(MMU::Page_Directory * pd);
    ~Address_Space();

    using MMU::Directory::pd;

    Log_Addr attach(Segment * seg);
    Log_Addr attach(Segment * seg, Log_Addr addr);
    void detach(Segment * seg);
    void detach(Segment * seg, Log_Addr addr);

    Phy_Addr physical(Log_Addr address);
};


class Segment: public MMU::Chunk
{
    friend class Thread;        // for Segment(pt)

private:
    typedef MMU::Chunk Chunk;

public:
    typedef CPU::Phy_Addr Phy_Addr;
    typedef MMU::Flags Flags;

public:
    Segment(unsigned int bytes, Flags flags = Flags::APP);
    Segment(Phy_Addr phy_addr, unsigned int bytes, Flags flags);
    ~Segment();

    unsigned int size() const;
    Phy_Addr phy_address() const;
    int resize(int amount);

private:
    Segment(Phy_Addr pt, unsigned int from, unsigned int to, Flags flags): Chunk(pt, from, to, flags) {
        db<Segment>(TRC) << "Segment(pt=" << pt << ",from=" << from << ",to=" << to << ",flags=" << flags << ") [Chunk::pt=" << Chunk::pt() << ",sz=" << Chunk::size() << "] => " << this << endl;
    }
};

class Shared_Segment_Port
{
public:
    Shared_Segment_Port(unsigned int p, Shared_Segment * s) : port(p), sseg(s) {}
    unsigned int port;
    Shared_Segment * sseg;
};

class Shared_Segment: public Segment
{
private:
    typedef MMU::Chunk Chunk;

public:
    typedef Port_List<Shared_Segment_Port> List;
    typedef CPU::Phy_Addr Phy_Addr;
    typedef MMU::Flags Flags;

public:
    Shared_Segment(unsigned int port, unsigned int bytes, const Flags & flags);
    static Shared_Segment * get_sseg(unsigned int port);
    static List _list;
    unsigned int _tasks;
    unsigned int _port;
};

__END_SYS

#endif
