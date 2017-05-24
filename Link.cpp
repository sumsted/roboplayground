#include "Link.h"
#include "Wire.h"

#define WIRE_DEVICE 8

class Link {
  public:
    Link(int pwire, void(*ptake_action)(*char));
    void setup();
    next_slave_send(byte command, byte payload);
  private:
    void slave_receive_data(int num_bytes);
    void master_send_data(byte *command, byte *payload);
    void master_request_data();
    void slave_send_data();
    void(*take_action)(byte, byte);
    byte next_command;
    byte next_payload;
    boolean is_slave;
};


/*
 * Establish if slave.
 * Set next command and payload used by request callback.
 * And pass in callback to handle received data.
 */
Link::Link(boolean pis_slave, void(*ptake_action)(byte, byte)){
    take_action = take_action;
    next_command = 0;
    next_payload = 0;
    is_slave = pis_slave;
}

/*
 * Attach to i2c device. If slave set callbacks.
 */
void Link::setup(){
    Wire.begin(WIRE_DEVICE);
    if(is_slave){
        Wire.onReceive(slave_receive_data);
        Wire.onRequest(slave_send_data);
    }
}
/*
 * Master sends and receives data synchronously.
 * Meaning blocked until slave handles request.
 */
void Link::master_send_data(byte command, byte payload){
    Wire.beginTransmission(WIRE_DEVICE);
    Wire.write(command);
    Wire.write(payload);
    Wire.endTransmission();
}

void Link::master_request_data(){
    int cp[2] = {0, 0};
    Write.requestFrom(WIRE_DEVICE, 2);
    while(Wire.available()){
        cp[i%2] = Wire.read();        
    }
    take_action(cp[0], cp[1]);
}

/*
 * Slave handles sends and receives asynchronously.
 * These callbacks are set in setup().
 */
void Link::slave_receive_data(int num_bytes){
    int cp[2] = {0, 0};
    i = 0;
    while(Wire.available() > 1){
        cp[i%2] = Wire.read();
    }
    take_action(cp[0], cp[1]);
}

void Link::next_slave_send(byte command, byte payload){
    next_command = command;
    next_payload = payload;
}

void Link::slave_send_data(){
    Wire.write(next_command);
    Wire.write(next_payload);
}