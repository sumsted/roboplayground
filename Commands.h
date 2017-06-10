#ifndef COMMANDS_H
#define COMMANDS_H

#include "SubSystems.h"
#include "I2CLink.h"

class Commands {
  public:
    Commands(SubSystems &ss);
    void command_a(boolean is_master);
    void command_b(boolean is_master);
    void command_c();
    void master_command(String command);
    void slave_acknowledge();
    void startup_sequence();
    void i2c_command(I2CPayload &command_payload, I2CPayload &result_payload);
    void i2c_master_command(boolean is_master, byte command, int value);
  private:
    SubSystems ss;
};
#endif
