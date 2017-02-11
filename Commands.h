#ifndef COMMANDS_H
#define COMMANDS_H

#include "SubSystems.h"

class Commands {
  public:
    Commands(SubSystems &ss);
    void command_a(boolean is_master);
    void command_b();
    void command_c();
    void command_d();        
    void master_command(String command);
    void slave_acknowledge();
    void startup_sequence();
  private:
    SubSystems ss;
};
#endif
