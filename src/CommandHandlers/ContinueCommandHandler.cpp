#include <string>
#include <algorithm>
#include "CommandHandler.cpp"
#include "../stringExt.cpp"
#include <cstdint>
#include <stdint.h>

class ContinueCommandHandler : public CommandHandler {
    public:
        ContinueCommandHandler();
        bool isCommandCompatible(std::string command);
        std::string getCompatibleCommand();
        void handle(std::string command, void** params);
    
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

void ContinueCommandHandler::handle(std::string command, void** params){
    if (!isCommandCompatible(command)){
        throw "Command " + command + "is not compatible with ContinueCommandHandler";
    }
    intptr_t castedParams = (intptr_t) params[0];
    int pid = castedParams;

    ptrace(PTRACE_CONT, pid, nullptr, nullptr);

    int wait_status;
    auto options = 0;
    waitpid(pid, &wait_status, options);



}