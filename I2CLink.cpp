#include "I2CLink.h"

/*
 * Establish if slave.
 * Set next command and payload used by request callback.
 * And pass in callback to handle received data.
 */


I2CLink::I2CLink(boolean is_begin){
    if(is_begin){
        Wire.begin(WIRE_DEVICE);
    }
}

static void I2CLink::setup_slave(void(*receive_callback)(int), void(*request_callback)()){
    Wire.onReceive(receive_callback);
    Wire.onRequest(request_callback);
}

static void I2CLink::slave_receive_helper(int num_bytes, byte (&cp)[2]){
    byte i = 0;
    while(Wire.available() > 1){
        *(cp+(i%2)) = Wire.read();
        i++;
    }
}

static void I2CLink::master_send_data(byte command, byte payload){
    Wire.beginTransmission(WIRE_DEVICE);
    Wire.write(command);
    Wire.write(payload);
    Wire.endTransmission();
}

static void I2CLink::master_request_data(void(*request_callback)(byte, byte)){
    byte cp[2] = {0, 0};
    byte i = 0;
    Wire.requestFrom(WIRE_DEVICE, 2);
    while(Wire.available()){
        cp[i%2] = Wire.read();        
        i++;
    }
    request_callback(cp[0], cp[1]);
}
