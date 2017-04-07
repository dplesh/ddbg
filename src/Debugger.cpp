#include <sys/types.h>
#include <sys/wait.h>
#include <linenoise.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "CommandHandlerFactory.cpp"
#include "CommandHandlers/CommandHandler.cpp"
#include "CommandHandlers/ContinueCommandHandler.cpp"
#include "stringExt.cpp"
#include "ProgramInfo.cpp"

class Debugger {
    public:
        Debugger(std::string program_name, pid_t processId)
            : programInfo{initProgramInfo(program_name, processId)}, commandHandlerFactory{initCommandHandlerFactory()} {}
        void run();

    private:
        ProgramInfo programInfo;
        CommandHandlerFactory* commandHandlerFactory;
        
        CommandHandlerFactory* initCommandHandlerFactory();
        void handleCommand(char* command);
        static ProgramInfo initProgramInfo(std::string program_name, pid_t proccessId);
};


void Debugger::run(){
    int wait_status;
    int options = 0;
    waitpid(programInfo.pid, &wait_status, options);
    
    char* line = NULL;
    while ((line = linenoise("ddbg> ")) != nullptr){
        handleCommand(line);
        linenoiseHistoryAdd(line);
        //linenoiseFree(line);
    }
}

ProgramInfo Debugger::initProgramInfo(std::string program_name, pid_t processId){
    ProgramInfo programInfo = {program_name, processId};
    return programInfo;
}

CommandHandlerFactory* Debugger::initCommandHandlerFactory(){
    std::vector<CommandHandler*> handlers(1);
    ContinueCommandHandler* contHandler = new ContinueCommandHandler();
    handlers[0] = contHandler;
    return new CommandHandlerFactory(handlers);
}

void Debugger::handleCommand(char* line){
    auto args = split(line, ' ');
    auto command = args[0];
    
    CommandHandler* compatibleHandler = commandHandlerFactory->getHandler(command);
    if (compatibleHandler == nullptr) {
        std::cerr << "Unknown command\n";
        return;
    }
    
    compatibleHandler->handle(programInfo, args);
}


