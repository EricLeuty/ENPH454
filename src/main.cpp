#include <Arduino.h>
#include <ArduinoJson.h>
#include "LabSensor.h"
#include "Temperature.h"
#include "Power.h"


//number of I2C Sensors
#define NUM_SENSORS 3 


//interval between collecting data from the active sensors in milliseconds
#define MEASUREMENT_INTERVAL 1000

//arrays that sensor objects
typedef LabSensor* SensorPtr;
SensorPtr* sensors = new SensorPtr[NUM_SENSORS];
SensorPtr* activeSensors = new SensorPtr[NUM_SENSORS];
int numConnected(0);


//initialize arduino
void setup() {
  //initialize serial connection
  Serial.begin(115200);
  Serial.println("Serial Connected");
  

  //add sensor objects to sensors array
  sensors[0] = new Temperature("Temperature and pressure sensor", 0x76);
  sensors[1] = new Power("Solar side power", 0x40);
  sensors[2] = new Power("Fuel cell power", 0x41);


  //configInfo stores the start time and the 
  //names and addresses of each sensor 
  DynamicJsonDocument configInfo(100);
  configInfo.clear();
  configInfo["Start Time"] = millis() / float(1000);
  JsonObject sensorsInfo = configInfo.createNestedObject("Sensors");


  //checks if sensor is connected
  for(int i = 0; i < NUM_SENSORS; i++) {
    //attempts to connect to each sensor
    if(sensors[i]->begin()) {
      //add connected sensor to array of connected sensors
      activeSensors[numConnected] = sensors[i];
      numConnected++;
      //add sensor info to configInfo
      String sensor_num = "Sensor " + String(i);
      JsonObject sensorInfo = sensorsInfo.createNestedObject(sensor_num);
      sensorInfo["Name"] = activeSensors[i]->getName();
      sensorInfo["Address"] = activeSensors[i]->getAddress();
    }
    else {
      //delete inactive sensors
      Serial.print("Deleted inactive sensor");
      delete sensors[i];
    }
  }


  //delete array that held unititialized sensors
  Serial.println("Deleted sensor Array");
  delete[] sensors;
  Serial.println();
  

  //serialize and print configInfo
  serializeJson(configInfo, Serial);
  Serial.println();
}

void loop() {
  //collect data from each active sensor and send data over serial
  for(int i = 0; i < numConnected; i++) {
    Serial.println(activeSensors[i]->getData());
  }
  delay(MEASUREMENT_INTERVAL);
}

