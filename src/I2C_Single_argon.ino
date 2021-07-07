SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
#include "Wire.h"

void receiveEvent(int howMany)
{
  char x = Wire1.read();
  Serial.print("slave");
  Serial.println(x);
  if (x == '1')
  {
    digitalWrite(D7, HIGH);
  }
  if (x == '0')
  {
    digitalWrite(D7, LOW);
  }
}

void requestEvent()
{
  if (digitalRead(D6) == HIGH)
  {
    Wire1.write('H');
  }
  if (digitalRead(D6) == LOW)
  {
    Wire1.write('L');
  }
}

void setup()
{
  Wire.begin();      //master
  Wire1.begin(0x2A); //slave
  Serial.begin(9600);

  pinMode(D7, OUTPUT);
  pinMode(D6, INPUT);

  Wire1.onReceive(receiveEvent);
  Wire1.onRequest(requestEvent);
  while (!Serial.isConnected());
  Serial.println("I2C Master slave available");
}

void loop()
{
  if (Serial.available())
  {
    char value = Serial.read();
    if (value == '1')
    {
      Serial.println("1");
      Wire.beginTransmission(0x2a);
      Wire.write('1');
      Wire.endTransmission();
    }

    if (value == '0')
    {
      Serial.println("0");
      Wire.beginTransmission(0x2a);
      Wire.write('0');
      Wire.endTransmission();
    }

    if (value == '?')
    {
      Serial.println("?");
      Wire.requestFrom(0x2a, 1);
      while (Wire.available() == 0);
      char state = Wire.read();
      Serial.print(state);
    }
  }
}
