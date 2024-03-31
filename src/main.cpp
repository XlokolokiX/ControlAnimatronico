#include <Arduino.h>
#include <Ps3Controller.h>
#include <ESP32Servo.h>

Servo EyeLX;
Servo EyeLY;
Servo EyeRX;
Servo EyeRY;
Servo EyeLid;
Servo Mouth;


//FC:62:B9:42:82:2F address del control PS3 (Posible)
bool ps3 = false;
bool cross = false;
const char* address = "62:B9:42:82:2F";

int8_t Analog_left[2] = {0,0}, Analog_Right[2] = {0,0};

void notify(){

  //Eventos de los analógicos
  if(Ps3.event.analog_changed.stick.lx == 1){
    Analog_left[0] = Ps3.data.analog.stick.lx;
  }
  if(Ps3.event.analog_changed.stick.ly == 1){
    Analog_left[1] = Ps3.data.analog.stick.ly;
  }
  if(Ps3.event.analog_changed.stick.rx == 1){
    Analog_Right[0] = Ps3.data.analog.stick.rx;
  }
  if(Ps3.event.analog_changed.stick.ry == 1){
    Analog_Right[1] = Ps3.data.analog.stick.ry;
  }
  Serial.println("LX: " + (String)Analog_left[0] + " LY: " + (String)Analog_left[1] );
  Serial.println("RX: " + (String)Analog_Right[0] + " RY: " + (String)Analog_Right[1] );
  if(Ps3.event.button_down.cross == 1){

  }
}

void connected(){
  ps3 = true;
  Serial.println("Controller: Connected");
}

void disconnected(){
  ps3 = false;
  Serial.println("Controller: Disconnected");
}


void setup() {
  delay(200);
  Serial.begin(115200);
  Ps3.begin(address);
  Ps3.attach(notify);
  Ps3.attachOnConnect(connected);
  Ps3.attachOnDisconnect(disconnected);
  EyeLX.attach(19);
  EyeLY.attach(19);
  EyeRX.attach(05);
  EyeRY.attach(17);
  EyeLid.attach(16);
  Mouth.attach(04);
}

void loop() {
  if( !Ps3.isConnected() ){
    return;
  }
  delay(100);
}
