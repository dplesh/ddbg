#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "../ProgramInfo.cpp"
#include "../stringExt.cpp"

class CommandHandler {
    public:
        CommandHandler(std::vector<std::string>* compatibleCommands)
            : t_compatibleCommands(compatibleCommands) {}

        CommandHandler(std::string compatibleCommand)
        {
            std::vector<std::string> commands(1);
            commands[0] = compatibleCommand;
            t_compatibleCommands = &commands;
        }
        
        CommandHandler()
            : t_compatibleCommands{} {}
        
        virtual bool isCommandCompatible(std::string command);
        virtual void handle(const ProgramInfo programInfo, std::vector<std::string> params) = 0;

    protected:
        std::vector<std::string>* t_compatibleCommands;


};


bool CommandHandler::isCommandCompatible(std::string command){
    for (std::string compatibleCommand : *t_compatibleCommands){
        std::string loweredCommand = command;
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        if (is_prefix(command, compatibleCommand)){
            return true;
        }
    }
    return false;
    
}