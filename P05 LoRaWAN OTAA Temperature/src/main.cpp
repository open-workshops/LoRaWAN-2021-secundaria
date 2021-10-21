/*******************************************************************************
  P04: Práctica de LoRaWAN con OTAA y sensor de temperatura
  
  Este ejemplo permite enviar datos de un sensor con activacion por OTAA
  - Inicalmente se hace un JOIN por OTAA a una red LoRaWAN
  - La placa lee el estado de un sensor SHT30 (temperatura y humedad)
  - Los valores de temperatura y humedad se imprimen por serial
  - Se formatean los valores anteriores en un array para enviarlos por red
  - Se realiza el uplink por LoRaWAN

  Crea un dispositivo en TTN y rellena los campos de abajo con
  las claves correspondientes

  Conexiones:
    Sensor de temperatura     Placa Heltec
    VIN                       3.3
    GND                       GND
    SCL                       PIN 22
    SDA                       PIN 21

    # PAYLOAD FORMATER para TTN #

    TODO!
  
 ******************************************************************************/

#include <Arduino.h>
#include <WEMOS_SHT3X.h>
#include <TTN_esp32.h>

const char* devEui = "XXXXXXXXXXXXXXXX"; // Rellena con el Device EUI de TTN
const char* appEui = "XXXXXXXXXXXXXXXX"; // Rellena con el Application EUI de TTN
const char* appKey = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"; // Rellena con la Application Key de TTN

TTN_esp32 ttn;
SHT3X sht30(0x44);

void setup() {
  Serial.begin(115200);
  delay(1000);

  ttn.begin();
  ttn.join(devEui, appEui, appKey);
  Serial.print("TTN Join");
  while (!ttn.isJoined())
  {
      Serial.print(".");
      delay(500);
  }
  Serial.println("\njoined!");
  ttn.showStatus();
}

void loop() {
  int errorCode = sht30.get(); // solicitamos medición de temperatura y humedad al sensor

  if (errorCode) // si ha habido un error, no continuamos
  {
    Serial.println("Error leyendo el sensor");
    delay(100000);
    return;
  }

  Serial.print("Temperatura: ");
  Serial.print(sht30.cTemp);
  Serial.println("º C");

  Serial.print("Humedad: ");
  Serial.print(sht30.humidity);
  Serial.println(" %");
  
  Serial.println();

  uint8_t payload[10];


  ttn.sendBytes(payload, 7);
  delay(60000);
}