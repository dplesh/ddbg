#include <string>
#include <algorithm>
#include "CommandHandler.cpp"
#include "../stringExt.cpp"
#include <cstdint>
#include <stdint.h>
#include "../ProgramInfo.cpp"

class ContinueCommandHandler : public CommandHandler {
    public:
        ContinueCommandHandler();
        bool isCommandCompatible(std::string command);
        std::string getCompatibleCommand();
        void handle(ProgramInfo* programInfo, std::vector<std::string> params);
    
    private:
        std::string t_compatibleCommand;        
};

ContinueCommandHandler::ContinueCommandHandler(){
    t_compatibleCommand = "continue";
}

std::string ContinueCommandHandler::getCompatibleCommand(){
    return t_compatibleCommand;
}

bool ContinueCommandHandler::isCommandCompatible(std::string command){
    std::string loweredCommand = command;
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    return is_prefix(command, t_compatibleCommand);
}

void ContinueCommandHandler::handle(ProgramInfo* programInfo, std::vector<std::string> params){
    std::string command = params[0];
    
    if (!isCommandCompatible(command)){
        throw "Command " + command + "is not compatible with ContinueCommandHandler";
    }
    
    int pid = programInfo->pid;

    ptrace(PTRACE_CONT, pid, nullptr, nullptr);

    int wait_status;
    auto options = 0;
    waitpid(pid, &wait_status, options);



}