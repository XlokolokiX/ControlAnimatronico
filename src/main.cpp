#include <Arduino.h>
#include <Ps3Controller.h>
#include <ESP32Servo.h>
#include <Adafruit_NeoPixel.h>

//DEFINICIÓN DE PINES ------------------------------------------------------
#define eye_LED_PIN 4
#define eye_LX_PIN 36
#define eye_LY_PIN 39
#define eye_RX_PIN 34
#define eye_RY_PIN 35
#define eye_LID1_PIN 32
#define eye_LID2_PIN 33
#define mouth_PIN 25
//--------------------------------------------------------------------------

//DEFINICIÓN DE CONFIGURACIONES --------------------------------------------
#define LED_COUNT 14
#define BRIGHTNESS 50
#define MG90_MIN 500
#define MG90_MAX 2400
#define MG995_MIN 1000
#define MG995_MAX 2000
//--------------------------------------------------------------------------

//VARIABLES GLOBALES -------------------------------------------------------
Adafruit_NeoPixel eye_LED(LED_COUNT,5, NEO_GBR + NEO_KHZ800);

Servo EyeLX;
Servo EyeLY;
Servo EyeRX;
Servo EyeRY;
Servo EyeLid1;
Servo EyeLid2;
Servo Mouth;

//FC:62:B9:42:82:2F address del control PS3 (Posible)
bool ps3 = false;
bool cross = false;
const char* address = "62:B9:42:82:2F";

int8_t Analog_left[2] = {0,0}, Analog_Right[2] = {0,0};
//--------------------------------------------------------------------------

//ANIMACIONES --------------------------------------------------------------
//--------------------------------------------------------------------------

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

  //Control PS3
  Ps3.begin(address);
  Ps3.attach(notify);
  Ps3.attachOnConnect(connected);
  Ps3.attachOnDisconnect(disconnected);

  //Servos
  EyeLX.attach(eye_LX_PIN, MG90_MIN, MG90_MAX);
  EyeLX.setPeriodHertz(50);
  EyeLY.attach(eye_LY_PIN, MG90_MIN, MG90_MAX);
  EyeLY.setPeriodHertz(50);
  EyeRX.attach(eye_RX_PIN, MG90_MIN, MG90_MAX);
  EyeRX.setPeriodHertz(50);
  EyeRY.attach(eye_RY_PIN, MG90_MIN, MG90_MAX);
  EyeRY.setPeriodHertz(50);
  EyeLid1.attach(eye_LID1_PIN, MG90_MIN, MG90_MAX);
  EyeLid1.setPeriodHertz(50);
  EyeLid2.attach(eye_LID2_PIN, MG90_MIN, MG90_MAX);
  EyeLid2.setPeriodHertz(50);
  Mouth.attach(mouth_PIN, MG995_MIN, MG995_MAX);
  Mouth.setPeriodHertz(50);
  
  //Led
  eye_LED.begin();
  eye_LED.setBrightness(BRIGHTNESS);
  eye_LED.clear();

  eye_LED.Color(3, 252, 240);
  for(int i = 0; i<255; i+=5){
    delay(10);
    eye_LED.setBrightness(i);
  }
  
}

void loop() {
  if( !Ps3.isConnected() ){
    return;
  }
  delay(100);
}
