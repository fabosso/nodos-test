/// Dependencias de este programa:
// New Ping.
#include <NewPing.h>            // https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home

// Declaración de defines.

#define COMBUSTIBLE_ECHO_PIN 6
#define COMBUSTIBLE_TRIG_PIN 5
#define PING_SAMPLES 5           // Cantidad de muestras ultrasónicos.

// Declaración de variables.

NewPing sonar(COMBUSTIBLE_TRIG_PIN, COMBUSTIBLE_ECHO_PIN, 300);

///////////////////////////////////////////////////////////////

// Setup del arduino.

void setup() {
    Serial.begin(9600);
    #ifdef COMBUSTIBLE_TRIG_PIN
        pinMode(COMBUSTIBLE_TRIG_PIN, OUTPUT);
    #endif
    #ifdef COMBUSTIBLE_ECHO_PIN
        pinMode(COMBUSTIBLE_ECHO_PIN, INPUT);
    #endif
}

// Rutina del arduino.

void loop() {
    static unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 200) {
        getNewGas();
        previousMillis = currentMillis;
    }
}

//////////////////////////////////////////////////////////////

// Zona de declaración de funciones.
void getNewGas() {
    float timeUltrasonic = sonar.ping_median(PING_SAMPLES);
    Serial.print("Ping: ");
    Serial.print(timeUltrasonic);
    Serial.println(" us");
}
