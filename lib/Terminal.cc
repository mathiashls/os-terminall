#include "Terminal.h"
#include <unistd.h>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <pwd.h>


using namespace std;

Terminal::Terminal() {

    _my_pid = getpid();
    _parent = getppid();

}

Terminal::~Terminal() {

    // Mathias doesn't support self-destruction behavior

}

int Terminal::run() {

    int aux=0, status;
    string cmdline;
    bool lock;
    vector<string> stuart; // Don't mess with Stuart, he own all your cmd information. Powerful fella.
  
    do {

        stuart.clear();
        bool list = false;
        char hostname[100];
        gethostname(hostname, 100);

        /* 
         *    Getting the User's login - Optional
         *
         *    Some Linux distro may show some problems working with getlogin() depending on
         *    the OS features. This code was implemented on a Arch Linux BSPWM, so the 
         *    alternative way to receive the user's login is using the getuid() method.
         */

 
        struct passwd *p;
        uid_t  uid;
        p = getpwuid(uid = getuid());
 
        do {

            cout << "[" << p->pw_name << "@" << hostname << " ~]$ ";
            getline(cin, cmdline);

        } while(cmdline=="");

        cmdline = trim(cmdline); 
        int cmd_size = cmdline.size();
        lock = ultranizer(cmdline, &stuart);

        // Now, we take care about what the user want to do

        if(stuart[0] == "quit" || stuart[0] == "exit") {
      
            exit(0);

        }

        if(stuart[0] == "hbottom") {

            if(not _processes.empty()) {

                showMap();

            }
  
        } else { 

            Process proc(stuart[0], stuart, lock);

            if(lock == false) {

                _processes.insert(make_pair(proc.pid(), &proc));

            }

        }

    } while(true);

}

void Terminal::showMap() {

    ProcessMap::iterator tracker = _processes.begin();

    system("clear");
    cout << " PID   User  " << endl << endl;

    do {

        cout << tracker->first << "   " << tracker->second->name << endl;
        tracker++;

    } while(tracker != _processes.end()); 

}

// Trim code by arliones 
// HERE IS HOW TO TRIM SPACES FROM THE BORDERS OF A STRING
string Terminal::trim(string& str) {

    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));

}

bool Terminal::ultranizer(string cmd, std::vector<string> * tokens) {

    /*
     *   Ultranizer - The tolkenizer, ultra implemented
     *
     *   This function do what a tokenizer must do, and more.
     *   Break the string into tokens and push it all inside the vector.
     *   If the last char of the vector is a '&', the ultranizer delete 
     *   it and return false.
     */
 
    int aux = 0; 

    for(int i=0; i<cmd.size(); i=aux-1) {
       
        int pos = cmd.find(" ", aux);
        string foo = cmd.substr(aux, pos-aux);
        tokens->push_back(foo);
        aux = pos + 1;
     
    }

    if(tokens->back() == "&") {

        tokens->pop_back();
        return false;

    } else return true;

}
