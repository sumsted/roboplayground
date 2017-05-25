#ifndef I2CLINK_H
#define I2CLINK_H

#include "SubSystems.h"
#include <utility/Wire.h>

#define WIRE_DEVICE 8

// I2C Command
#define I2C_PING 0
#define I2C_MOTOR_1_FORWARD 1
#define I2C_MOTOR_2_FORWARD 2
#define I2C_MOTOR_1_BACKWARD 3
#define I2C_MOTOR_2_BACKWARD 4
#define I2C_ULTRASONIC 5
#define I2C_LED_LEFT 6
#define I2C_LED_RIGHT 7

// I2C Payload
#define I2C_EMPTY 0

class I2CLink {
  public:
    I2CLink(boolean is_slave, void(*ptake_action)(byte, byte));
    void master_send_data(byte *command, byte *payload);
    void master_request_data();
    byte slave_send_command;
    byte slave_send_payload;
    byte slave_received_command;
    byte slave_received_payload;
  private:
    void slave_receive_data(int num_bytes);
    void slave_send_data();
    void(*take_action)(byte, byte);
    boolean is_slave;
    Wire *wire;
};

#endif
