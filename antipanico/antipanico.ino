/// Dependencias de este programa: ninguna.

// Declaración de defines.

#define ANTIPANICO_PIN 5
#define ANTIPANICO_ACTIVO HIGH
#define ANTIPANICO_INACTIVO LOW

// Declaración de variables.

/**
    emergency es un flag que se pone en true o en false en base al estado del 
    botón antipánico. Si emergency es true, significa que el botón ha sido presionado.
*/
bool emergency = false;

///////////////////////////////////////////////////////////////

// Setup del arduino.

void setup() {
    Serial.begin(9600);
    pinMode(ANTIPANICO_PIN, INPUT);
}

// Rutina del arduino.

void loop() {
    emergencyObserver();
}

//////////////////////////////////////////////////////////////

// Zona de declaración de funciones.

/**
    emergencyObserver() se encarga de pollear el estado del pin del botón antipánico,
    almacenando el valor en un flag, emergency.
*/
void emergencyObserver() {
    if (digitalRead(ANTIPANICO_PIN) == ANTIPANICO_ACTIVO) { 
        if (!emergency) {
            Serial.println("Emergencia detectada! ");
        }
        emergency = true;
    } else {
        if (emergency) {
            Serial.println("Emergencia finalizada. ");
        }
        emergency = false;
    }
}