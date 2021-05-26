#include <Wire.h>
#include <Servo.h>

//definir servomotor semillero

Servo servoSeed;

//definir variables

static int airQuality = 0;
static int xCoord = 0;
static int yCoord = 0;
static int power = 0;
static int seed = 0;
static bool success = false;

void setup() {

  Serial.begin(9600); //comienza la comunicación por bluetooth (pines serial 0 y 1)
  Serial.flush(); //limpia la memoria serial
  servoSeed.attach(5); //enlazar servomotor semillero al pin 11

}

void loop () {

  recieveData();

  //Serial.println(analogRead(A0));
  sendAtmSensor();
  
  if (success) {

    //enviar información sensor calidad del aire de vuelta
    //sendAtmSensor();
    
    //dispensar semilla
    if (seed == 1) {
  
    //seed();

    }

     Serial.println(xCoord);
     Serial.println(yCoord);
     Serial.println(power);
     Serial.println(seed);
    
  }

  //PID
  
}

void recieveData () {

  Serial.flush();
  success = false;

  seed = 0;
  char get_char = ' ';  //variable para leer bluetooth

  //si se recibe un paquete de datos continuar
  if (Serial.available() > 0) {

    get_char = Serial.read();
    //si se identifica el carcter de inicio de comunicación continuar
    if (get_char == '*') {
    
      //extrer información de coordenada X
      xCoord = Serial.parseInt(); //guardar la información de coordenada X
      delay(10);
    
      //extraer información de coordenada Y
      yCoord = Serial.parseInt(); //guardar la información de coordenada Y
      delay(10);
    
      //extraer información de potencia
      power = Serial.parseInt(); //guardar la información de potencia
      delay(10);
    
      //extraer información de semillero
      seed = Serial.parseInt(); //guardar la información de semillero 
      delay(10);

      success = true;
    }    
  }

  return;
  
}


void sendAtmSensor () {

  //leer sensor de calidad atmosférica
  airQuality = map(analogRead(A0), 0, 320, 0, 100);
  //char airQualitySend[] = {'#', airQuality};
  Serial.println(airQuality);
  return;

}
