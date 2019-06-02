


Ticker otaTicker;

int pushButtonState = LOW;
int ledState = LOW;

//Necesary to make Arduino Software autodetect OTA device
WiFiServer TelnetServer(8266);
void otaTick(){
  int state = digitalRead(LED_POWER);  // get the current state of GPIO1 pin
  digitalWrite(LED_POWER, !state);     // set pin to the opposite state
  digitalWrite(LED_STATUS, !state);     // set pin to the opposite state

}

void OTASetup(){

  Serial.print("Configuring OTA device...");
  TelnetServer.begin();   //Necesary to make Arduino Software autodetect OTA device
  ArduinoOTA.onStart([]() {
    Serial.println("OTA starting...");
    otaTicker.attach(0.6, otaTick);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("OTA update finished!");
    Serial.println("Rebooting...");
    otaTicker.detach();
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("OTA in progress: %u%%\r\n", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();

  Serial.println("OK");

}
