#include <SoftwareSerial.h>
#include <Wire.h>

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
  Serial.flush(); //limpia la memoria UART

}

void loop () {

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

}

int readAtmSensor () {

  //leer sensor de calidad atmosférica
  airQuality = analogRead(A0);
  airQuality = map (airQuality, 0, 1023, 0, 100);
  return airQuality;

}
