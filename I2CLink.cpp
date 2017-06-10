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

void I2CLink::slave_receive_helper(I2CPayload &payload){
    byte i;
    byte p[I2C_PAYLOAD_LENGTH];
    if(Wire.available()){
        for(i=0;i<I2C_PAYLOAD_LENGTH;i++){
            p[i] = Wire.read();
        }
        payload.set_payload(p);
    }
}

void I2CLink::slave_send_helper(I2CPayload &payload){
    int i;
    byte p[I2C_PAYLOAD_LENGTH];
    payload.get_payload(p);
    for(i=0;i<I2C_PAYLOAD_LENGTH;i++){
        Wire.write(p[i]);
    }
}

void I2CLink::master_send_payload(I2CPayload &payload){
    int i;
    byte p[I2C_PAYLOAD_LENGTH];
    payload.get_payload(p);
    Wire.beginTransmission(WIRE_DEVICE);
    for(i=0;i<I2C_PAYLOAD_LENGTH;i++){
        Wire.write(p[i]);
    }
    Wire.endTransmission();
}

void I2CLink::master_request_payload_callback(void(*request_callback)(I2CPayload &payload)){
    byte i;
    byte p[I2C_PAYLOAD_LENGTH];
    I2CPayload payload;
    Wire.requestFrom(WIRE_DEVICE, I2C_PAYLOAD_LENGTH);
    if(Wire.available()){
        for(i=0;i<I2C_PAYLOAD_LENGTH;i++){
            p[i] = Wire.read();
        }
        payload.set_payload(p);
    }
    request_callback(payload);
}

void I2CLink::master_request_payload(I2CPayload &payload){
    byte i;
    byte p[I2C_PAYLOAD_LENGTH];
    Wire.requestFrom(WIRE_DEVICE, I2C_PAYLOAD_LENGTH);
    if(Wire.available()){
        for(i=0;i<I2C_PAYLOAD_LENGTH;i++){
            p[i] = Wire.read();
        }
        payload.set_payload(p);
    }
}
