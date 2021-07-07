SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
#include "Wire.h"

void receiveEvent(int howMany)//everytime a recieve event is called, this function plays out
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

void requestEvent()//everytime a request event is called, this function plays out
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
  Wire.begin();      //initializes as master
  Wire1.begin(0x2A); //initializes asslave
  Serial.begin(9600);

  pinMode(D7, OUTPUT);
  pinMode(D6, INPUT);

  Wire1.onReceive(receiveEvent); //the recieve event is called out here
  Wire1.onRequest(requestEvent);//the request event is called here
  while (!Serial.isConnected());
  Serial.println("I2C Master slave available");
}

void loop()
{
  if (Serial.available()) //this is the master telling the slave what to do whem a certian value comes through serial
  {
    char value = Serial.read(); //if the value is 1, a 1 is written to the slave
    if (value == '1')
    {
      Serial.println("1"); 
      Wire.beginTransmission(0x2a);
      Wire.write('1');
      Wire.endTransmission();
    }

    if (value == '0') //if the value is 0, a 0 is written to the slave
    {
      Serial.println("0");
      Wire.beginTransmission(0x2a);
      Wire.write('0');
      Wire.endTransmission();
    }

    if (value == '?')//if the value is ?, a ? is written to the slave
    {
      Serial.println("?");
      Wire.requestFrom(0x2a, 1);
      while (Wire.available() == 0);
      char state = Wire.read();
      Serial.println(state);
    }
  }
}
