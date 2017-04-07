#pragma once
#include <string>
#include <sys/types.h>

struct ProgramInfo {
    std::string programName;
    pid_t pid;
};