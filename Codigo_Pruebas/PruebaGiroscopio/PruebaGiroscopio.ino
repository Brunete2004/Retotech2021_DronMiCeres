#include<Wire.h>

const int MPU_addr=0x68;
int16_t axis_X,axis_Y,axis_Z;

int minVal=265;
int maxVal=402;

int gx, gy, gz;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(57600);
}
void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  axis_X=Wire.read()<<8|Wire.read();
  axis_Y=Wire.read()<<8|Wire.read();
  axis_Z=Wire.read()<<8|Wire.read();
    int xAng = map(axis_X,minVal,maxVal,-90,90);
    int yAng = map(axis_Y,minVal,maxVal,-90,90);
    int zAng = map(axis_Z,minVal,maxVal,-90,90);

       gx = RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
       gy = RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
       gz = 0;

       if (gy > 180) {
        gy=gy-360;
       }

       if (gx > 180) {
        gx=gx-360;
       }

       Serial.print("g[x y z]:\t");
       Serial.print(gx); Serial.print("\t");
       Serial.print(gy); Serial.print("\t");
       Serial.println(gz);

       delay(200);
}
