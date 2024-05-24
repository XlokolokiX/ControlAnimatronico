#include <SPI.h>
#include <Ps3Controller.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_NeoPixel.h>

/* La posición mínima y máxima del servo tiene que mapearse.
 * Para los SG90 se tiene una frec de funcionamiento de 50Hz
 * (T = 20ms) donde:
 *  - DC = 1ms ----> 0°/-90° (todo a la izquierda)
 *  - DC = 1.5ms --> 90°/0° (posición central) 
 *  - DC = 2ms ----> 180°/90° (todo a la derecha)
 *  
 * El mapeo resulta:
 * T = 20ms ----- 4095 cuentas
 *  
 * Pos_min = 1ms*4095/20ms   = 204 cuentas
 * Pos_med = 1.5ms*4095/20ms = 307 cuentas
 * Pos_max = 2ms*4095/20ms   = 409 cuentas
 */

//DEFINICIÓN DE PINES ------------------------------------------------------
#define eye_LED_PIN 17
#define torch_LED_PIN 4
//--------------------------------------------------------------------------

//DEFINICIÓN DE CONFIGURACIONES --------------------------------------------
#define LED_COUNT 16       // N LED's en ambos ojos
#define SERVOMIN  204     // ancho del pulso que da 0°/-90°
#define SERVOMAX  409     // ancho del pulso que da 180°/90°
#define SERVO_FREQ 50     // frecuencia de trabajo del servo
#define SERVONUM   7      // cantidad de servos conectados al shield

int servoPins[SERVONUM] = {0, 1, 2, 3, 4, 5, 6};             
// arreglo de servos conectados al shield 
//0: up/down (EYE_LEFT)
//l: left/right (EYE_LEFT)
//2: up/down (EYE_RIGHT)
//3: left/right (EYE_RIGHT)
//4: UP_LID
//5: DOWN_LID
//6: MOUTH
//--------------------------------------------------------------------------

//MAPEO DE SERVOS ------(Grados)--------------------------------------------
#define LX_MAX 50
#define LX_MIN -50
#define LY_MAX 60
#define LY_MIN -60

#define RX_MAX 50
#define RX_MIN -50
#define RY_MAX 60
#define RY_MIN -60

#define LIDUP_MAX 90
#define LIDUP_MIN -90
#define LIDOWN_MAX 90
#define LIDOWN_MIN -90

#define MOUTH_MAX 90
#define MOUTH_MIN -90
//--------------------------------------------------------------------------

//VARIABLES GLOBALES -------------------------------------------------------
//Luces
Adafruit_NeoPixel eye_LED(LED_COUNT, eye_LED_PIN, NEO_GRB + NEO_KHZ800);
bool turn_Eye_Led, turn_Flame_Led  = false;
bool blue, red, green, pink = false;

//Movimientos
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int8_t analog_Data[1][2] = {{0,0}};
int8_t mouth_Data = 0;
int8_t eyelid_Data = 127; //abiertas, checkear
bool subir, bajar = false;
uint8_t eyeLid_state = 0; // 0: abierto, 1: cerrado
//BT
const char* address = "28:29:26:82:db:34";          //ADDRESS DEL CONTROL PS3
//--------------------------------------------------------------------------

//FUNCIONES ----------------------------------------------------------------
//---------------- Servo shield ---------------------
/**
 *  Configura el ángulo de posición de un servo conectado a la shield
 *  @param n_servo  Número del servo a configurar
 *  @param ang      Ángulo de posición deseado
 */
void setServo(uint8_t n_servo, long ang){
  uint16_t duty = map(ang, -90, 90, SERVOMIN, SERVOMAX);
  pwm.setPWM(n_servo, 0, duty);
}

/**
 *  Realiza el mapeo de las posiciones analógicas del joystick del control
 *  Ps3. 
 *  @param analogData   Datos capturados del joystick (posición del analógico)
 *  @param servo        Servo que se pretende mover
 *  @param min_Angle    Mínima posición angular posible
 *  @param max_Angle    Máxima posición angular posible
 *  @param death_Zone   Rango de posiciones del joystick que se coinsideran 
 *                        sin movimiento
 *  @param invert
 */
void analogMapping(int8_t analogData, int8_t servo, int min_Angle, int max_Angle, int8_t death_Zone = 10, bool invert = false){
  long angle;

  if(analogData <= death_Zone && analogData >= -death_Zone){
    angle = 0;
  }else if(analogData >= -128 && analogData <= -death_Zone){
    angle = map(analogData, -128, -death_Zone-1, min_Angle, -1);
  }else if(analogData>=11 && analogData<=127){
    angle = map(analogData, death_Zone+1, 127, 1, max_Angle);
  }
  if(invert){
    angle = -angle;
  }

  setServo(servo, angle);
  return;
}

//---------------- Lógica de Luces ---------------------
/**
 *  Mapeo de eventos para el encendido de los leds de los ojos
 *  y la cabeza.
 */
void lightsAnimation(){

  // Reset - Apagado de todas las luces
  if(Ps3.event.button_down.r1 == 1){
    blue = false;
    red = false;
    green = false;
    pink = false;
    eye_LED.clear();
    eye_LED.show();
    
    //delay(10);
    //return;
  }

  // Encendido azul.
  if(Ps3.event.button_down.cross == 1){
    red = false;
    green = false;
    pink = false;
    if(blue == false){
      blue = true;
      Serial.println("Blue");
      for(int i = 0; i<LED_COUNT; i++){
        //delay(20);
        eye_LED.setPixelColor(i,0,0,255);
        eye_LED.show();
      }
    }

    //delay(10);
    //return;
    }

  // Encendido rojo
  if(Ps3.event.button_down.circle == 1){
    blue = false;
    green = false;
    pink = false;
    if(red == false){
      red = true;
      Serial.println("Red");
      for(int i = 0; i<LED_COUNT; i++){
        //delay(20);
        eye_LED.setPixelColor(i,255,0,0);
        eye_LED.show();
      }
    }

    //delay(10);
    //return;
  }

  // Encendido verde
  if(Ps3.event.button_down.triangle == 1){
    red = false;
    pink = false;
    blue = false;
    if(green == false){
    green = true;
    Serial.println("Green");
      for(int i = 0; i<LED_COUNT; i++){
        //delay(20);
        eye_LED.setPixelColor(i,0,255,0);
        eye_LED.show();
      }
    }

    //delay(10);
    //return;
  }

  // Encendido rosa
  if(Ps3.event.button_down.square == 1){
    blue = false;
    red = false;
    green = false;
    if(pink == false){
      pink = true;
      Serial.println("Pink");
      for(int i = 0; i<LED_COUNT; i++){
        //delay(20);
        eye_LED.setPixelColor(i,255,51,204);
        eye_LED.show();
      }
    }

    //delay(10);
    //return;
  }

  // Encendido/apagado llama
  if(Ps3.event.button_down.r2 == 1){
    turn_Flame_Led = !turn_Flame_Led;
    Serial.println("Flame: " + (String)turn_Flame_Led);
    if(turn_Flame_Led == true){
      digitalWrite(torch_LED_PIN, 1);
    }else{
      digitalWrite(torch_LED_PIN, 0);
    }

    //delay(50);
    //return;
  }
}

//---------------- Lógica de boca ---------------------
/**
 * Mapea el movimiento de la boca. La posición del servo queda 
 * determinada por el tiempo que se mantiene presionado el pulsador
 * asociado.
 * @param open  Estado de apertura de la boca (si se sigue abriendo o no)
 * @param close Estado de cierre de la boca (si se sigue cerrando o no)
 */
void mouthMapping(int open, int close){
  if(open){
    if(mouth_Data>=-128 && mouth_Data <= 127-5) {
      mouth_Data += 5;
    }
  }
  if(close){
      if(mouth_Data>=-128+5 && mouth_Data <=127) {
      mouth_Data -=5;
    }
  }
  analogMapping(mouth_Data, servoPins[6], MOUTH_MIN, MOUTH_MAX);
}

//---------------- Lógica de pestañas ---------------------
/**
 * Mapea el movimiento de las pestañas.
 * @param lidState Estado de las pestañas, si deben abrirse o cerrarse
 */

// lid up (4) cuando se cierra va a -90 (-127)  --- cuando se abre va a 90 (127)
// lid down (5) cuando se cierra va a 90 (127)  --- cuando se abre va a -90 (-127)
void eyeBlinking(uint8_t lidState){
  switch(lidState) {
    case 0:
      // estado abierto
      analogMapping(115, servoPins[4], LIDUP_MIN, LIDUP_MAX);
      analogMapping(115, servoPins[5], LIDOWN_MIN, LIDOWN_MAX);
      delay(20);
      break;
    case 1:
      // estado cerrado
      analogMapping(-110, servoPins[4], LIDOWN_MIN, LIDOWN_MAX);
      analogMapping(-110, servoPins[5], LIDUP_MIN, LIDUP_MAX);
      delay(20);
      break;
    default:
      break;
  }
}

/**
 *  Interrupción Ps3: Controla los eventos para cada uno de los
 *  pulsadores y analógicos del controlador.
 */
void notify(){ 
  
  //---------------- Lógica Ojos ------------------------
  // Realiza la lectura del control joystick del control y mapea los datos
  // a movimientos de los servos asocidos a los ojos.
  if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
    analog_Data[0][0] = Ps3.data.analog.stick.lx;
    analog_Data[0][1] = Ps3.data.analog.stick.ly;
    analogMapping(analog_Data[0][1], 0, LY_MIN, LY_MAX, 10, true);
    analogMapping(analog_Data[0][0], 1, LX_MIN, LX_MAX);
    analogMapping(analog_Data[0][1], 2, RY_MIN, RY_MAX);
    analogMapping(analog_Data[0][0], 3, RX_MIN, RX_MAX);
    Serial.println("L: " + (String)analog_Data[0][0] + "R: " + (String)analog_Data[0][1]);
  }
  //-----------------------------------------------------

  //---------------- Lógica pestañeo --------------------
  // Setea el flag de estado de las pestañas (abierto/cerrado) de acuerdo a
  // el estado del pulsador 
  if( Ps3.event.button_down.l1 ) {
    eyeLid_state = 1;
  } else if( Ps3.event.button_up.l1 ){
    eyeLid_state = 0;
  }
  //-----------------------------------------------------

  //---------------- Lógica Boca ------------------------
  // Setea el estado de dos flags que determinan si la boca se abre (subir)
  // o se cierra (bajar)
  if ( Ps3.event.button_down.up )
  {
    subir = 1;
  }
  if ( Ps3.event.button_up.up )
  {
    subir = 0;
  }
  if ( Ps3.event.button_down.down )
  {
    bajar = 1;
  }
  if ( Ps3.event.button_up.down )
  {
    bajar = 0;
  }
  //-----------------------------------------------------
}

/**
 *  Notifica la correcta conexión del control Ps3
 */
void connected(){
  Ps3.setRumble(50.0, 1);
  digitalWrite(LED_BUILTIN, 1);
  Serial.println("Controller: Connected");
}

/**
 *  Notifica la desconexión del control Ps3
 */
void disconnected(){
  digitalWrite(LED_BUILTIN, 0);
  Serial.println("Controller: Disconnected");
}


//--------------------------------------------------------------------------
void setup() {

  // Start-up

  delay(1000);
  Serial.begin(115200);
  Serial.println(" ");

  // Control PS3
  Ps3.begin(address);
  Ps3.attach(notify);
  Ps3.attachOnConnect(connected);
  Ps3.attachOnDisconnect(disconnected);
  
  // Leds
  eye_LED.begin();
  eye_LED.setBrightness(255);
  eye_LED.show();
  pinMode(torch_LED_PIN, OUTPUT);

  // Servo shield
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);
  for(int i = 0; i < SERVONUM; i++){
    setServo(servoPins[i], 0);
  }
  
  Serial.println("Ready");
  delay(1000);
}
//--------------------------------------------------------------------------
// Se agregan en el loop las funciones de:
// - control de boca
// - control de luces de ojos y vela
// - control de pestaneo
// para evitar errores de buggeo en la interrupción
void loop() {
  if( !Ps3.isConnected() ){
    return;
  }

  delay(10);

  mouthMapping(subir, bajar);

  delay(10);

  lightsAnimation();

  //delay(10);

  eyeBlinking(eyeLid_state);

  delay(10);

}
//--------------------------------------------------------------------------