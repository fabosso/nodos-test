/// Dependencias de este programa:

// Declaración de defines.
#define PUERTA_PIN 6
#define PUERTA_ACTIVA HIGH    // Señal entrante cuando la puerta está abierta.
#define PUERTA_INACTIVA LOW // Señal entrante cuando la puerta está cerrada.

// Declaración de variables.

/**
    doorOpen es un flag que se pone en true o en false en base al estado de la puerta.
    Si doorOpen es true, significa que la puerta está abierta.
*/
bool doorOpen = false;

///////////////////////////////////////////////////////////////

// Setup del arduino.

void setup() {
    Serial.begin(9600);
    #ifdef PUERTA_PIN
        pinMode(PUERTA_PIN, INPUT_PULLUP);
    #endif
}

// Rutina del arduino.

void loop() {
    // doorObserver();
    digitalPinObserver(PUERTA_PIN);
}

//////////////////////////////////////////////////////////////

// Zona de declaración de funciones.

/**
    doorObserver() se encarga de pollear el estado del pin del 
    sensor de puerta, almacenando ese valor en un flag, doorOpen.
*/
void doorObserver() {
    if (digitalRead(PUERTA_PIN) == PUERTA_ACTIVA) {
        if (!doorOpen) {
            doorOpen = true;
            Serial.println("Se ha abierto la puerta!");
        }
    } else {
        if (doorOpen) {
            doorOpen = false;
            Serial.println("Se ha cerrado la puerta!");
        }
    }
}

void digitalPinObserver(int pin) {
    if (digitalRead(pin) == HIGH) {
        Serial.println(1);
    } else {
        Serial.println(0);
    }
}
