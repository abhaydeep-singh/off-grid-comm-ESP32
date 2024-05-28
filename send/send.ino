#include <LoRa.h>

#define SS 5  
#define RST 14  
#define DIO0 2  

void setup() {
  Serial.begin(9600);
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

  if (LoRa.parsePacket()) {
    String receivedMessage = "";
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }
    Serial.print("Received: ");
    Serial.println(receivedMessage);
  }
}

void sendMessage(String message) {
  Serial.print("Sending: ");
  Serial.println(message);
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
}
