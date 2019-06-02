

//Motor Connections
//Change this if you wish to use another diagram
//#define EnA  10
//#define EnB  5



#define ON HIGH
#define OFF LOW

#define TYPE 1
void valveSetup()
{
  
  // All motor control pins are outputs
  //  pinMode(EnA, OUTPUT);
  //  pinMode(EnB, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
  digitalWrite(EN, LOW);
}

void valveRelayOn()
{

  digitalWrite(D5, ON);
  digitalWrite(D6, ON);

  //LED_STATUS ON
  ledState = 2;
  digitalWrite(LED_STATUS, !ledState);
  Serial.print("Valve Relay On");
}

void valveRelayOff()
{

  digitalWrite(D5, OFF);
  digitalWrite(D6, OFF);
  //LED_STATUS OFF
  ledState = 0;
  digitalWrite(LED_STATUS, !ledState);
  Serial.print("Valve Relay Off");
}

void valveDriverOn()
{
  digitalWrite(EN, HIGH);
  // turn on motor A
  digitalWrite(D5, HIGH);
  digitalWrite(D6, LOW);
  // set speed to 150 out 255
  //  analogWrite(EnA, 200);
  // turn on motor B
  digitalWrite(D7, HIGH);
  digitalWrite(D8, LOW);
  // set speed to 150 out 255
  //  analogWrite(EnB, 200);
  delay(1000);
  // now turn off motors
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);


  digitalWrite(EN, LOW);

  //LED_STATUS ON
  ledState = 1;
  digitalWrite(LED_STATUS, !ledState);
  Serial.print("Valve Driver On");
}

void valveDriverOff()
{
   digitalWrite(EN, HIGH);
  // turn on motor A
  digitalWrite(D5, LOW);
  digitalWrite(D6, HIGH);
  // set speed to 150 out 255
  //  analogWrite(EnA, 200);
  // turn on motor B
  digitalWrite(D7, LOW);
  digitalWrite(D8, HIGH);
  // set speed to 150 out 255
  //  analogWrite(EnB, 200);
  delay(1000);
  // now turn off motors
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);


  digitalWrite(EN, LOW);

  //LED_STATUS OFF
  ledState = 0;
  digitalWrite(LED_STATUS, !ledState);
  Serial.print("Valve Driver Off");
}

void valveOn()
{
  // if (TYPE == 1)
  // {
  //   valveRelayOn();
  // }
  // else
  // {
    valveDriverOn();
  // }
}

void valveOff()
{
  // if (TYPE == 1)
  // {
  //   valveRelayOff();
  // }
  // else
  // {
    valveDriverOff();
  // }
}
