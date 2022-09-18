/// Dependencias de este programa:
// Software serial.
#include <SoftwareSerial.h>     // https://www.arduino.cc/en/Reference/SoftwareSerial
// TinyGPS++.
#include <TinyGPS++.h>          // https://github.com/mikalhart/TinyGPSPlus

// Declaración de defines.

#define RX_GPS_PIN 8
#define TX_GPS_PIN 9
#define GPS_DECIMAL_POSITIONS 5

// Declaración de variables.

SoftwareSerial ssGPS(TX_GPS_PIN, RX_GPS_PIN); // hacemos cruce de señales por SW, respecto del método constructor (TX -> RX, RX -> TX)
TinyGPSPlus GPS;

///////////////////////////////////////////////////////////////

// Setup del arduino.

void setup() {
    Serial.begin(9600);
    ssGPS.begin(9600);
}

// Rutina del arduino.

void loop() {
    static unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 2000) {
        getNewGPS();
        if (GPS.location.isValid()) {
            Serial.print("Lat: ");
            Serial.print(String(GPS.location.lat(), GPS_DECIMAL_POSITIONS));
            Serial.print("Long: ");
            Serial.print(String(GPS.location.lng(), GPS_DECIMAL_POSITIONS));
            Serial.print("Alt: ");
            Serial.println(String((int)GPS.altitude.meters()));
        } else {
            Serial.print("Lat: ");
            Serial.print("***");
            Serial.print("Long: ");
            Serial.print("***");
            Serial.print("Alt: ");
            Serial.println("***");
        }
        previousMillis = currentMillis;
    }
}

//////////////////////////////////////////////////////////////

// Zona de declaración de funciones.

/**
    getNewGPS() se encarga de leer la información proveniente del puerto
    serial correspondiente al GPS (ssGPS) y encodear esa información a un
    objeto que organiza esos datos (GPS).
*/
void getNewGPS() {
    while (ssGPS.available() > 0) {
        GPS.encode(ssGPS.read());
    }
}
