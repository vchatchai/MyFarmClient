#include <TransmissionResult.h>
#include <NetworkInfo.h>
#include <ESP8266WiFiMesh.h>
#include <TypeConversionFunctions.h>

#include <Hash.h>

#include <ESP8266WiFi.h>  //For ESP8266
#include <ESP8266mDNS.h>  //For OTA
#include <WiFiUdp.h>      //For OTA
#include <ArduinoOTA.h>   //For OTA


//WIFI configuration
#define wifi_ssid "Chatchai"
#define wifi_password "manager1"

//MQTT configuration
#define mqtt_server "m11.cloudmqtt.com"
#define mqtt_port 11621
#define mqtt_user "kysbvegn"
#define mqtt_password "Ww2mmbIEU9_e"
String mqtt_client_id = "ESP8266-"; //This text is concatenated with ChipId to get unique client_id
//MQTT Topic configuration

String root = "/";
String farm = root+"farm_home";
String humidity_topic = farm + "/sensor/humidity/" ;
String temperature_topic = farm + "/sensor/temperature/" ;
String valve_topic = farm + "/valve/";
String pump_topic = farm + "/pump/";
//PIN BUTTON
#define BUTTON_PIN 5
//DHT SENSOR
#define DHTPIN  4

//LED PORT
#define LED_STATUS 0
#define LED_POWER 2

void setup() {
  Serial.begin(115200);
  Serial.println("\r\nBooting...");

  Serial.println("\r\nSet Value PinMode.");
  valveSetup();
  // initialize digital pin LED as an output.
  pinMode(LED_POWER, OUTPUT);
  pinMode(LED_STATUS, OUTPUT);

  dhtSetup();

  pushButtonSetup();
  setup_wifi();


  OTASetup();

  Serial.println("Configuring MQTT server...");
  mqtt_client_id = ESP.getChipId();
  humidity_topic = humidity_topic + ESP.getChipId();
  temperature_topic = temperature_topic + ESP.getChipId();
  mqttSetup();
  Serial.printf("   Server IP: %s\r\n", mqtt_server);
  Serial.printf("   Username:  %s\r\n", mqtt_user);
  Serial.println("   Cliend Id: " + mqtt_client_id);
  Serial.println("   MQTT configured!");

  Serial.println("Setup completed! Running app...");
  //Initial completed.
  //LED_POWER ON
  digitalWrite(LED_POWER, LOW);
}

void loop() {

  ArduinoOTA.handle();

  mqttLoop();
  dhtLoop();
  pushButtonLoop();
}
