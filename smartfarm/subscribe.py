from command import *
import paho.mqtt.client as mqtt
import os.path
import time
import json
from devices.WaterPump import WaterPump
#from Drone import Drone
#from DroneCommandProcessor import DroneCommandProcessor

# Replace /Users/gaston/certificates with the path
# in which you saved the certificate authoritity file,
# the client certificate file and the client key
certificates_path = "/Users/gaston/certificates"
ca_certificate = os.path.join(certificates_path, "ca.crt")
client_certificate = os.path.join(certificates_path, "device001.crt")
# Replace localhost with the IP for the Mosquitto
# or other MQTT server
mqtt_server_host = "192.168.1.113"
mqtt_server_port = 1883
mqtt_keepalive = 60

def on_connect(client, userdata, rc):
    print("Connect result: {}".format(mqtt.connack_string(rc)))
    client.subscribe("pump/water1")

def on_subscribe(client, userdata, mid, granted_qos):
    print("Subscribed with QoS: {}".format(granted_qos[0]))

def on_message(client, userdata, msg):
    payload_string = msg.payload.decode('utf-8')
    print("Topic: {}. Payload: {}".format(
        msg.topic, 
        payload_string))

if __name__ == "__main__":
    client = mqtt.Client(protocol=mqtt.MQTTv311)
    client.on_connect = on_connect
    client.on_subscribe = on_subscribe
    client.on_message = on_message
    waterPump = WaterPump("water1",client)
  #  drone = Drone("drone1")
  #  droneProcessor = DroneCommandProcessor("drone1",drone,client)

#    client.tls_set(ca_certs = ca_certificate,
#        certfile=client_certificate,
#        keyfile=client_key)
    client.connect_async(host=mqtt_server_host,
        port=mqtt_server_port,
        keepalive=mqtt_keepalive) 
    client.loop_forever()



# if __name__ == "__main__":
    

#     # DroneCommandProcessor.commands_topic = "commands/{}".format(self.name)
#     # DroneCommandProcessor.processed_commands_topic = "processedcommands/{}".format(self.name)
#     client = mqtt.Client(protocol=mqtt.MQTTv311)
#     client.on_connect = DroneCommandProcessor.on_connect
#     client.on_message = DroneCommandProcessor.on_message

# #       client.tls_set(ca_certs = ca_certificate,
# #           certfile=client_certificate,
# #           keyfile=client_key)
#     client.connect(host=mqtt_server_host,
#                         port=mqtt_server_port,
#                         keepalive=mqtt_keepalive)



#     drone = Drone("drone01")
#     drone_command_processor = DroneCommandProcessor("drone01", drone)
#     while True:
#         # Process messages and the commands every 1 second
#         drone_command_processor.process_commands()
#         print("Command process")
#         time.sleep(1)
