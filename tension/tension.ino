/// Dependencias de este programa:
// Energy Monitor:
#include <EmonLib.h>            // https://learn.openenergymonitor.org/electricity-monitoring/ctac/how-to-build-an-arduino-energy-monitor

// Declaración de defines.

#define TENSION_PIN A0
#define EMON_CROSSINGS 20 // Cantidad de semi-ondas muestreadas para medir tensión y/o corriente.
#define EMON_TIMEOUT 1000 // Timeout de la rutina calcVI (en ms).

// Declaración de variables.

EnergyMonitor eMon;

///////////////////////////////////////////////////////////////

// Setup del arduino.

void setup() {
    Serial.begin(9600);
    eMon.voltage(TENSION_PIN, 226.0, 1.7);
}

// Rutina del arduino.

void loop() {
    static unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 2000) {
        eMon.calcVI(EMON_CROSSINGS, EMON_TIMEOUT);
        getNewVoltage();
        previousMillis = currentMillis;
    }
}

//////////////////////////////////////////////////////////////

// Zona de declaración de funciones.
void getNewVoltage() {
    Serial.print("Nueva tension: ");
    Serial.print(eMon.Vrms);
    Serial.println(" V");
}
