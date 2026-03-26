#ifndef CONNECTION_H
#include "Connection.h"
#endif

typedef Connection<char> Connection_t;
typedef typename Connection_t::command command_t;


#include <iostream>

using namespace std;

int main(int argc, const char** argv) {

  command_t cmd0("ls -a");
  command_t cmd1("grep -i connection");

  cout << "Piped commands: " << (cmd0 | cmd1) << '\n';

  cout << "Run commands:   " << (cmd0 | cmd1) << '\n';
  Connection_t con;
  con.run(cmd0 | cmd1);

  return 0;
}
