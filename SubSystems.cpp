#include "SubSystems.h"

SubSystems::SubSystems(): motor_left(9), motor_right(10), ultrasonic(3) 
{
  ir_reset();
}

void SubSystems::move(int direction, int speed)
{
   int leftSpeed = 0;
   int rightSpeed = 0;
   switch(direction){
     case BOT_FORWARD:
       leftSpeed = speed;
       rightSpeed = speed;
       break;        
     case BOT_BACKWARD:
       leftSpeed = -speed;
       rightSpeed = -speed;
       break;        
     case BOT_ROTATE_LEFT:
       leftSpeed = -speed;
       rightSpeed = speed;
       break;        
     case BOT_ROTATE_RIGHT:
       leftSpeed = speed;
       rightSpeed = -speed;
       break;        
     case BOT_FORWARD_LEFT:
       leftSpeed = speed;
       rightSpeed = speed/2;
       break;        
     case BOT_FORWARD_RIGHT:
       leftSpeed = speed/2;
       rightSpeed = speed;
       break;        
     case BOT_BACKWARD_LEFT:
       leftSpeed = -speed/2;
       rightSpeed = -speed;
       break;        
     case BOT_BACKWARD_RIGHT:
       leftSpeed = -speed;
       rightSpeed = -speed/2;
       break;        
     case BOT_STOP:
       leftSpeed = 0;
       rightSpeed = 0;
       break;        
     }
   motor_left.run((9)==M1?-(leftSpeed):(leftSpeed));
   motor_right.run((10)==M1?-(rightSpeed):(rightSpeed));
   motor_left.run(leftSpeed);
   motor_right.run(rightSpeed);
}

void SubSystems::ir_loop(){
  ir.loop();
}

boolean SubSystems::is_approximate(double a, double b, double e){
  return (abs(a-b)<e);
}

void SubSystems::play_note(int d, int n){
  buzzer.tone(n, d);
  buzzer.noTone();      
}

void SubSystems::show_color(int d, int r, int g, int b){
  led.setColor(0,r,g,b);
  led.show();
  delay(d);    
}

void SubSystems::show_color(int d, int color){
  switch(color){
    case RED:
      led.setColor(0,255,0,0);
      break;
    case GREEN:
      led.setColor(0,0,255,0);
      break;
    case BLUE:
      led.setColor(0,0,0,255);
      break;
    case WHITE:
      led.setColor(0,255,255,255);
      break;
    case BLACK:
    default:
      led.setColor(0,0,0,0);
      break;
  }
  led.show();
  delay(d);    
}

void SubSystems::show_color(int color){
  show_color(0, color);
}

void SubSystems::ir_reset(){
  ir.end();
  ir.begin();
}

boolean SubSystems::get_remote_button(uint32_t *button){
  if(ir.decode()){
    *button = ir.value >> 16 & 0xff;
    return true;
  } else {
    *button = 0;
    return false;
  }
}

boolean SubSystems::is_button_pressed(){
  return (analogRead(7) > 100);
}

void SubSystems::send_ir_string(String contents){
  ir.sendString(contents);
}

String SubSystems::get_ir_string(){
  return ir.getString();
}

double SubSystems::get_distance(){
  return ultrasonic.distanceCm();
}


