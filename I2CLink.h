#ifndef I2CLINK_H
#define I2CLINK_H

#include "SubSystems.h"
#include <Wire.h>

/*
 * I2CLink is a helper for I2C communication.
 * Keep the payload simple, only 2 bytes, command, payload.
 * May change payload to int.
 */

#define WIRE_DEVICE 8
/*
 * Wiring UNO
 * Arduino 1        Arduino 2
 *    A4 SDA <----> A4 SDA       Analog
 *    A5 SLC <----> A5 SLC       Clock
 *       GND <----> GND          Ground
 */

// I2C Command
#define I2C_NO_COMMAND 0
#define I2C_MOTOR_1_FORWARD 1
#define I2C_MOTOR_2_FORWARD 2
#define I2C_MOTOR_1_BACKWARD 3
#define I2C_MOTOR_2_BACKWARD 4
#define I2C_ULTRASONIC 5
#define I2C_LED_LEFT 6
#define I2C_LED_RIGHT 7
#define I2C_OPEN_DOOR 8
#define I2C_CLOSE_DOOR 9

// I2C Payload
#define I2C_EMPTY 0
#define I2C_CLOSE 0
#define I2C_OPEN 1
#define I2C_DOWN 0
#define I2C_UP 1

class I2CLink {
  public:
    I2CLink();
    static void begin();
    static void setup_slave(void(*receive_callback)(int), void(*request_callback)());
    static void master_send_data(byte command, byte payload);
    static void master_request_data(void(*request_callback)(byte, byte));
    static void slave_receive_helper(int num_bytes, byte (&cp)[2]);
};

#endif
