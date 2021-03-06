#ifndef TEMPERATURE_H
#define TEMPERATURE_H


#include <Adafruit_BMP280.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include "LabSensor.h"


//temperature and pressure measurement resolution
const float temp_err = 0.01;    
const float pres_err = 0.16;    


//Temperature object provides an interface between BMP280 and main loop
//The class formats data as a JSON
class Temperature : public LabSensor {
    public:
        Temperature(const String& name, uint8_t address_arg);
        bool begin() override;
        String getData() override;
        void printData() override;

    private:
        Adafruit_BMP280 bmp;
        Adafruit_Sensor *bmp_temp;
        Adafruit_Sensor *bmp_pressure;
        sensors_event_t temp_event;
        sensors_event_t pressure_event;
    
};

#endif
