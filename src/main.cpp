#include <Arduino.h>
#include <Ps3Controller.h>
#include <ESP32Servo.h>
#include <Adafruit_NeoPixel.h>

//DEFINICIÓN DE PINES ------------------------------------------------------
#define eye_LED_PIN 0
#define torch_LED_PIN 4
#define eye_LX_PIN 23
#define eye_LY_PIN 22
#define eye_RX_PIN 19
#define eye_RY_PIN 18
#define eye_LID1_PIN 25
#define eye_LID2_PIN 26
#define mouth_PIN 27
//--------------------------------------------------------------------------

//DEFINICIÓN DE CONFIGURACIONES --------------------------------------------
#define LED_COUNT 8
#define BRIGHTNESS 50
#define MG90_MIN 500
#define MG90_MAX 2400
#define MG995_MIN 1000
#define MG995_MAX 2000
//--------------------------------------------------------------------------

//VARIABLES GLOBALES -------------------------------------------------------

Adafruit_NeoPixel eye_LED(LED_COUNT, eye_LED_PIN, NEO_GRB + NEO_KHZ800);
bool turn_Eye_Led, turn_Flame_Led  = false;
bool blue, red, green, pink = false;

const char* address = "28:29:26:82:db:34";

int8_t analog_Data[2][2] = {{0,0},{0,0}};
//--------------------------------------------------------------------------

//ANIMACIONES --------------------------------------------------------------
//--------------------------------------------------------------------------

void notify(){ //Eventos del control
  
  //---------------- Analógicos ---------------
  if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
    analog_Data[0][0] = Ps3.data.analog.stick.lx;
    analog_Data[0][1] = Ps3.data.analog.stick.ly;
    Serial.println("L: " + (String)analog_Data[0][0] + " " +(String)analog_Data[0][1]);
  }

  if( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ){
    analog_Data[1][0] = Ps3.data.analog.stick.rx;
    analog_Data[1][1] = Ps3.data.analog.stick.ry;
    Serial.println("R: " + (String)analog_Data[1][0] + " " +(String)analog_Data[1][1]);
  }

  //---------------- Lógica de Luces ---------------------
  if(Ps3.event.button_down.r1 == 1){
    blue = false;
    red = false;
    green = false;
    pink = false;
    eye_LED.clear();
    eye_LED.show();
  }
  if(Ps3.event.button_down.cross == 1){
    red = false;
    green = false;
    pink = false;
    if(blue == false){
      blue = true;
      Serial.println("Blue");
      for(int i = 0; i<8; i++){
        delay(80);
        eye_LED.setPixelColor(i,0,0,255);
        eye_LED.show();
      }
    }
   }
  if(Ps3.event.button_down.circle == 1){
    blue = false;
    green = false;
    pink = false;
    if(red == false){
      red = true;
      Serial.println("Red");
      for(int i = 0; i<8; i++){
        delay(80);
        eye_LED.setPixelColor(i,255,0,0);
        eye_LED.show();
      }
    }
  }
  if(Ps3.event.button_down.triangle == 1){
    red = false;
    pink = false;
    blue = false;
    if(green == false){
    green = true;
    Serial.println("Green");
      for(int i = 0; i<8; i++){
       delay(80);
       eye_LED.setPixelColor(i,0,255,0);
       eye_LED.show();
      }
    }
  }
  if(Ps3.event.button_down.square == 1){
    blue = false;
    red = false;
    green = false;
    if(pink == false){
      pink = true;
      Serial.println("Pink");
      for(int i = 0; i<8; i++){
       delay(80);
       eye_LED.setPixelColor(i,255,51,204);
       eye_LED.show();
      }
    }
  }
}

void connected(){
  Ps3.setRumble(50.0, 1);
  digitalWrite(LED_BUILTIN, 1);
  Serial.println("Controller: Connected");
}

void disconnected(){
  digitalWrite(LED_BUILTIN, 0);
  Serial.println("Controller: Disconnected");
}


void setup() {
  delay(200);
  Serial.begin(115200);
  Serial.println(" ");

  //Control PS3
  Ps3.begin(address);
  Ps3.attach(notify);
  Ps3.attachOnConnect(connected);
  Ps3.attachOnDisconnect(disconnected);
  
  //Led
  eye_LED.begin();
  eye_LED.setBrightness(255);
  eye_LED.show();

  Serial.println("Ready");
}

void loop() {
  if( !Ps3.isConnected() ){
    return;
  }
  delay(100);
}
