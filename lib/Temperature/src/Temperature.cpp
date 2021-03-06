#include <Temperature.h>


Temperature::Temperature(const String& name_arg, uint8_t address_arg) : LabSensor(name_arg, address_arg) {
    bmp_temp = bmp.getTemperatureSensor();
    bmp_pressure = bmp.getPressureSensor();   
}

bool Temperature::begin() {
    if(bmp.begin(address)){
        bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
        Serial.print(F("Connected"));
        return true;
        }
    Serial.println(F("Failed to connected"));   
    return false;
}

String Temperature::getData() {
    bmp_temp->getEvent(&temp_event);
    bmp_pressure->getEvent(&pressure_event);

    DynamicJsonDocument measurement(100);
    measurement.clear();
    measurement["Address"] = address;
    measurement["Timestamp"] = temp_event.timestamp;
    measurement["Temperature"] = temp_event.temperature;
    measurement["Temperature Error"] = temp_err;
    measurement["Pressure"] = pressure_event.pressure;
    measurement["Pressure Error"] = pres_err;

    String data;
    serializeJson(measurement, data);
    return data;
}

void Temperature::printData() {
    Serial.print(getData());
}

