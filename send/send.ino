#include <LoRa.h>
#include "BluetoothSerial.h"

#define SS 5  
#define RST 14  
#define DIO0 2  

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("BT-Node-1"); // Bluetooth device name
  while (!Serial);

  Serial.println("Sender Host");

  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa Error");
    while (1);
  }
}

void loop() {
  if (Serial.available()) {
    String dataToSend = Serial.readString();
    sendMessage(dataToSend);
  }

  if (SerialBT.available()) {
    String dataToSend = SerialBT.readString();
    sendMessage(dataToSend);
  }

  if (LoRa.parsePacket()) {
    String receivedMessage = "";
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read(); //reading from lora buffer, casting to char and concatinating into string
    }
    Serial.print("Received: ");
    Serial.println(receivedMessage);
    SerialBT.print("Received: ");
    SerialBT.println(receivedMessage);
  }
}

void sendMessage(String message) {
  Serial.print("Sending: ");
  Serial.println(message);
  SerialBT.print("Sending: ");
  SerialBT.println(message);
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
}
