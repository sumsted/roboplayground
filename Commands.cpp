#include "Commands.h"

Commands::Commands(SubSystems *ss){
    ssp = ss;
}

void Commands::command_a(boolean is_master){
  Serial.println("command_a: start");
  double slave_offset = 20.0;
  double master_offset = 10.0;
  double slack = 3.0;
  double offset = is_master ? master_offset: slave_offset;
  ssp->play_note(300, NOTE_G4); 
  long end_time = millis() + 5 * 1000;
  while(millis()<end_time){
    double current_distance = ssp->get_distance();
    Serial.println("command_a: current_distance: "+String(current_distance));
    if(ssp->is_approximate(current_distance,offset,slack)){
      int speed = (current_distance - offset)>0?150:-150;
      Serial.println("command_a: move: "+String(speed));
      ssp->move(BOT_FORWARD, speed);
    } else {
      Serial.println("command_a: stop: ");
      ssp->move(BOT_STOP, STOP);
    }
    delay(500);
    //test
  }
  ssp->move(BOT_STOP, STOP);
  end_time = millis() + 500;
  while(millis()<end_time){
    int i;
    for(i=0;i<4;i++){
      ssp->move(BOT_ROTATE_RIGHT, MEDIUM);
      delay(100);
      ssp->move(BOT_ROTATE_LEFT, MEDIUM);
      delay(100);      
    }
  ssp->move(BOT_STOP, STOP);
  }  
  Serial.println("command_a: stop");
}

void Commands::command_b(){
  Serial.println("command_b");
  ssp->play_note(300, NOTE_B4); 
}

void Commands::command_c(){
  Serial.println("command_c");
  ssp->play_note(300, NOTE_C4); 
}

void Commands::command_d(){
  Serial.println("command_d");
  ssp->play_note(300, NOTE_D4); 
}

void Commands::master_command(String command){
  Serial.println("master_command");
  int i;
  for(i=0;i<5;i++){
    ssp->show_color(WHITE);
    ssp->show_color(RED);
  }
  ssp->send_ir_string(command);
}

void Commands::slave_acknowledge(){
  Serial.println("slave_acknowledge: "); 
}

void Commands::startup_sequence(){
  Serial.println("startup_sequence");
  int i;
  for(i=0;i<1;i++){
    ssp->show_color(200,WHITE);
    ssp->play_note(300, NOTE_G4); 
    ssp->show_color(200,RED);
    ssp->play_note(300, NOTE_E4); 
    ssp->show_color(200,GREEN);
    ssp->play_note(300, NOTE_C4); 
    ssp->show_color(200,BLUE);
  }
}
