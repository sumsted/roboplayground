#include "SerialController.h"

SerialController::SerialController(SubSystems &ssr){
    ss = ssr;
    is_available = false;
    prevc = 0;
    index = 0;
    is_start = false;
    data_len = 0;
    command_index = 0;
}

void SerialController::serial_handler(){
    read_serial();
    if(is_available){
        unsigned char c = serial_read&0xff;
        if(c==0x55&&is_start==false){
            if(prevc==0xff){
            index=1;
            is_start = true;
            }
        }else{
            prevc = c;
            if(is_start){
                if(index==2){
                    data_len = c; 
                }else if(index>2){
                    data_len--;
                }
                write_buffer(index,c);
            }
        }
        index++;
        if(index>51){
            index=0; 
            is_start=false;
        }
        if(is_start&&data_len==0&&index>3){ 
            is_start = false;
            route_command(); 
            index=0;
        }
    }    
}

void SerialController::read_serial(){
  is_available = false;
  if(Serial.available()>0){
    is_available = true;
    serial_read = Serial.read();
  }
}

void SerialController::route_command(){
    is_start = false;
    int idx = read_buffer(3);
    command_index = (uint8_t)idx;
    int action = read_buffer(4);
    int device = read_buffer(5);
    switch(action){
        case GET:{
                if(device != ULTRASONIC_SENSOR){
                    write_head();
                    write_serial(idx);
                }
                read_sensor(device);
                write_end();
            }
            break;
        case RUN:{
                run_module(device);
                call_ok();
            }
            break;
        case RESET:{
                //reset
                call_ok();
            }
            break;
        case START:{
                //start
                call_ok();
            }
            break;
        }
}

void SerialController::read_sensor(int device){
    /**************************************************
    ff    55      len idx action device port slot data a
    0     1       2   3   4      5      6    7    8
    0xff  0x55   0x4 0x3 0x1    0x1    0x1  0xa 
    ***************************************************/
    float value=0.0;
    int port,slot,pin;
    port = read_buffer(6);
    pin = port;
    switch(device){
    case  ULTRASONIC_SENSOR:{
            value = (float)ss.get_distance();
            write_head();
            write_serial(command_index);
            send_float(value);
        }
        break;
    }
}

void SerialController::run_module(int device){
    //0xff 0x55 0x6 0x0 0x2 0x22 0x9 0x0 0x0 0xa 
    int port = read_buffer(6);
    int pin = port;
    switch(device){
        case MOTOR:{
            port==M1?ss.move_left((int)read_short(7)):ss.move_right((int)read_short(7));
            } 
        break;
        case RGBLED:{
            ss.show_color(0,(int)read_buffer(9),(int)read_buffer(10),(int)read_buffer(11));
        }
        break;
        case TONE:{
            ss.play_note((int)read_short(8), (int)read_short(6));
        }
        break;
    }
}

void SerialController::call_ok(){
    write_serial(0xff);
    write_serial(0x55);
    write_end();
}

void SerialController::write_head(){
    write_serial(0xff);
    write_serial(0x55);
}

void SerialController::write_serial(unsigned char c){
    Serial.write(c);
}

void SerialController::write_end(){
     Serial.println(); 
}
unsigned char SerialController::read_buffer(char index){
    return buffer[index];
}

void SerialController::write_buffer(char index, unsigned char c){
    buffer[index] = c;
}

short SerialController::read_short(int idx){
    val_short.byte_val[0] = read_buffer(idx);
    val_short.byte_val[1] = read_buffer(idx+1);
    return val_short.short_val; 
}

void SerialController::send_float(float value){
    write_serial(2);
    val.float_val = value;
    write_serial(val.byte_val[0]);
    write_serial(val.byte_val[1]);
    write_serial(val.byte_val[2]);
    write_serial(val.byte_val[3]);
}