/// Dependencias de este programa:

// Declaración de defines.

#define LLUVIA_PIN A0
#define LLUVIA_THRESHOLD_VOLTAGE 2.5    // Tensión threshold cuando llueve.
#define LLUVIA_THRESHOLD_10BIT ((int)(LLUVIA_THRESHOLD_VOLTAGE * (1024 / 5.0)))
#define LLUVIA_ACTIVO LOW

// Declaración de variables.

bool raindrops = false;

///////////////////////////////////////////////////////////////

// Setup del arduino.

void setup() {
    Serial.begin(9600);
}

// Rutina del arduino.

void loop() {
    getNewRaindrop();
}

//////////////////////////////////////////////////////////////

// Zona de declaración de funciones.

/**
    getNewRaindrop() se encarga de agregar un nuevo valor en el array de lluvia,
    basándose en la medición actual del puerto analógico LLUVIA_PIN y en el umbral 
    LLUVIA_THRESHOLD_10BIT configurado.
*/
void getNewRaindrop() {
    #if LLUVIA_ACTIVO == HIGH
        if (analogRead(LLUVIA_PIN) >= LLUVIA_THRESHOLD_10BIT) {
            if (!raindrops) {
                Serial.println("Se largo a llover!");
                raindrops = true;
            }
        } else {
            if (raindrops) {
                Serial.println("Dejo de llover.");
                raindrops = false;
            }
        }
    #else
        if (analogRead(LLUVIA_PIN) < LLUVIA_THRESHOLD_10BIT) {
            if (!raindrops) {
                Serial.println("Se largo a llover!");
                raindrops = true;
            }
        } else {
            if (raindrops) {
                Serial.println("Dejo de llover.");
                raindrops = false;
            }
        }
    #endif
}
