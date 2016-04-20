#include "Process.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Process::Process(string & program, vector<string> & params, bool block) {

    int pid = fork();
    name = program.c_str();

    if(pid > 0) {

        _my_pid = pid;

    }

    if(pid==-1) {

        cerr << "Erro no fork!" << endl;
        exit(-1);
  
    } else if (pid==0) {

        cout << "Vader, I'm your son!" << endl;
        exec(program, params);

    }

    if(block == true) {

        espera();

    }

    _parent = getppid(); 

}

Process::~Process() {

    // Self-destruction behavior can hurt you

}

int Process::espera() {

    int foo = status();
    wait(&foo);

}

pid_t Process::pid() {

    return _my_pid;

}

int Process::status() {

    return _status;

}

void Process::exec(string & program, vector<string> & params) {

    int pid;
    bool hasPath=false;  
  
    if(program[0]=='/') {

        hasPath == true;

    }

    char * foo[333];  

    for(int i=0; i<params.size(); i++) {

        foo[i] = string_to_c_convert(params[i]);

        if(i+1 == params.size()) {

            foo[i+1] = NULL;
    
        }

    }

    if(hasPath == true) {

        if(execv(foo[0], foo) == -1) {

            cerr << "Erro: comando inexistente (path)." << endl;

        }

        exit(0);

    }

    if(hasPath == false) {

        if(execvp(foo[0], foo) == -1) {

            cerr << "Erro: comando inexistente(no path)." << endl;
 
        }

        exit(0);
 
    }  


}




// HERE IS HOW TO TRANSFORM A vector<string> TO A char * const []
// C++ STD provides a series of algorithms. We will use one of them: transform.
// transform will take a element series from a container (ex. vector) and call
// the function pointer passed as argument to transform each member of the series.
// The result of the transformation is stored in another container.
//
// For instance, to transform all strings in a vector<string> to c-like strings in
// a vector<char*>, use transform like this:
// vector<string> input;
// vector<char *> argv;
// transform(input.begin(), input.end(), back_inserter(argv), string_to_c_convert);
//
// If you need, you can cast the vector<char*> argv to a c-like array of char*:
// char * const * args = &argv[0];

char * Process::string_to_c_convert(const string & s) {

    char *pc = new char[s.size()+1];
    strcpy(pc, s.c_str());
    return pc;

}


