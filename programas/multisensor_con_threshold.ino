//MUCHAS GRACIAS SANTI POR PROVEER EL PROGRAMA
//                                      -Gonie

//- Sensores Laser -

//Librería: VL53L0X by Pololu
//Output: 1 o 0 (DETECTA o NO DETECTA)
//Variable UMBRAL: Distancia en milímetros en la que DETECTA o NO DETECTA

#include <Wire.h>
#include "VL53L0X.h"

VL53L0X sensor[6];  
const int xshut_pins[6] = {2, 3, 4, 5, 6, 7};  
const int UMBRAL = 1000;  // Distancia en mm para considerar detección

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  for (int i = 0; i < 6; i++) pinMode(xshut_pins[i], OUTPUT), digitalWrite(xshut_pins[i], LOW);

  for (int i = 0; i < 6; i++) {
    delay(10);
    digitalWrite(xshut_pins[i], HIGH);
    delay(10);
    sensor[i].setAddress(0x30 + i);
    sensor[i].init();
    sensor[i].startContinuous();
  }
}

void loop() {
  for (int i = 0; i < 6; i++) {
    bool detecta = sensor[i].readRangeContinuousMillimeters() < UMBRAL;
    Serial.print(detecta ? "1\t" : "0\t");  
  }
  Serial.println();
  delay(100);
}
