/// Dependencias de este programa:
// Energy Monitor:
#include <EmonLib.h>            // https://learn.openenergymonitor.org/electricity-monitoring/ctac/how-to-build-an-arduino-energy-monitor

// Declaración de defines.

#define CORRIENTE_PIN A1
#define EMON_CALIBRATION 111.1
#define EMON_CROSSINGS 20 // Cantidad de semi-ondas muestreadas para medir tensión y/o corriente.
#define EMON_TIMEOUT 1000 // Timeout de la rutina calcVI (en ms).


// Declaración de variables.

EnergyMonitor eMon;

///////////////////////////////////////////////////////////////

// Setup del arduino.

void setup() {
    Serial.begin(9600);
    #ifdef CORRIENTE_PIN
        eMon.current(CORRIENTE_PIN, EMON_CALIBRATION); 
    #endif
}

// Rutina del arduino.

void loop() {
    static unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 2000) {
        eMon.calcVI(EMON_CROSSINGS, EMON_TIMEOUT);
        getNewCurrent();
        previousMillis = currentMillis;
    }
}

//////////////////////////////////////////////////////////////

// Zona de declaración de funciones.
void getNewCurrent() {
    Serial.print("Nueva corriente: ");
    Serial.print(eMon.Irms);
    Serial.println(" A");
}
