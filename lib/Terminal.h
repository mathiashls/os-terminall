#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <sys/types.h>
#include <map>
#include <string>
#include <vector>
#include "Process.h"

class Terminal {
public:
    Terminal();
    virtual ~Terminal();

    int run();
    pid_t pid();

private:
    std::string trim(std::string& str);
    bool extract_cmd(std::string cmd, std::vector<std::string> * tokens);

    pid_t _my_pid;
    pid_t _parent;
    typedef std::map<pid_t,Process*> ProcessMap;
    ProcessMap _processes;
};

#endif 
