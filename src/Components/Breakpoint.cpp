#pragma once

#include <stdint.h>

class Breakpoint {
    public:
        Breakpoint(pid_t processId, std::intptr_t addr)
            : pid{processId}, address{addr}, enabled{false}, originalData{}
        {}

        void enable();
        void disable();

        auto isEnabled() const -> bool {return enabled;}
        auto getAddress() const -> std::intptr_t {return address;}

    private:
        pid_t pid;
        std::intptr_t address;
        bool enabled;
        uint8_t originalData;
};

void Breakpoint::enable(){
    long data = ptrace(PTRACE_PEEKDATA, pid, address, nullptr);
    originalData = static_cast<uint8_t> (data & 0xff);
    uint64_t int3 = 0xcc;
    uint64_t int3data = ((data & ~0xff) | int3);
    ptrace(PTRACE_POKEDATA, pid, address, int3data);

    enabled = true;

}

void Breakpoint::disable(){
    long data = ptrace(PTRACE_PEEKDATA, pid, address, nullptr);
    uint64_t restoredData = ((data & ~0xff) | originalData);
    ptrace(PTRACE_POKEDATA, pid, address, restoredData);

    enabled - false;
}