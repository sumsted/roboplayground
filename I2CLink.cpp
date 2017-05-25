#include "I2CLink.h"

/*
 * Establish if slave.
 * Set next command and payload used by request callback.
 * And pass in callback to handle received data.
 */
I2CLink::I2CLink(boolean pis_slave, void(*ptake_action)(byte, byte)){
    is_slave = pis_slave;
    take_action = ptake_action;
    slave_send_command = 0;
    slave_send_payload = 0;
    wire = new Wire.begin(WIRE_DEVICE);
    if(is_slave){
        wire->onReceive(slave_receive_data);
        wire->onRequest(slave_send_data);
    }
}

/*
 * Master sends and receives data synchronously.
 * Meaning blocked until slave handles request.
 */
void I2CLink::master_send_data(byte command, byte payload){
    wire->beginTransmission(WIRE_DEVICE);
    wire->write(command);
    wire->write(payload);
    wire->endTransmission();
}

void I2CLink::master_request_data(){
    int cp[2] = {0, 0};
    Write.requestFrom(WIRE_DEVICE, 2);
    while(wire->available()){
        cp[i%2] = wire->read();        
    }
    take_action(cp[0], cp[1]);
}

/*
 * Slave handles sends and receives asynchronously.
 * These callbacks are set in setup().
 */
void I2CLink::slave_receive_data(int num_bytes){
    int cp[2] = {0, 0};
    byte i = 0;
    while(wire->available() > 1){
        cp[i%2] = wire->read();
        i++;
    }
    slave_received_command = cp[0];
    slave_received_payload = cp[1];
    take_action(cp[0], cp[1]);
}

void I2CLink::slave_send_data(){
    wire->write(slave_send_command);
    wire->write(slave_send_payload);
}