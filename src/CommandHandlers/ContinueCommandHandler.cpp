#include <string>
#include <cstdint>
#include <stdint.h>
#include "CommandHandler.cpp"
#include "../ProgramInfo.cpp"

class ContinueCommandHandler : public CommandHandler {
    public:
        ContinueCommandHandler(std::vector<std::string>* compatibleCommands) 
            : CommandHandler(compatibleCommands) {}
        
        ContinueCommandHandler(std::string command)
            : CommandHandler(command) {}
        
        void handle(const ProgramInfo programInfo, std::vector<std::string> params);
};

void ContinueCommandHandler::handle(const ProgramInfo programInfo, std::vector<std::string> params){
    std::string command = params[0];
    
    if (!isCommandCompatible(command)){
        throw "Command " + command + "is not compatible with ContinueCommandHandler";
    }
    
    int pid = programInfo.pid;

    ptrace(PTRACE_CONT, pid, nullptr, nullptr);

    int wait_status;
    auto options = 0;
    waitpid(pid, &wait_status, options);
}