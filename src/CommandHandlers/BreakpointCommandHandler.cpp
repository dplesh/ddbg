#include <string>
#include <algorithm>
#include <cstdint>
#include <stdint.h>
#include "CommandHandler.cpp"
#include "../Components/Breakpoint.cpp"
#include "../stringExt.cpp"
#include "../ProgramInfo.cpp"

class BreakpointCommandHandler : public CommandHandler {
    public:
        BreakpointCommandHandler(std::vector<std::string>* compatibleCommands) 
            : CommandHandler(compatibleCommands) {}
        void handle(const ProgramInfo programInfo, const std::vector<std::string> params);    
        bool isCommandCompatible(std::string command) override;
    
    private:
        std::vector<Breakpoint> breakpoints;
    
    protected:
        std::string t_unsetBreakpointCommand;
};

bool BreakpointCommandHandler::isCommandCompatible(std::string command){
    
}


void BreakpointCommandHandler::handle(const ProgramInfo programInfo, const std::vector<std::string> params){

}   