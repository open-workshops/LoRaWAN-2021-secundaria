#include <Arduino.h>
/*
  P1: Práctica de LoRa P2P (Transmisor)
  
  Este ejemplo permite enviar tramas de LoRa a bajo nivel.

*/

#include <RadioLib.h>

// SX1278 has the following connections:
// NSS pin:   SS = 18
// DIO0 pin:  DIO0 = 26
// RESET pin: RST_LoRa = 14
// DIO1 pin:  DIO1 = 35
SX1278 radio = new Module(SS, DIO0, RST_LoRa, DIO1);

void setup()
{
  Serial.begin(115200);
  delay(4000); // esperamos a que el minitor serial este listo

  // initialize SX1278 with default settings
  Serial.print("Inicializando... ");

  // Freq: 434.0
  // Bandwidth: 125
  // Spreading factor: 7
  int state = radio.begin(434.0, 125, 7);

  if (state == ERR_NONE)
  {
    Serial.println("OK!");
  } 
  else
  {
    Serial.print("Error, codigo: ");
    Serial.println(state);
    while (true);
  }
}

void loop()
{
  Serial.print(F("Transmitiendo paquete... "));

  //String datos = "ESCRIBE AQUI TU NOMBRE";
  int state = radio.transmit(datos);


  if (state == ERR_NONE)
  {
    Serial.println(F(" ENVIADO!"));

  }
  else
  {
    Serial.print(F("Error, codigo: "));
    Serial.println(state);
  }

  // esperamos 5 segundos y transmitimos de nuevo
  delay(5000);
}