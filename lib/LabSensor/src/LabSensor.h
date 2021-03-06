#ifndef LABSENSOR_H
#define LABSENSOR_H


#include <Arduino.h>
#include <ArduinoJson.h>


//All I2C devices inherit LabSensor 
//LabSensor allows multiple different 
//I2C devices objects to be stored on a single LabSensor* Array
class LabSensor {
public:
    LabSensor(const String& name_arg, uint8_t address_arg);
    virtual ~LabSensor();
    virtual bool begin() = 0;
    virtual String getData() = 0;
    virtual void printData() = 0;
    virtual String getSensorInfo() const;
    virtual String getName() const;
    virtual uint8_t getAddress() const;

protected:
    String name;
    uint8_t address;
};

#endif