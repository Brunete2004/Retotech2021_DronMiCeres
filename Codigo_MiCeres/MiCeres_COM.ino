#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>

//definir comunicación serial secundaria (COM -> NAV)

SoftwareSerial NAVSerial (2, 3); //RX, TX

//definir servomotor semillero

Servo servoSeed;

//definir caractares para comunicaión bluetooth

#define START_CMD_CHAR '*'
#define END_CMD_CHAR '#'
#define DIV_CMD_CHAR '|'

//definir variables

int airQuality;
int xCoord;
int yCoord;
int power;
int seed;


void setup() {

  Serial.begin(9600); //comienza la comunicación por bluetooth (pines serial 0 y 1)
  Serial.flush(); //limpia la memoria serial
  NAVSerial.begin(9600); //comienza la comunicacióncon NAV (pines serial 2 y 3)
  NAVSerial.flush(); //limpia la memoria serial
  servoSeed.attatch(11); //enlazar servomotor semillero al pin 11

}

void loop () {

  seed = 0;
  char get_char = ' ';  //variable para leer bluetooth

  //esperar a recibir algun comando
  if (Serial.available() < 1) return; //si serial esta vacio, volver a loop().

  //indentificar caracter de inicio de comunicación
  get_char = Serial.read();
  if (get_char != START_CMD_CHAR) return; //si no se identifica este caracter volver a loop().

  //extrer información de coordenada X
  xCoord = Serial.parseInt(); //guardar la información de coordenada X

  //extraer información de coordenada Y
  yCoord = Serial.parseInt(); //guardar la información de coordenada Y

  //extraer información de potencia
  power = Serial.parseInt(); //guardar la información de potencia

  //extraer información de semillero
  seed = Serial.parseInt(); //guardar la información de semillero

  //enviar la información necesria a NAV
  NAVSerial.write(prepareSerialData (xCoord, yCoord, power));

  //dispensar semilla
  if (seed == 1) {

  seed();

  }

  //enviar datos atmosféricos a la APP
  Serial.write(readAtmSensor());

}

string prepareSerialData (xCoord, yCoord, power) {

  //concatenar variables en un paquete de datos
  string send = "*" + xCoord + yCoord + power + "#";
  return send;

}


int readAtmSensor () {

  //leer sensor de calidad atmosférica
  int airQuality = analogRead(A0);
  airQuality = map (airQuality, 0, 1023, 0, 100);
  airQuality = "*" + airQuality + "#"
  return airQuality;

}
