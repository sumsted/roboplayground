#include "Commands.h"


Commands::Commands(SubSystems &ssr){
    ss = ssr;
}

void Commands::command_a(boolean is_master){
  // Serial.println("command_a: start");
  double slack = 3.0;
  double offset = is_master ? 10.0: 20.0;
  // Serial.println("command_a: offset: "+String(offset));
  ss.play_note(300, NOTE_G4); 
  long end_time = millis() + 20000;
  while(millis()<end_time){
    double current_distance = ss.get_distance();
    // Serial.println("command_a: current_distance: "+String(current_distance));
    if(!ss.is_approximate(current_distance,offset,slack)){
      int speed = (current_distance - offset)>0?150:-150;
      // Serial.println("command_a: move: "+String(speed));
      ss.move(BOT_FORWARD, speed);
    } else {
      // Serial.println("command_a: stop: ");
      ss.move(BOT_STOP, STOP);
    }
    delay(500);
    //test
  }
  ss.move(BOT_STOP, STOP);
  end_time = millis() + 500;
  while(millis()<end_time){
    char i;
    for(i=0;i<4;i++){
      ss.move(BOT_ROTATE_RIGHT, FAST);
      delay(200);
      ss.move(BOT_ROTATE_LEFT, FAST);
      delay(200);      
    }
    ss.move(BOT_STOP, STOP);
  }  
  // Serial.println("command_a: stop");
}

#define NUM_COMMANDS_B 12
int cabm[NUM_COMMANDS_B][3] = {
  {BOT_FORWARD, FAST, 3000},
  {BOT_ROTATE_LEFT, FAST, 2000},
  {BOT_STOP, STOP, 100},
  {BOT_ROTATE_RIGHT, FAST, 2000},
  {BOT_FORWARD_LEFT, FAST, 2000},
  {BOT_FORWARD_RIGHT, FAST, 2000},
  {BOT_ROTATE_LEFT, FAST, 200},
  {BOT_ROTATE_RIGHT, FAST, 200},
  {BOT_ROTATE_LEFT, FAST, 200},
  {BOT_ROTATE_RIGHT, FAST, 200},
  {BOT_ROTATE_LEFT, FAST, 200},
  {BOT_ROTATE_RIGHT, FAST, 200}
};

int cabs[NUM_COMMANDS_B][3] = {
  {BOT_FORWARD, FAST, 3000},
  {BOT_ROTATE_RIGHT, FAST, 2000},
  {BOT_STOP, STOP, 100},
  {BOT_ROTATE_LEFT, FAST, 2000},
  {BOT_FORWARD_RIGHT, FAST, 2000},
  {BOT_FORWARD_LEFT, FAST, 2000},
  {BOT_ROTATE_RIGHT, FAST, 200},
  {BOT_ROTATE_LEFT, FAST, 200},
  {BOT_ROTATE_RIGHT, FAST, 200},
  {BOT_ROTATE_LEFT, FAST, 200},
  {BOT_ROTATE_RIGHT, FAST, 200},
  {BOT_ROTATE_LEFT, FAST, 200}
};

void Commands::command_b(boolean is_master){
  // Serial.println("command_b");
  ss.play_note(300, NOTE_B4); 
  char i;
  for(i=0;i<NUM_COMMANDS_B;i++){
    if(is_master){
      ss.move(cabm[i][0],cabm[i][1]);
      delay(cabm[i][2]);
    } else {
      ss.move(cabs[i][0],cabs[i][1]);
      delay(cabs[i][2]);
    }
  }
  ss.move(BOT_STOP,STOP);
}

void Commands::command_c(){
  // Serial.println("command_c");
  ss.play_note(300, NOTE_C4);
  char i;
  boolean target_found=false;
  for(i=0;i<1;i++){
    ss.show_color(WHITE);
    if(ss.scan_to(50, 10)){
      // Serial.println("command_c: found");
      ss.show_color(GREEN);
      ss.move_to(10,3);
    } else{
      // Serial.println("command_c: not found");
      ss.show_color(RED);
      break;
    }
  }
}

void Commands::master_command(String command){
  // Serial.println("master_command");
  int i;
  for(i=0;i<5;i++){
    ss.show_color(WHITE);
    ss.show_color(RED);
  }
  ss.send_ir_string(command);
}

void Commands::slave_acknowledge(){
  // Serial.println("slave_acknowledge: "); 
}

void Commands::startup_sequence(){
  // Serial.println("startup_sequence");
  int i;
  for(i=0;i<1;i++){
    ss.show_color(200,WHITE);
    ss.play_note(300, NOTE_G4); 
    ss.show_color(200,RED);
    ss.play_note(300, NOTE_E4); 
    ss.show_color(200,GREEN);
    ss.play_note(300, NOTE_C4); 
    ss.show_color(200,BLUE);
  }
}
