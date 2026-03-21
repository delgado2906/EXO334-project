#include <SoftwareSerial.h>
#include <IRremote.hpp>

SoftwareSerial BT(2, 3); // RX, TX

int rele1 = 7;
int rele2 = 8;
int IR_PIN = 9;

void setup() {
  BT.begin(9600);
  Serial.begin(9600);

  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);

  IrReceiver.begin(IR_PIN);
}

void loop() {

  if (BT.available()) {
    byte cmd = BT.read();
    ejecutarComando(cmd);
  }

  if (IrReceiver.decode()) {

    int irValue = IrReceiver.decodedIRData.command;
    Serial.println(irValue);

    if (irValue == 140)   ejecutarComando(0x01); // rele1 ON
    if (irValue == 5) ejecutarComando(0x02); // rele1 OFF
    if (irValue == 158)  ejecutarComando(0x03); // rele2 ON
    if (irValue == 93) ejecutarComando(0x04); // rele2 OFF

    IrReceiver.resume();
  }
}

void ejecutarComando(byte cmd) {

  switch (cmd) {

    case 0x01:
      digitalWrite(rele1, HIGH);
      Serial.println("Rele1 ON");
      break;

    case 0x02:
      digitalWrite(rele1, LOW);
      Serial.println("Rele1 OFF");
      break;

    case 0x03:
      digitalWrite(rele2, HIGH);
      Serial.println("Rele2 ON");
      break;

    case 0x04:
      digitalWrite(rele2, LOW);
      Serial.println("Rele2 OFF");
      break;
  }
}