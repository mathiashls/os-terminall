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

  int cmd_size, aux=0, status;
  string cmdline;
  bool lock, loop = true;
  vector<string> vic;
  
  do {

    vic.clear();
    bool list = false;
    char hostname[255];
    gethostname (hostname, 255);

    struct passwd *p;
    uid_t  uid;
    p = getpwuid(uid = getuid());
 
  
    cout << "[" << p->pw_name << "@" << hostname << " ~]$ ";
    getline(cin, cmdline);

    cmdline = trim(cmdline);

    cmd_size = cmdline.size();

    if(cmdline[cmd_size-1] == '&'){
      
      lock = false;
    
    } else {
    
      lock = true;
  
    } 

    for(int i=0; i<cmdline.size(); i=aux-1) {
    
      int pos = cmdline.find(" ", aux);
      string foo = cmdline.substr (aux, pos-aux);
      vic.push_back(foo);
      aux = pos + 1;
 
    }

    if(vic[0] == "quit" || vic[0] == "exit") {
      
      exit(0);

    } 

    if(lock == false) {

      int foo = vic.size();
      vic[foo-1].clear();

    }

    Process proc(vic[0], vic, lock);
     
  } while(loop==true);

}



// Trim code by arliones 
// HERE IS HOW TO TRIM SPACES FROM THE BORDERS OF A STRING
string Terminal::trim(string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}
