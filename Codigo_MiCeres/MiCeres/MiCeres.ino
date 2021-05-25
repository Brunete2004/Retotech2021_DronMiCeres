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
  servoSeed.attach(11); //enlazar servomotor semillero al pin 11

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
  sendSerialData(xCoord, yCoord, power);

  //dispensar semilla
  if (seed == 1) {

  //seed();

  }

  //enviar datos atmosféricos a la APP
  sendAtmSensor();

}

void sendSerialData (int xCoordRaw, int yCoordRaw, int powerRaw) {

  char xCoord[15];
  char yCoord[15];
  char power[15];

  sprintf(xCoord, "%05d", xCoordRaw);
  sprintf(yCoord, "%05d", yCoordRaw);
  sprintf(power, "%05d", powerRaw);

  //concatenar variables en un paquete de datos y enviaralas a NAV
  char send[13] = {'*', xCoord, '|', yCoord, '|', powerRaw, '#'};
  /*NAV*/Serial.write(send);
  return;

}


int sendAtmSensor () {

  //leer sensor de calidad atmosférica
  int airQualityRaw = analogRead(A0);
  airQualityRaw = map (airQuality, 0, 1023, 0, 100);
  char airQualitySend[] = {'*', airQualityRaw, '#'};
  //Serial.write(airQualitySend);
  return;

}
