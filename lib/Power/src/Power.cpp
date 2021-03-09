#include "Power.h"

Power::Power(const String& name, uint8_t address_arg) : LabSensor(name, address_arg) {
    ina219 = Adafruit_INA219(address);
}

bool Power::begin() {
    bool connected;
    Serial.println("Connecting to device: " + name);
    Serial.print("Connection status: ");

    if(ina219.begin()){
        Serial.print(F("Connected"));
        connected = true;
    }
    else {
        Serial.print(F("Failed"));
        connected = false;
    }    
    Serial.println();
    return connected;
}

String Power::getData() {
    
    DynamicJsonDocument measurement(100);
    measurement.clear();
    measurement["Address"] = address;
    measurement["Timestamp"] = millis() / float(1000);
    measurement["Voltage (V)"] = ina219.getBusVoltage_V();
    measurement["Current (A)"] = ina219.getCurrent_mA() / 1000;
    measurement["Voltage Error"] = ina219.getBusVoltage_V() * (volt_err);
    measurement["Current Error"] = (ina219.getCurrent_mA() / 1000) * (curr_err);

    String data;
    serializeJson(measurement, data);
    return data;

}


void Power::printData() {
    Serial.print(getData());
}

