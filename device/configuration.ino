#include <ArduinoJson.h>
#include <FS.h>
#include <string.h>

// Our configuration structure.
//
// Never use a JsonDocument to store the configuration!
// A JsonDocument is *not* a permanent storage; it's only a temporary storage
// used during the serialization phase. See:
// https://arduinojson.org/v6/faq/why-must-i-create-a-separate-config-object/



String filename = "/config.json";  // <- SD library uses 8.3 filenames

// Loads the configuration from a file
void loadConfiguration() {
  // Open file for reading

 
  Serial.println("File exist:");

 
  Serial.println(SPIFFS.exists(filename));


  File file = SPIFFS.open(filename,"r");
 

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<512> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

 
  Serial.println( doc["hostname"].as<const char*>());
  Serial.println( doc["port"].as<const char*>());

  
    //WIFI configuration
  config.config_wifi_ssid =  "Home";
  config.config_wifi_password = "manager1";

//MQTT configuration
 config.config_mqtt_server = "m11.cloudmqtt.com";
 config.config_mqtt_port = 11621;
 config.config_mqtt_user = "kysbvegn";
 config.config_mqtt_password = "Ww2mmbIEU9_e";

     //WIFI configuration
/*
  String ssid = doc["wifi_ssid"];
  String ssid_pass = doc["wifi_password"];
  config.config_wifi_ssid = strdup(ssid.c_str());
  config.config_wifi_password = strdup(ssid_pass.c_str());
  // config.config_wifi_password =  ssid_pass.c_str();
  // ssid.toCharArray(config.config_wifi_ssid,ssid.length()+1);
  // ssid_pass.toCharArray(config.config_wifi_password, ssid_pass.length()+1);

//MQTT configuration
  String mqtt = doc["mqtt_server"];
  String mqtt_user = doc["mqtt_user"];
  String mqtt_pass = doc["mqtt_password"];
  config.config_mqtt_server = strdup(mqtt.c_str());
  config.config_mqtt_user = strdup(mqtt_user.c_str());
  config.config_mqtt_password = strdup(mqtt_pass.c_str());
//   mqtt.toCharArray( config.config_mqtt_server,mqtt.length());
//   mqtt_user.toCharArray(config.config_mqtt_user,mqtt_user.length());
//   mqtt_pass.toCharArray(config.config_mqtt_password,mqtt_pass.length());
 config.config_mqtt_port = 11621;

*/
 
  // config.config_mqtt_port = doc["port"] | 11621;
  // strlcpy(config.config_mqtt_server,doc["mqtt_server"] | "m11.cloudmqtt.com",  sizeof(config.config_mqtt_server));         
  // strlcpy(config.config_mqtt_user,doc["mqtt_user"] | "Ww2mmbIEU9_e",  sizeof(config.config_mqtt_user)); 
  // strlcpy(config.config_mqtt_password,doc["mqtt_password"] | "kysbvegn",  sizeof(config.config_mqtt_password)); 
  // strlcpy(config.config_wifi_ssid,doc["wifi_ssid"] ,  sizeof(config.config_wifi_ssid)); 
  // strlcpy(config.config_wifi_password,doc["wifi_password"]  ,  sizeof(config.config_mqtt_user)); 
  
  // Copy values from the JsonDocument to the Config
//   config.port = doc["port"] | 2731;
//   strlcpy(config.hostname,                  // <- destination
//           doc["hostname"] | "example.com",  // <- source
//           sizeof(config.hostname));         // <- destination's capacity

  // Close the file (Curiously, File's destructor doesn't close the file)
  file.close();
}

// Saves the configuration to a file
void saveConfiguration() {
  // Delete existing file, otherwise the configuration is appended to the file
  SPIFFS.remove(filename);

  // Open file for writing
  File file = SPIFFS.open(filename, "w");
  if (!file) {
    Serial.println(F("Failed to create file"));
    return;
  }

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<256> doc;

  // Set the values in the document
  // doc["hostname"] = "localhost";
  // doc["port"] = "1234";

//   //WIFI configuration
// doc["wifi_ssid"] =  "Home";
// doc["wifi_password"] = "manager1";

// //MQTT configuration
 doc["mqtt_server"]= "m11.cloudmqtt.com";
 doc["mqtt_port"]= 11621;
 doc["mqtt_user"]= "kysbvegn";
 doc["mqtt_password"]= "Ww2mmbIEU9_e";


  //WIFI configuration
// doc["wifi_ssid"] =  "Home";
// doc["wifi_password"] = "manager1";

//MQTT configuration
//  doc["mqtt_server"]= config.config_mqtt_server;
//  doc["mqtt_port"]= 11621;
//  doc["mqtt_user"]= config.config_mqtt_user;
//  doc["mqtt_password"]= config.config_wifi_password;

  // Serialize JSON to file
  if (serializeJson(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }

  // Close the file
  file.close();
}

// Prints the content of a file to the Serial
void printFile(const char *filename) {
  // Open file for reading
  File file = SPIFFS.open(filename,"r");
  if (!file) {
    Serial.println(F("Failed to read file"));
    return;
  }

  Serial.println("printFile start");
  // Extract each characters by one by one
  while (file.available()) {
    Serial.print((char)file.read());
  }

  Serial.println(file.readString());
  Serial.println("printFile finished");

  // Close the file
  file.close();
}

void configSetup() {

    Serial.println(F("initialize FS library"));
    // boolean result = SPIFFS.format();
    // Serial.println(result);
    // Serial.println(F("format finished"));
  // Initialize SPIFFS library
  while (!SPIFFS.begin()) {
    Serial.println(F("Failed to initialize SD library"));
    delay(1000);
  }

  // Should load default config if run for the first time
  Serial.println(F("Loading configuration..."));
  loadConfiguration();

  // Create configuration file
  // Serial.println(F("Saving configuration..."));
  // saveConfiguration(filename);

  // Dump config file
  Serial.println(F("Print config file..."));
//   printFile(filename);
}