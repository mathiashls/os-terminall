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
 
  
    cout << "[" << p->pw_name << "@" << hostname << " ~]$ ";
    getline(cin, cmdline);

    cmdline = trim(cmdline); // Using trim function to take off the trash in the begin and final of the string

    int cmd_size = cmdline.size();

    if(cmdline[cmd_size-1] == '&') {

      lock = false;

    } else {

      lock = true;
  
    }

    tokenizer(cmdline, &stuart);

    

    // Now, we take care about what the user want to do

    if(stuart[0] == "quit" || stuart[0] == "exit") {
      
      exit(0);

    } 

    Process proc(stuart[0], stuart, lock);
     
  } while(true);

}



// Trim code by arliones 
// HERE IS HOW TO TRIM SPACES FROM THE BORDERS OF A STRING
string Terminal::trim(string& str) {

    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

void Terminal::tokenizer(string cmd, std::vector<string> * tokens) {

  int aux = 0; 

  for(int i=0; i<cmd.size(); i=aux-1) {
       
    int pos = cmd.find(" ", aux);
    string foo = cmd.substr(aux, pos-aux);
    tokens->push_back(foo);
    aux = pos + 1;
     
  }

}
