/*
 * CC-BY-SA 3.0 by Maker Works Tech Co., Ltd, www.makeblock.cc
 * Modified from mbot factory firmware
 */
#include "SubSystems.h"


#define GET 1
#define RUN 2
#define RESET 4
#define START 5
#define ULTRASONIC_SENSOR 1
#define MOTOR 10
#define RGBLED 8
#define TONE 34

class SerialController {
    public:
        SerialController(SubSystems &ss);
        void serial_handler();
    private:
        union{
            byte byte_val[2];
            short short_val;
        }val_short;
        union{
            byte byte_val[4];
            float float_val;
            long long_val;
        }val;
        unsigned char prevc;
        boolean is_available;
        char command;
        int action;
        int device;
        char index;
        char buffer[52];
        boolean is_start;
        byte data_len;
        uint8_t command_index;
        char serial_read;

        SubSystems ss;

        void route_command();
        void read_serial();
        void read_sensor(int device);
        void run_module(int device);
        void call_ok();
        void write_head();
        void write_serial(unsigned char c);
        void write_end();
        unsigned char read_buffer(char index);
        void write_buffer(char index, unsigned char c);
        short read_short(int idx);
        void send_float(float value);
};