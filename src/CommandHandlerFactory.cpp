#pragma once

#include <string>
#include "CommandHandlers/CommandHandler.cpp"

class CommandHandlerFactory {
    public:
        CommandHandlerFactory(CommandHandler* handlers)
            : commandHandlers(handlers) {}
        CommandHandler* getHandler(std::string command);

    private:
        CommandHandler* commandHandlers;
};