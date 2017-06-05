#from devices.Pump import Pump
#import wiringpi
import paho.mqtt.client as mqtt
from pyA20.gpio import gpio
from pyA20.gpio import port
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
        gpio.init()
        gpio.setcfg(port.PA10, gpio.OUTPUT)
    def on_message(self, client, userdata, msg):
        payload_string = msg.payload.decode('utf-8')
        print("Topic1111111: {}. Payload: {}".format(msg.topic, payload_string))
#     wiringpi.digitalWrite(PORT,not data['status'])
        status = gpio.input(port.PA10)
        gpio.output(port.PA10, not status)
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
