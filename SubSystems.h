#ifndef SUB_SYSTEM_H
#define SUB_SYSTEM_H

#include <SoftwareSerial.h>
#include <MeDCMotor.h>
#include <MeUltrasonicSensor.h>
#include <MeBuzzer.h>
#include <MeInfraredReceiver.h>
#include <MeRGBLed.h>
#include <MeIR.h>

#define BOT_FORWARD 1
#define BOT_BACKWARD 2
#define BOT_ROTATE_LEFT 3
#define BOT_ROTATE_RIGHT 4
#define BOT_FORWARD_LEFT 5
#define BOT_FORWARD_RIGHT 6
#define BOT_BACKWARD_LEFT 7
#define BOT_BACKWARD_RIGHT 8
#define BOT_STOP 9

#define FAST 200
#define MEDIUM 100
#define SLOW 75
#define STOP 0

#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494

#define WHITE 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define BLACK 5

#define ON_BOARD_BUTTON 7

class SubSystems {
  public:
    SubSystems();
    

    // ultrasonic
    boolean is_approximate(double a, double b, double e);
    double get_distance();

    // motor movement
    void move(int direction, int speed);

    // colors and sound
    void play_note(int d, int n);
    void show_color(int d, int r, int g, int b);
    void show_color(int d, int color);
    void show_color(int color);

    // button
    boolean is_button_pressed();

    // ir
    void ir_reset();
    void ir_loop();
    void send_ir_string(String contents);
    String get_ir_string();
    boolean get_remote_button(uint32_t *button);
  private:
    MeDCMotor motor_left;
    MeDCMotor motor_right;
    MeUltrasonicSensor ultrasonic;
    MeBuzzer buzzer;
    MeRGBLed led;
    MeIR ir;
    long hello;
};
#endif
