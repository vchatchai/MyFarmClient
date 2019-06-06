#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic



// void configModeCallback (WiFiManager *wiFiManager){
//   Serial.println("Entered config mode");
//   Serial.println(WiFi.softAPIP());
//   //if you used auto generated SSID, print it
//   Serial.println(wiFiManager->getConfigPortalSSID());
//   //entered config mode, make led toggle faster
//   ticker.attach(0.2, tick);
// }


//flag for saving data
bool shouldSaveConfig = false;

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}


void setup_wifi() {
  // delay(10);
  // Serial.print("Connecting to ");
  // Serial.print(config.config_wifi_ssid);
  // WiFi.begin(config.config_wifi_ssid, config.config_wifi_password);
  // while (WiFi.status() != WL_CONNECTED) {

  //   //LED_POWER ON
  //   digitalWrite(LED_POWER, HIGH);
  //   delay(500);
  //   //LED_POWER OFF
  //   digitalWrite(LED_POWER, LOW);
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println("OK");
  // Serial.print("   IP address: ");
  // Serial.println(WiFi.localIP());



  //read configuration from FS json
  // Serial.println("mounting FS...");


  statusTicker.attach(0.6, statusTick);


  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", config.config_mqtt_server, 40);
  // WiFiManagerParameter custom_mqtt_port("port", "mqtt port", config.config_mqtt_port, 6);
  WiFiManagerParameter custom_mqtt_user("user", "mqtt user", config.config_mqtt_user, 20);
  WiFiManagerParameter custom_mqtt_pass("password", "mqtt password", config.config_mqtt_password, 20);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  // wifiManager.setAPCallback(configModeCallback);



  //set static ip
  // wifiManager.setSTAStaticIPConfig(IPAddress(10,0,1,99), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
  
  //add all your parameters here
  wifiManager.addParameter(&custom_mqtt_server);
  // wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_mqtt_user);
  wifiManager.addParameter(&custom_mqtt_pass);

  //reset settings - for testing
  // wifiManager.resetSettings();

  //set minimu quality of signal so it ignores AP's under that quality
  //defaults to 8%
  //wifiManager.setMinimumSignalQuality();
  
  //sets timeout until configuration portal gets turned off
  //useful to make it all retry or go to sleep
  //in seconds
  //wifiManager.setTimeout(120);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("Node")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }



    
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
    statusTicker.detach();

    if(shouldSaveConfig){
      saveConfiguration();
    }

    digitalWrite(LED_POWER, LED_POWER_ON);

}