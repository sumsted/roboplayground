#include "I2CPayload.h"

I2CPayload::I2CPayload(){
    this->reset();
    this->payload[I2C_VALUE_TYPE_POSITION] = I2C_VALUE_TYPE_INT;
}

I2CPayload::I2CPayload(byte value_type){
    this->reset();
    this->payload[I2C_VALUE_TYPE_POSITION] = value_type;
}

I2CPayload::I2CPayload(byte command, byte value_type){
    this->reset();
    this->payload[I2C_COMMAND_POSITION] = command;
    this->payload[I2C_VALUE_TYPE_POSITION] = value_type;
}

void I2CPayload::reset(){
    byte i;
    for(i=0;i<I2C_PAYLOAD_LENGTH;i++){
        this->payload[i] = 0;
    }
}

void I2CPayload::reset_value(){
    byte i;
    for(i=I2C_VALUE_POSITION;i<I2C_PAYLOAD_LENGTH;i++){
        this->payload[i] = 0;
    }
}

byte I2CPayload::get_payload(byte (&value)[I2C_PAYLOAD_LENGTH]){
    byte i;
    for(i=0;i<I2C_PAYLOAD_LENGTH;i++){
        value[i] = payload[i];
    }
    return 0;
}

byte I2CPayload::set_payload(byte (&value)[I2C_PAYLOAD_LENGTH]){
    byte i;
    for(i=0;i<I2C_PAYLOAD_LENGTH;i++){
        payload[i] = value[i];
    }
    return 0;
}

void I2CPayload::set_command(byte command){
    this->payload[I2C_COMMAND_POSITION] = command;
}

void I2CPayload::set_value_type(byte value_type){
    this->payload[I2C_VALUE_TYPE_POSITION] = value_type;
}

byte I2CPayload::get_command(){
    return this->payload[I2C_COMMAND_POSITION];
}

byte I2CPayload::get_value_type(){
    return this->payload[I2C_VALUE_TYPE_POSITION];
}

byte I2CPayload::set_int(byte position, int value){
    HostNetworkInt ni;
    byte i;
    byte payload_index = I2C_VALUE_POSITION + position * 4;
    if(payload_index < I2C_VALUE_POSITION || payload_index >= I2C_PAYLOAD_LENGTH){
        return -1;
    }
    ni.val = value;
    htonl(ni.val);
    for(i=0; i<4; i++, payload_index++){
        this->payload[payload_index] = ni.pieces[i];
    }
    return 0;
}

byte I2CPayload::set_ints(int (&value)[I2C_VALUE_INT_MAX]){
    HostNetworkInt ni;
    byte v, i;
    byte payload_index = I2C_VALUE_POSITION;
    for(v=0; v<I2C_VALUE_INT_MAX; v++){
        ni.val = value[v];
        htonl(ni.val);
        for(i=0; i<4; i++, payload_index++){
            this->payload[payload_index] = ni.pieces[i];
        }
    }
    return 0;
}

byte I2CPayload::set_byte(byte position, byte value){
    byte i;
    byte payload_index = I2C_VALUE_POSITION + position;
    if(payload_index < I2C_VALUE_POSITION || payload_index >= I2C_PAYLOAD_LENGTH){
        return -1;
    }
    this->payload[payload_index] = value;
    return 0;
}

byte I2CPayload::set_bytes(byte (&value)[I2C_VALUE_BYTE_MAX]){
    byte i;
    byte payload_index = I2C_VALUE_POSITION;
    for(i=0; i<I2C_VALUE_BYTE_MAX; i++, payload_index++){
        this->payload[payload_index] = value[i];
    }
    return 0;
}

byte I2CPayload::get_int(byte position, int &value){
    HostNetworkInt hi;
    byte i;
    byte payload_index = I2C_VALUE_POSITION + position * 4;
    if(payload_index < I2C_VALUE_POSITION || payload_index >= I2C_PAYLOAD_LENGTH){
        return -1;
    }
    for(i=0; i<4; i++, payload_index++){
        hi.pieces[i] = this->payload[payload_index];
    }
    ntohl(hi.val);
    value = hi.val;
    return 0;    
}

int I2CPayload::get_int(byte position){
    HostNetworkInt hi;
    byte i;
    byte payload_index = I2C_VALUE_POSITION + position * 4;
    if(payload_index < I2C_VALUE_POSITION || payload_index >= I2C_PAYLOAD_LENGTH){
        return 0;
    }
    for(i=0; i<4; i++, payload_index++){
        hi.pieces[i] = this->payload[payload_index];
    }
    ntohl(hi.val);
    return hi.val;
}

byte I2CPayload::get_ints(int (&value)[I2C_VALUE_INT_MAX]){
    HostNetworkInt hi;
    byte i, v;
    byte payload_index = I2C_VALUE_POSITION;
    for(v=0; v<I2C_VALUE_INT_MAX; v++){
        for(i=0; i<4; i++, payload_index++){
            hi.pieces[i] = this->payload[payload_index];
        }
        ntohl(hi.val);
        value[v] = hi.val;
    }
    return 0;    
}

byte I2CPayload::get_byte(byte position, byte &value){
    byte i;
    byte payload_index = I2C_VALUE_POSITION + position;
    if(payload_index < I2C_VALUE_POSITION || payload_index >= I2C_PAYLOAD_LENGTH){
        return -1;
    }
    value = payload[position];
    return 0;    
}

byte I2CPayload::get_bytes(byte (&value)[I2C_VALUE_BYTE_MAX]){
    byte i;
    byte payload_index = I2C_VALUE_POSITION;
    for(i=0;i<I2C_VALUE_BYTE_MAX;i++, payload_index++){
        value[i] = payload[payload_index];
    }
    return 0;
}