#include "SubSystems.h"

SubSystems::SubSystems(): motor_left(9), motor_right(10), ultrasonic(3), led(7, 7==7?2:4)
{
  ir_reset();
}

void SubSystems::move(int direction, int speed)
{
  Serial.println("SubSystems: move: direction: "+String(direction)+", speed: "+String(speed));
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
       leftSpeed = speed/2;
       rightSpeed = speed;
       break;        
     case BOT_FORWARD_RIGHT:
       leftSpeed = speed;
       rightSpeed = speed/2;
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
}

void SubSystems::ir_loop(){
  ir.loop();
}

boolean SubSystems::is_approximate(double a, double b, double e){
  return (abs(a-b)<e);
}

void SubSystems::play_note(int d, int n){
  Serial.println("SubSystems: play_note: duration: "+String(d)+", tone: "+String(n));
  buzzer.tone(n, d);
  buzzer.noTone();      
}

void SubSystems::show_color(int d, int r, int g, int b){
  Serial.println("SubSystems: show_color: d: "+String(d)+", r,g,b: "+String(r)+", "+String(g)+", "+String(b));
  led.setColor(0,r,g,b);
  led.show();
  delay(d);    
}

void SubSystems::show_color(int d, int color){
  Serial.println("SubSystems: show_color: d: "+String(d)+", color: "+String(color));
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
  Serial.println("SubSystems: show_color: color: "+String(color));
  show_color(0, color);
}

void SubSystems::ir_reset(){
  Serial.println("SubSystems: ir_reset\n");
  ir.end();
  ir.begin();
}

boolean SubSystems::get_remote_button(uint32_t *button){
  // Serial.println("SubSystems: get_remote_button\n");
  if(ir.decode()){
    *button = ir.value >> 16 & 0xff;
    return true;
  } else {
    *button = 0;
    return false;
  }
}

boolean SubSystems::is_button_pressed(){
  // Serial.println("SubSystems: is_button_pressed\n");
  return (analogRead(7) > 100);
}

void SubSystems::send_ir_string(String contents){
  Serial.println("SubSystems: send_ir_string\n");
  ir.sendString(contents);
}

String SubSystems::get_ir_string(){
  Serial.println("SubSystems: get_ir_string\n");
  return ir.getString();
}

double SubSystems::get_distance(){
  Serial.println("SubSystems: get_distance\n");
  return ultrasonic.distanceCm();
}


