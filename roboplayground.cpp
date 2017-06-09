#include <MeMCore.h>
#include "SubSystems.h"
#include "Commands.h"
#include "SerialController.h"
#include "I2CLink.h"

boolean is_master = false;
boolean previous_button_state = false;
boolean current_button_state = false;
String last_command = String("");
byte i2c_slave_receive_command = I2C_NO_COMMAND;
int i2c_slave_receive_payload = I2C_EMPTY;
byte i2c_slave_send_command = I2C_NO_COMMAND;
int i2c_slave_send_payload = I2C_EMPTY;

SubSystems ss;
Commands cmd(ss);
SerialController sc(ss);


// These are the callbacks for i2c slave
void i2c_slave_receive(int num_bytes){
  byte cp[] = {0, 0};
  byte command;
  int value;
  I2CLink::slave_receive_helper(num_bytes, i2c_slave_receive_command, i2c_slave_receive_payload);
  Serial.println("slave command: "+ String(i2c_slave_receive_command) + "payload: " + String(i2c_slave_receive_payload));
}

void i2c_slave_send(){
    Wire.write(i2c_slave_send_command);
    Wire.write(i2c_slave_send_payload);
}

// ic2_handler() called in loop by slave
void i2c_handler(){
  // If i2c command received, process it and then reset it to no command
  if(i2c_slave_receive_command != I2C_NO_COMMAND){
    cmd.i2c_command(i2c_slave_receive_command, i2c_slave_receive_payload, i2c_slave_send_command, i2c_slave_send_payload);
    i2c_slave_receive_command = I2C_NO_COMMAND;
    i2c_slave_receive_payload = I2C_EMPTY;
  }
}

void button_handler(){
  // Toggle master slave setting if on board button pressed
  current_button_state = ss.is_button_pressed();
  if(current_button_state != previous_button_state){
    previous_button_state = current_button_state;
    if(current_button_state == true){
      is_master = is_master ? false : true;
      if(is_master == true){
        ss.show_color(RED);
      } else {
        ss.show_color(BLUE);
      }
    } 
  }  
}

void ir_remote_handler(){
  // Listen for command, remote for master and bot 2 bot for slave
  uint32_t value = 0;
  if(ss.get_remote_button(&value)){
    switch (value){
      case IR_BUTTON_1:cmd.master_command(String("A"));cmd.command_a(is_master);break;
      case IR_BUTTON_2:cmd.master_command(String("B"));cmd.command_b(is_master);break;
      case IR_BUTTON_3:cmd.master_command(String("C"));cmd.command_c();break;
      case IR_BUTTON_4:cmd.i2c_master_command(is_master, I2C_LED_LEFT, WHITE);break;
      case IR_BUTTON_5:cmd.i2c_master_command(is_master, I2C_OPEN_DOOR, I2C_EMPTY);break;
      case IR_BUTTON_6:cmd.i2c_master_command(is_master, I2C_CLOSE_DOOR, I2C_EMPTY);break;
      case IR_BUTTON_7:cmd.i2c_master_command(is_master, I2C_LED_LEFT, BLACK);break;
      case IR_BUTTON_8:cmd.i2c_master_command(is_master, I2C_ULTRASONIC, I2C_EMPTY);break;

      case IR_BUTTON_UP:ss.move(BOT_FORWARD, FAST);break;
      case IR_BUTTON_LEFT:ss.move(BOT_ROTATE_LEFT, FAST);break;
      case IR_BUTTON_DOWN:ss.move(BOT_BACKWARD, FAST);break;
      case IR_BUTTON_RIGHT:ss.move(BOT_ROTATE_RIGHT, FAST);break;
      case IR_BUTTON_D:ss.move(BOT_FORWARD_LEFT, FAST);break;
      case IR_BUTTON_E:ss.move(BOT_FORWARD_RIGHT, FAST);break;
      case IR_BUTTON_0:ss.move(BOT_BACKWARD_LEFT, FAST);break;
      case IR_BUTTON_F:ss.move(BOT_BACKWARD_RIGHT, FAST);break;
      case IR_BUTTON_SETTING:ss.move(BOT_STOP, STOP);break;
    }      
  }
}

void ir_command_handler(){
  // The slave bot (blue) listens for IR commands from master
  String command = ss.get_ir_string();
  if(command!="" && command != last_command){
    // Serial.println("command: "+command);
    if(command.endsWith("A") == true){
      cmd.command_a(is_master);
    } else if(command.endsWith("B") == true){
      cmd.command_b(is_master);    
    } else if(command.endsWith("C") == true){
      cmd.command_c();    
    }
    last_command = String(command);
  }
}


/*
 * Setup and Loop
 */
void setup() {
  Serial.println("setup");
  Serial.begin(115200);
  // Serial.begin(9600);
  cmd.startup_sequence();
  ss.show_color(BLUE);
  I2CLink::begin();
}

boolean last_is_master = false;
void loop() {
  button_handler();
  if(last_is_master != is_master){
    ss.ir_reset();
    if(is_master){
      I2CLink::end();
      I2CLink::begin();
    } else {
      I2CLink::end();
      I2CLink::begin(true);
      I2CLink::setup_slave(i2c_slave_receive, i2c_slave_send);
    }
    last_is_master = is_master;
    Serial.println("master: "+String(is_master));
  }
  if(is_master){
    sc.serial_handler();
    ir_remote_handler();      
  } else {
    ir_command_handler();
    i2c_handler();
  }
  ss.ir_loop();
}
