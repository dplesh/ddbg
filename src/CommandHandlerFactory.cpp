#pragma once

#include <string>
#include "CommandHandlers/CommandHandler.cpp"
#include <vector>

class CommandHandlerFactory {
    public:
        CommandHandlerFactory(std::vector<CommandHandler*> handlers)
            : commandHandlers(handlers) {}
        CommandHandler* getHandler(std::string command);

    private:
        std::vector<CommandHandler*> commandHandlers;
};

CommandHandler* CommandHandlerFactory::getHandler(std::string command){
    for (CommandHandler* handler : commandHandlers){
        if (handler->isCommandCompatible(command)){
            return handler;
        }
    }
    return nullptr;
}