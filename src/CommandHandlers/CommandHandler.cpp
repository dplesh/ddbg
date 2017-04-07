#pragma once
#include <string>

class CommandHandler {
    public:
        virtual bool isCommandCompatible(std::string command) = 0;
        virtual std::string getCompatibleCommand() = 0;
        virtual void handle(std::string command, void** params) = 0;
};