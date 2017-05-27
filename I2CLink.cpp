#include "I2CLink.h"

I2CLink::I2CLink(){
}

void I2CLink::begin(boolean is_slave){
    if(is_slave){
        Wire.begin(WIRE_DEVICE);
    }else{
        Wire.begin();
    }
}

void I2CLink::setup_slave(void(*receive_callback)(int), void(*request_callback)()){
    Wire.onReceive(receive_callback);
    Wire.onRequest(request_callback);
}

void I2CLink::end(){
    Wire.end();
}

void I2CLink::slave_receive_helper(int num_bytes, byte (&cp)[2]){
    byte i = 0;
    if(Wire.available() > 1){
        cp[0] = Wire.read();
        cp[1] = Wire.read();
    }
}

void I2CLink::master_send_data(byte command, byte payload){
    Wire.beginTransmission(WIRE_DEVICE);
    Wire.write(command);
    Wire.write(payload);
    Wire.endTransmission();
}

void I2CLink::master_request_data_cb(void(*request_callback)(byte, byte)){
    byte c=0;
    byte p=0;
    Wire.requestFrom(WIRE_DEVICE, 2);
    if(Wire.available()){
        c = Wire.read();
        p = Wire.read();
    }
    request_callback(c, p);
}

void I2CLink::master_request_data(byte(&cp)[2]){
    Wire.requestFrom(WIRE_DEVICE, 2);
    if(Wire.available()){
        cp[0] = Wire.read();
        cp[1] = Wire.read();
    }
}
