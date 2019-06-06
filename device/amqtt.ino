#include <PubSubClient.h> //For MQTT



//MQTT client
WiFiClient espClient;
PubSubClient mqtt_client(espClient);
void mqttSetup(){
  statusTicker.attach(3, statusTick);

  mqtt_client.setServer(config.config_mqtt_server, config.config_mqtt_port);
  mqtt_client.setCallback(callback);


  statusTicker.detach();

  digitalWrite(LED_POWER, LED_POWER_ON);     // set pin to the opposite state
}


void mqtt_reconnect() {

  statusTicker.attach(3, statusTick);
  // Loop until we're reconnected
  while (!mqtt_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {d
    if (mqtt_client.connect(mqtt_client_id.c_str(), config.config_mqtt_user, config.config_mqtt_password)) {
      Serial.println("connected");
      String subscribe_path = valve_topic ;
      // Length (with one extra character for the null terminator)
      int str_len = subscribe_path.length() + 1;

      // Prepare the character array (the buffer)
      char char_array[str_len];

      // Copy it over
      subscribe_path.toCharArray(char_array, str_len);

      Serial.print("subscribe: ");
      Serial.println(char_array);
      mqtt_client.subscribe(char_array);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");

      // Wait 5 seconds before retrying

      // //LED_POWER ON
      // digitalWrite(LED_POWER, HIGH);
      // delay(2500);
      // //LED_POWER OFF
      // digitalWrite(LED_POWER, LOW);
      // delay(2500);

    }
  }

  statusTicker.detach();

  digitalWrite(LED_POWER, LED_POWER_ON);     // set pin to the opposite state
}

void mqttLoop(){ 

  if (!mqtt_client.connected()) {
    mqtt_reconnect();
  }
  mqtt_client.loop();
}


// This functions is executed when some device publishes a message to a topic that your ESP8266 is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that
// your ESP8266 is subscribed you can actually do something
void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic room/lamp, you check if the message is either on or off. Turns the lamp GPIO according to the message
  if (topic == valve_topic) {
    powerTicker.detach();
    Serial.print("Changing Valve to ");
    if (messageTemp == "1") {
      valveOn();
    } else if (messageTemp == "0") {
      valveOff();
    }
  }else if (topic == pump_topic ) {
    powerTicker.detach();
    Serial.print("Changing Valve to ");
    if (messageTemp == "on") {
      pumpOn();
    } else if (messageTemp == "off") {
      pumpOff();
    }
  }
  Serial.println();
}
