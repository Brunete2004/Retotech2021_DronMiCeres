/*Disposicion de los motores del dron:
     
     1
     ↑
  4--O--2
     |
     3
*/

#include <Servo.h>

Servo Motor1;
Servo Motor2;
Servo Motor3;
Servo Motor4;

int valorPot;

void setup() {
  // Ligar ESC1 al pin 6
  Motor1.attach(6,1000,2000);
  // Ligar ESC2 al pin 9
  Motor2.attach(9,1000,2000);
  // Ligar ESC3 al pin 10
  Motor3.attach(10,1000,2000);
  // Ligar ESC4 al pin 11
  Motor4.attach(11,1000,2000);
  // (pin, valor mínimo del pulso, valor máximo del pulso (todo en microsegundos)) 
}

void loop() {
  valorPot = analogRead(A0); //leer el valor del potenciómetro (valor entre 0 y 1023)
  valorPot = map(valorPot, 0, 1023, 0, 180); //cambiar el valor a ángulos para emplearlos con la librería SERVO (valores entre 0 y 180)

  //escribir el valor del potenciómetro a los ESC
  Motor1.write(valorPot);
  Motor2.write(valorPot);
  Motor3.write(valorPot);
  Motor4.write(valorPot);
}
