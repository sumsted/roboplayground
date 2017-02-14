#include "SubSystems.h"

class SerialController {
    public:
        // bt serial
        // command GET RUN RESET START
        // run mod device MOTOR JOYSTICK RGDLED SERVO SEVSEG LEDMATRIX LIGHT_SENSOR IR
        // SHUTTER DIGITAL PWM TONE SERVO_PIN TIMER
        SerialController(SubSystems &ss);
        void serial_handler();
    private:
        union{
            byte byteVal[2];
            short shortVal;
        }valShort;
        char command;
        int action;
        int device;
        char index;
        char buffer[52];
        SubSystems ss;
        void route_command();
        void read_sensor();
        void run_module();
        void call_ok();
        void write_serial(unsigned char c);
        void write_end();
        unsigned char read_buffer(char index);
        void write_buffer(char index, unsigned char c);
        short readShort(int idx);
}