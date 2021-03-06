#ifndef POWER_H
#define POWER_H


#include <Adafruit_INA219.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include "LabSensor.h"


//bus voltage and current measurement resolution
const float volt_err = 0.002; 
const float curr_err = 0.002;


//Power object provides an interface between INA219 and main loop
//The class formats data as a JSON
class Power : public LabSensor{
    public:
        Power(const String& name, uint8_t address_arg);
        bool begin() override;
        String getData() override;
        void printData() override;

    private:
        Adafruit_INA219 ina219;
};

#endif