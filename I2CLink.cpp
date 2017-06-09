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

void I2CLink::slave_receive_helper(int num_bytes, byte &command, int &value){
    byte i = 0;
    I2CPayload payload;
    if(Wire.available() > 1){
        command = Wire.read();
        for(i=0;i<4;i++){
            payload.pieces[i] = Wire.read();
        }
        value = ntohl(payload.value);
    }
}

void I2CLink::master_send_data(byte command, int value){
    I2CPayload payload;
    payload.value = htonl(value);
    int i;

    Wire.beginTransmission(WIRE_DEVICE);
    Wire.write(command);
    for(i=0;i<sizeof(payload);i++){
        Wire.write(payload.pieces[i]);
    }
    Wire.endTransmission();
}

void I2CLink::master_request_data_cb(void(*request_callback)(byte, int)){
    byte command=0;
    byte i = 0;
    I2CPayload payload;
    Wire.requestFrom(WIRE_DEVICE, 2);
    if(Wire.available()){
        command = Wire.read();
        for(i=0;i<4;i++){
            payload.pieces[i] = Wire.read();
        }
    }
    request_callback(command, payload.value);
}

void I2CLink::master_request_data(byte &command, int &value){
    Wire.requestFrom(WIRE_DEVICE, 2);
    byte i = 0;
    I2CPayload payload;
    if(Wire.available() > 1){
        command = Wire.read();
        for(i=0;i<4;i++){
            payload.pieces[i] = Wire.read();
        }
        value = ntohl(payload.value);
    }
}
// void I2CLink::ntohl(uint32_t* value) {
//     uint32_t tmp_a = (*value & 0xff000000) >> 24;
//     uint32_t tmp_b = (*value & 0x00ff0000) >> 8;
//     uint32_t tmp_c = (*value & 0x0000ff00) << 8 ;
//     uint32_t tmp_d = (*value & 0x000000ff) << 24;
//     *value = tmp_d | tmp_c |tmp_b | tmp_a;
// }
