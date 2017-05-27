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
    while(Wire.available() > 1){
        cp[i%2] = Wire.read();
        i++;
    }
}

void I2CLink::master_send_data(byte command, byte payload){
    Wire.beginTransmission(WIRE_DEVICE);
    Wire.write(command);
    Wire.write(payload);
    Wire.endTransmission();
}

void I2CLink::master_request_data(void(*request_callback)(byte, byte)){
    byte cp[2] = {0, 0};
    byte i = 0;
    Wire.requestFrom(WIRE_DEVICE, 2);
    while(Wire.available()){
        cp[i%2] = Wire.read();        
        i++;
    }
    request_callback(cp[0], cp[1]);
}
