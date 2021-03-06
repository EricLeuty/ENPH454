#include "LabSensor.h"

LabSensor::LabSensor(const String& name_arg, uint8_t address_arg) : name(name_arg), address(address_arg) {}

LabSensor::~LabSensor() {}

String LabSensor::getSensorInfo() const {
    DynamicJsonDocument sensorInfo(100);
    sensorInfo.clear();
    sensorInfo["Sensor Name"] = name;
    sensorInfo["Sensor Address"] = address;
    
    String output;
    serializeJson(sensorInfo, output);
    return output;
}

String LabSensor::getName() const {
    return name;
}

uint8_t LabSensor::getAddress() const {
    return address;
}