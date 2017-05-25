#ifndef I2CLINK_H
#define I2CLINK_H

#define WIRE_DEVICE 8

class I2CLink {
  public:
    I2CLink(boolean is_slave, void(*ptake_action)(byte, byte));
    void setup();
    next_slave_send(byte command, byte payload);
    void master_send_data(byte *command, byte *payload);
    void master_request_data();
    byte slave_send_command;
    byte slave_send_payload;
    byte slave_received_command;
    byte slave_received_payload;
  private:
    void slave_receive_data(int num_bytes);
    void slave_send_data();
    void(*take_action)(byte, byte);
    boolean is_slave;
};

#endif
