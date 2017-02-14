#include "SerialController.h"

SerialController:SerialController(SubSystems &ssr){
    ss = ssr;
}

void SerialController::serial_handler(){

}

void SerialController::route_command(){

}

void SerialController::read_sensor(int device){

}

void SerialControllerSubSystems::run_module(int device){

}

void SerialController::call_ok(){
    writeSerial(0xff);
    writeSerial(0x55);
    writeEnd();
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

short SerialController::readShort(int idx){
  valShort.byteVal[0] = readBuffer(idx);
  valShort.byteVal[1] = readBuffer(idx+1);
  return valShort.shortVal; 
}