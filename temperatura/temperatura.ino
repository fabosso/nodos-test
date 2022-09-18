/// Dependencias de este programa:
// One Wire.
#include <OneWire.h>            // https://www.pjrc.com/teensy/td_libs_OneWire.html
// Dallas Temperature.
#include <DallasTemperature.h>  // https://www.milesburton.com/Dallas_Temperature_Control_Library

// Declaración de defines.

#define TEMPERATURA_PIN A2

// Declaración de variables.

#ifdef TEMPERATURA_PIN
    OneWire oneWireObjeto(TEMPERATURA_PIN);
    DallasTemperature sensorDS18B20(&oneWireObjeto);
#endif

///////////////////////////////////////////////////////////////

// Setup del arduino.

void setup() {
    Serial.begin(9600);
    #ifdef TEMPERATURA_PIN
        sensorDS18B20.begin();
    #endif
}

// Rutina del arduino.

void loop() {
    static unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 1000) {
        sensorDS18B20.requestTemperatures();
        getNewTemperature();
        previousMillis = currentMillis;
    }
}

//////////////////////////////////////////////////////////////

// Zona de declaración de funciones.
void getNewTemperature() {
    float temperature = sensorDS18B20.getTempCByIndex(0);
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" C");
}
