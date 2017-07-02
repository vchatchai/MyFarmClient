#from devices.Pump import Pump
#import wiringpi
import paho.mqtt.client as mqtt
from pyA20.gpio import gpio
from pyA20.gpio import port
class PSUPower:
    def __init__(self, name, client):
        '''

        '''
     #   self.name = name
        topic = 'psu/'+name
        client.message_callback_add(topic+'/power',self.on_message_power)
        client.message_callback_add(topic+'/switch',self.on_message_power)
        # wiringpi.wiringPiSetupGpio()
        # wiringpi.pinMode(PORT,1)
        # wiringpi.digitalWrite(PORT,not data['status'])
        gpio.init()
        gpio.setcfg(port.PA10, gpio.OUTPUT)
        gpio.output(port.PA10, 0)
        gpio.output(port.PA13, 0)
    def on_message_power(self, client, userdata, msg):
        payload_string = msg.payload.decode('utf-8')
        print("Topic1111111: {}. Payload: {}".format(msg.topic, payload_string))
#     wiringpi.digitalWrite(PORT,not data['status'])
        status = gpio.input(port.PA10)
        gpio.output(port.PA10, not status)
    def on_message_start(self, client, userdata, msg):
        payload_string = msg.payload.decode('utf-8')
        print("Topic1111111: {}. Payload: {}".format(msg.topic, payload_string))
#     wiringpi.digitalWrite(PORT,not data['status'])
        status = gpio.input(port.PA13)
        gpio.output(port.PA10, not status)
