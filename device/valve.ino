

//Motor Connections
//Change this if you wish to use another diagram
//#define EnA  10
//#define EnB  5
#define In1  15
#define In2  13
#define In3  12
#define In4  13
#define EN   16


#define ON LOW
#define OFF HIGH

#define TYPE 1
void valveSetup()
{
  // All motor control pins are outputs
  //  pinMode(EnA, OUTPUT);
  //  pinMode(EnB, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  digitalWrite(In1, OFF);
  digitalWrite(In2, OFF);
  digitalWrite(In3, OFF);
  digitalWrite(In4, OFF);
}

void valveRelayOn()
{

  digitalWrite(In1, ON);
  digitalWrite(In2, ON);

  //LED_STATUS ON
  ledState = 1;
  digitalWrite(LED_STATUS, !ledState);
  Serial.print("Valve On");
}

void valveRelayOff()
{

  digitalWrite(In1, OFF);
  digitalWrite(In2, OFF);
  //LED_STATUS OFF
  ledState = 0;
  digitalWrite(LED_STATUS, !ledState);
  Serial.print("Valve Off");
}

void valveDriverOn()
{
  digitalWrite(EN, HIGH);
  // turn on motor A
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  // set speed to 150 out 255
  //  analogWrite(EnA, 200);
  // turn on motor B
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  // set speed to 150 out 255
  //  analogWrite(EnB, 200);
  delay(500);
  // now turn off motors
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);


  digitalWrite(EN, LOW);

  //LED_STATUS ON
  ledState = 1;
  digitalWrite(LED_STATUS, !ledState);
  Serial.print("Valve On");
}

void valveDriverOff()
{
  digitalWrite(EN, HIGH);
  // turn on motor A
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  // set speed to 150 out 255
  //  analogWrite(EnA, 200);
  // turn on motor B
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  // set speed to 150 out 255
  //  analogWrite(EnB, 200);
  delay(500);
  // now turn off motors
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  digitalWrite(EN, LOW);

  //LED_STATUS OFF
  ledState = 0;
  digitalWrite(LED_STATUS, !ledState);
  Serial.print("Valve Off");
}

void valveOn()
{
  if (TYPE == 1)
  {
    valveRelayOn();
  }
  else
  {
    valveDriverOn();
  }
}

void valveOff()
{
  if (TYPE == 1)
  {
    valveRelayOff();
  }
  else
  {
    valveDriverOff();
  }
}
