/// Dependencias de este programa: 
// SPI.
#include <SPI.h>                // https://www.arduino.cc/en/reference/SPI
// LoRa.
#include <LoRa.h>               // https://github.com/sandeepmistry/arduino-LoRa

// Declaración de defines.

#define NSS_PIN 10
#define RESET_PIN -1
#define DIO0_PIN 2
#define DIO1_PIN 3
#define DIO2_PIN 4
#define RXTX_PIN -1
#define LORA_FREQ 433175000                                                         // Frecuencia de la transmisión LoRa (en Hz).
#define DEVICE_ID 10009                                                             // Identificador de este nodo.
#define EXTERIOR_ID (DEVICE_ID + 10000)                                             // Identificador del nodo exterior.
#define BROADCAST_ID (DEVICE_ID - DEVICE_ID % 10000 + 9999)                         // ID broadcast para este tipo de nodo.
#define LORA_TIMEOUT 20                                                             // Tiempo entre cada mensaje LoRa.
#define LORA_SYNC_WORD 0x34                                                         // Palabra de sincronización LoRa.
#define DEVICE_ID_MAX_SIZE 6                                                        // Tamaño máximo que se espera para cada DEVICE_ID entrante.
#define INCOMING_PAYLOAD_MAX_SIZE 100                                               // Tamaño máximo esperado del payload LoRa entrante.
#define INCOMING_FULL_MAX_SIZE (INCOMING_PAYLOAD_MAX_SIZE + DEVICE_ID_MAX_SIZE + 2) // Tamaño máximo esperado del mensaje entrante.

// Declaración de variables.

/**
    incomingFullComplete es un flag que se pone en true luego de completarse la función de interrupción
    onRecieve de LoRa, provisto que la carga útil sea una string con entre 0 y INCOMING_FULL_MAX_SIZE 
    bytes.  
*/
bool incomingFullComplete = false;

/**
    incomingFull es una string que contiene el mensaje LoRa de entrada, incluyendo
    el identificador de nodo.
*/
String incomingFull;

/**
    receiverStr es una string que sólo contiene el identificador de nodo
    recibido en un mensaje LoRa entrante.
*/
String receiverStr;
/**
    greaterThanStr (>) es el delimitador entre el identificador de nodo y la carga útil
    del mensaje de entrada LoRa. Se carga en memoria una única vez en una String constante
    para evitar problemas de memoria heap.
*/
const String greaterThanStr = ">";

///////////////////////////////////////////////////////////////

// Setup del arduino.

void setup() {
    Serial.begin(9600);

    LoRa.setPins(NSS_PIN, RESET_PIN, DIO0_PIN);

    if (!LoRa.begin(LORA_FREQ)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
    LoRa.setSyncWord(LORA_SYNC_WORD);
    LoRa.onReceive(onReceive);
    LoRa.receive();

    Serial.println("LoRa initialized OK.");
}

// Rutina del arduino.

void loop() {
    static unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 60000) {
        // Compone y envía el paquete LoRa.
        LoRa.beginPacket();
        LoRa.print("LoRa message");
        LoRa.endPacket();

        // Pone al módulo LoRa en modo recepción.
        LoRa.receive();
        previousMillis = currentMillis;
    }
}

//////////////////////////////////////////////////////////////

// Zona de declaración de funciones.

void onReceive(int packetSize) {
    // Si el tamaño del paquete entrante es nulo,
    // o si es superior al tamaño reservado para la string incomingFull
    // salir de la subrutina.
    if (packetSize == 0 || packetSize > INCOMING_FULL_MAX_SIZE) {
        return;
    }

    // No se puede utilizar readString() en un callback.
    // Se añaden los bytes uno por uno.
    while (LoRa.available()) {
        incomingFull += (char)LoRa.read();
    }

    // Se levanta un flag de finalización de lectura LoRa.
    incomingFullComplete = true;
}

void downlinkObserver() {
    if (incomingFullComplete) {
        // Extraer el delimitador ">" para diferenciar el ID del payload.
        int delimiter = incomingFull.indexOf(greaterThanStr);

        // Obtener el ID de receptor.
        receiverStr = incomingFull.substring(1, delimiter);
        int receiverID = receiverStr.toInt();
            
        Serial.print("Receiver: ");
        Serial.println(receiverID);

        if (receiverID == DEVICE_ID || receiverID == BROADCAST_ID) {
            Serial.println("ID coincide!");
        } else if (receiverID == EXTERIOR_ID) {
            Serial.println("Nodo exterior!");
        } else {
            Serial.println("Descartado por ID!");
        }

        // Limpiar variables.
        incomingFullComplete = false;
        incomingFull = "";
        receiverStr = "";
    }
}
