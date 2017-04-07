#pragma once
#include <string>
#include <vector>
#include "../ProgramInfo.cpp"

class CommandHandler {
    public:
        virtual bool isCommandCompatible(std::string command) = 0;
        virtual std::string getCompatibleCommand() = 0;
        virtual void handle(ProgramInfo* programInfo, std::vector<std::string> params) = 0;
};