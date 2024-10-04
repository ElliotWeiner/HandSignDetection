/*********
  Elliot Weiner

  To Do:
  Set Up UART
*********/

// Import required libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESP8266WebServer.h>



#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// accelerometer
Adafruit_MPU6050 mpu;
float roll;
float pitch;
String msg;
uint8_t flex[] = {0,0,0};

// wifi
const char* ssid = "ESP8266-AP";
const char* password = "password";
IPAddress local_IP(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);


// REST server on port 80
ESP8266WebServer server(80);

void restServerRouting() {
    server.on("/", HTTP_GET, []() {
        server.send(200, "text/json", msg);
    });
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(9600);

  // Init accelerometer
  if (!mpu.begin()) {
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  

  // init Access Point
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);
  
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  // REST routing
  restServerRouting();
  server.begin(); 

  Wire.begin();
}
 
void loop(){  
 
  // calculate roll and pitch values
  sensors_event_t acceleration, gyroscope, temp;
  mpu.getEvent(&acceleration, &gyroscope, &temp);
  roll = atan2(acceleration.acceleration.y , acceleration.acceleration.z) * 180.0 / PI;
  pitch = atan2(-acceleration.acceleration.x , sqrt(acceleration.acceleration.y * acceleration.acceleration.y + acceleration.acceleration.z * acceleration.acceleration.z)) * 180.0 / PI; //account for roll already applied

  // get flex sensor data
  Wire.requestFrom(8, 3 * sizeof(uint8_t));

  // delay
  while (Wire.available() < 3 * sizeof(uint8_t)) {
    delay(1);
  }

  // read in data
  for (int i = 0; i < 3; i++) {
    flex[i] = Wire.read();
  }
  String str = String(flex[0]) + "  " + String(flex[1]) + "  " + String(flex[2]);
  Serial.println(str);

  msg = "{\"roll\": \"" + String(roll) + "\", \"pitch\": \"" + String(pitch) + "\", \"thumb\": \"" + String(flex[0]) + "\", \"pointer\": \"" + String(flex[1]) + "\", \"middle\": \"" + String(flex[2]) + "\", \"ax\": \"" + String(acceleration.acceleration.x) + "\", \"ay\": \"" + String(acceleration.acceleration.y) + "\", \"az\": \"" + String(acceleration.acceleration.z) + "\"}";
  server.handleClient();



}