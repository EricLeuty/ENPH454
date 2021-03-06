#include "Power.h"

Power::Power(const String& name, uint8_t address_arg) : LabSensor(name, address_arg) {
    ina219 = Adafruit_INA219(address);
}

bool Power::begin() {

        if(ina219.begin()){
            Serial.print(F("Connected"));
            return true;
        }
        
    Serial.print(F("Failed"));
    return false;
}

String Power::getData() {
    
    DynamicJsonDocument measurement(100);
    measurement.clear();
    measurement["Address"] = address;
    measurement["Voltage"] = String(ina219.getBusVoltage_V());
    measurement["Voltage Error"] = String(volt_err);
    measurement["Timestamp"] = String(millis());
    measurement["Current"] = String(ina219.getCurrent_mA() / 1000);
    measurement["Current Error"] = String(curr_err);

    String data;
    serializeJson(measurement, data);
    return data;

}


void Power::printData() {
    Serial.print(getData());
}

