#include <Arduino.h>
#include <Wire.h>



const int thumb = 3;
const int pointer = 0;
const int middle = 4;
uint8_t values[] = {0,0,0};

void setup() {
  // init serials
  Serial.begin(9600);

  // init pins
  pinMode(thumb, INPUT);
  pinMode(pointer, INPUT);
  pinMode(middle, INPUT);

  // i2c
  Wire.begin(8); 
  Wire.onRequest(requestEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  values[0] = map(analogRead(thumb), 0, 1023, 0, 255);
  values[1] = map(analogRead(pointer), 0, 1023, 0, 255);
  values[2] = map(analogRead(middle), 0, 1023, 0, 255);
  String msg = "thumb " + String(values[0]) + "," + "pointer " + String(values[1]) + "," + "middle " + String(values[2]);
  Serial.println(msg);
}

void requestEvent() {
  //Wire.write((uint8_t*)values, 3 * sizeof(uint8_t));
  for (int i = 0; i < 3; i++) {
    Wire.write(values[i]);
  }
}
