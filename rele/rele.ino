/// Dependencias de este programa:

// Declaración de defines.

#define RELE_PIN 7
#define RELE_ACTIVO HIGH        // definido según jumper de módulo
#define RELE_INACTIVO LOW       // definido según jumper de módulo


// Declaración de variables.

///////////////////////////////////////////////////////////////

// Setup del arduino.

void setup() {
    #ifdef RELE_PIN
        pinMode(RELE_PIN, OUTPUT);
    #endif
}

// Rutina del arduino.

void loop() {
    static unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 1000) {
        digitalWrite(RELE_PIN, !digitalRead(RELE_PIN));
        previousMillis = currentMillis;
    }
}

//////////////////////////////////////////////////////////////

// Zona de declaración de funciones.

