/// Dependencias de este programa: ninguna.

// Declaración de defines.

#define BUZZER_PIN A1
#define BUZZER_ACTIVO HIGH
#define BUZZER_INACTIVO LOW

// Declaración de variables.

///////////////////////////////////////////////////////////////

// Setup del arduino.

void setup() {
    #ifdef BUZZER_PIN
        pinMode(BUZZER_PIN, OUTPUT);
    #endif
}

// Rutina del arduino.

void loop() {
    alertMock();
}

//////////////////////////////////////////////////////////////

// Zona de declaración de funciones.
void alertMock() {
    static unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 500) {
        digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));
        previousMillis = currentMillis;
    }
}
