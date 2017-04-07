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


class Debugger {
    public:
        Debugger(std::string programName, pid_t processId)
            : program_name{std::move(programName)}, pid(processId), commandHandlerFactory{initCommandHandlerFactory()} {}
        void run();

    private:
        std::string program_name;
        pid_t pid;
        CommandHandlerFactory* commandHandlerFactory;
        
        CommandHandlerFactory* initCommandHandlerFactory();
        void handleCommand(char* command);
        void continue_execution();
};


void Debugger::run(){
    int wait_status;
    int options = 0;
    waitpid(pid, &wait_status, options);
    
    char* line = NULL;
    while ((line = linenoise("ddbg> ")) != nullptr){
        handleCommand(line);
        linenoiseHistoryAdd(line);
        //linenoiseFree(line);
    }
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
    
    if (is_prefix(command, "continue")) {
        continue_execution();
    }   
    else {
        std::cerr << "Unknown command\n";
    }
}

void Debugger::continue_execution(){
    return;
}


