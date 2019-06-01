#include <ArduinoJson.h>
#include <FS.h>

// Our configuration structure.
//
// Never use a JsonDocument to store the configuration!
// A JsonDocument is *not* a permanent storage; it's only a temporary storage
// used during the serialization phase. See:
// https://arduinojson.org/v6/faq/why-must-i-create-a-separate-config-object/
// struct Config {
//   char hostname[64];
//   int port;
// };

 String filename = "/config.txt";  // <- SD library uses 8.3 filenames
// Config config;                         // <- global configuration object

// Loads the configuration from a file
void loadConfiguration(String filename) {
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
  

  // Copy values from the JsonDocument to the Config
//   config.port = doc["port"] | 2731;
//   strlcpy(config.hostname,                  // <- destination
//           doc["hostname"] | "example.com",  // <- source
//           sizeof(config.hostname));         // <- destination's capacity

  // Close the file (Curiously, File's destructor doesn't close the file)
  file.close();
}

// Saves the configuration to a file
void saveConfiguration(String filename) {
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
  doc["hostname"] = "localhost";
  doc["port"] = "1234";

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
  loadConfiguration(filename);

  // Create configuration file
  Serial.println(F("Saving configuration..."));
  saveConfiguration(filename);

  // Dump config file
  Serial.println(F("Print config file..."));
//   printFile(filename);
}