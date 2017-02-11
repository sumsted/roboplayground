// #include <Arduino.h>
#include <MeMCore.h>
#include "SubSystems.h"
#include "Commands.h"

boolean is_master = false;
boolean previous_button_state = false;
boolean current_button_state = false;

SubSystems ss;
Commands cmd(ss);

String last_command = String("");


void setup() {
  // ss = new SubSystems();
  // cmd = new Commands(ss);
  Serial.begin(9600);
  cmd.startup_sequence();
  ss.show_color(BLUE);
}

void button_handler(){
  // Toggle master slave setting if on board button pressed
  current_button_state = ss.is_button_pressed();
  if(current_button_state != previous_button_state){
    Serial.println("loop:bs change");
    previous_button_state = current_button_state;
    if(current_button_state == true){
      Serial.println("loop: master check");
      is_master = is_master ? false : true;
      if(is_master == true){
        Serial.println("loop: is_master true");
        ss.show_color(RED);
      } else {
        Serial.println("loop: is_master false");
        ss.show_color(BLUE);
      }
    } 
  }  
}

void ir_remote_handler(){
//  Serial.println("ir_remote_handler");
  // Listen for command, remote for master and bot 2 bot for slave
  uint32_t value = 0;
  if(ss.get_remote_button(&value)){
    Serial.println("ir_remote_handler: ir value: "+String(value));
    switch (value){
      case IR_BUTTON_1:cmd.master_command("A");cmd.command_a(is_master);break;
      case IR_BUTTON_2:cmd.master_command("B");cmd.command_b();break;
      case IR_BUTTON_3:cmd.master_command("C");cmd.command_c();break;
      case IR_BUTTON_4:cmd.master_command("D");cmd.command_d();break;

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
    String command = ss.get_ir_string();
    if(command!="" && command != last_command){
      Serial.println("ir_command_handler: command:"+command+": last_command:"+last_command+":");  
      if(command.endsWith("A") == true){
        cmd.command_a(is_master);
      } else if(command.endsWith("B") == true){
        cmd.command_b();    
      } else if(command.endsWith("C") == true){
        cmd.command_c();    
      } else if(command.endsWith("D") == true){
        cmd.command_d();    
      }
      last_command = String(command);
    }else{
//      Serial.print(".");  
    }
}

boolean last_is_master = false;
void loop() {
  button_handler();
  if(last_is_master != is_master){
    ss.ir_reset();
    last_is_master = is_master;
  }
  if(is_master){
    ir_remote_handler();      
  } else {
    ir_command_handler();
  }
  ss.ir_loop();
}
