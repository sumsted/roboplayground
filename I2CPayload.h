#ifndef I2C_PAYLOAD_H
#define I2C_PAYLOAD_H

#include <Arduino.h>

#define htons(x) ( ((x)<< 8 & 0xFF00) | \
                   ((x)>> 8 & 0x00FF) )
#define ntohs(x) htons(x)

#define htonl(x) ( ((x)<<24 & 0xFF000000UL) | \
                   ((x)<< 8 & 0x00FF0000UL) | \
                   ((x)>> 8 & 0x0000FF00UL) | \
                   ((x)>>24 & 0x000000FFUL) )
#define ntohl(x) htonl(x)

#define I2C_COMMAND_POSITION 0
#define I2C_VALUE_TYPE_POSITION 1
#define I2C_VALUE_POSITION 4
#define I2C_PAYLOAD_LENGTH 32
#define I2C_VALUE_INT_MAX 7
#define I2C_VALUE_BYTE_MAX 28
#define I2C_VALUE_TYPE_INT 0
#define I2C_VALUE_TYPE_BYTE 1


union HostNetworkInt{
    long val;
    byte pieces[4];
};

class I2CPayload {
  public:
    I2CPayload();
    I2CPayload(byte value_type);
    I2CPayload(byte command, byte value_type);

    void reset();
    void reset_value();

    byte get_payload(byte (&value)[I2C_PAYLOAD_LENGTH]);
    byte set_payload(byte (&value)[I2C_PAYLOAD_LENGTH]);
    
    void set_command(byte command);
    void set_value_type(byte value_type);
    byte get_command();
    byte get_value_type();

    byte set_int(byte position, int value);
    byte set_ints(int (&value)[I2C_VALUE_INT_MAX]);
    byte set_byte(byte position, byte value);
    byte set_bytes(byte (&value)[I2C_VALUE_BYTE_MAX]);
    byte get_int(byte position, int &value);
    int get_int(byte position);
    byte get_ints(int (&value)[I2C_VALUE_INT_MAX]);
    byte get_byte(byte position, byte &value);
    byte get_bytes(byte (&value)[I2C_VALUE_BYTE_MAX]);
  private:
    byte payload[I2C_PAYLOAD_LENGTH];
};
#endif
