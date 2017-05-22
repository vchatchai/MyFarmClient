#from devices.Pump import Pump
#import wiringpi
import paho.mqtt.client as mqtt

class WaterPump:
    def __init__(self, name, client):
        '''

        '''
     #   self.name = name
        topic = 'pump/'+name
        client.message_callback_add(topic,self.on_message)
        # wiringpi.wiringPiSetupGpio()
        # wiringpi.pinMode(PORT,1)
        # wiringpi.digitalWrite(PORT,not data['status'])
    def on_message(self, client, userdata, msg):
        payload_string = msg.payload.decode('utf-8')
        print("Topic1111111: {}. Payload: {}".format(msg.topic, payload_string))
#     wiringpi.digitalWrite(PORT,not data['status'])
    def on(self):
        '''
        On Pump
        '''
    def off(self):
        '''
        Off Pump
        '''
    def status(self):
        '''
        status 
        '''
        return True
