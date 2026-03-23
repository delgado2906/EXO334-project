#include "BluetoothSerial.h"
#include <ESP32Servo.h>

HardwareSerial VC02(2);
BluetoothSerial SerialBT;

Servo myServo1;
Servo myServo2;

int servoPin1 = 18;
int servoPin2 = 32;

unsigned int receivedValue = 0;

void setup() {

  myServo1.attach(servoPin1);
  myServo2.attach(servoPin2);

  Serial.begin(115200);
  VC02.begin(9600, SERIAL_8N1, 16, 17);

  myServo1.write(60);
  myServo2.write(90);
}

void loop() {

  if (VC02.available() >= 1) {

    Serial.println("Data from VC-02");

    byte highByte = VC02.read();
    byte lowByte  = VC02.read();

    receivedValue = (highByte << 8) | lowByte;

    Serial.print("Received HEX value 0x: ");
    Serial.println(receivedValue, HEX);
  }

  if (receivedValue == 0x33FF) {
    myServo1.write(115);
    delay(1000);
    myServo1.write(61);
    receivedValue = 0;
  }

  if (receivedValue == 0x44FF) {
    myServo2.write(135);
    delay(1000);
    myServo2.write(91);
    receivedValue = 0;
  }

  if (receivedValue == 0x77FF) {
    SerialBT.write(0xAA77); 
    receivedValue = 0;
  }

  if (receivedValue == 0x70FF) {
    SerialBT.write(0xAA70);
    receivedValue = 0;
  }

  if (receivedValue == 0x88FF) {
    SerialBT.write(0xAA88);
    receivedValue = 0;
  }

  if (receivedValue == 0x80FF) {
    SerialBT.write(0xAA80);
    receivedValue = 0;
  }
}