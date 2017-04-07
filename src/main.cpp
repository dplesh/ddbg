#include <iostream>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include "Debugger.cpp"


int main(int argc, char* argv[]){
    if (argc < 2){
        std::cerr << "Please specify program to debug.";
        return -1;
    }

    std::string programName = argv[1];
    pid_t pid = fork();

    if (pid == 0){
        // child process
        ptrace(PTRACE_TRACEME,0, nullptr, nullptr);
        execl(programName.c_str(), programName.c_str(), nullptr);
    }
    else if (pid >= 1){
        // parent process
        Debugger dbg(programName, pid);
        dbg.run();
    }

}