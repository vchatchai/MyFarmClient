from pyA20 import i2c
import time
import paho.mqtt.client as mqtt
from pyA20.gpio import gpio
from pyA20.gpio import port
import paho.mqtt.publish as publish

class Pressure:
    def __init__(self, name, hostname):
        '''

        '''
        self.name = name
        self.hostname = hostname

        # topic = 'pump/'+name
        # client.message_callback_add(topic,self.on_message)
        # # wiringpi.wiringPiSetupGpio()
        # # wiringpi.pinMode(PORT,1)
        # # wiringpi.digitalWrite(PORT,not data['status'])
        # gpio.init()
        # gpio.setcfg(port.PA10, gpio.OUTPUT)

        i2c.init("/dev/i2c-0")  #Initialize module to use /dev/i2c-2
        i2c.open(0x48)  #The slave device address is 0x55
        
        #If we want to write to some register
        #i2c.write([0xAA, 0x20]) #Write 0x20 to register 0xAA
        #i2c.write([0xAA, 0x10, 0x11, 0x12]) #Do continuous write with start address 0xAA

        #If we want to do write and read
        data = [0x84,0xc2]
        i2c.write([0x01, 0xc2, 0x85 ]) #Set address at 0xAA register
        i2c.write([0x00])
        
        #	i2c.write([0x00])
       #     print(str(i2c.read(4)))
        #print(str(i2c.read(2)))
        #print(str(i2c.read(3)))
        #print(str(i2c.read(4)))

#            publish.single("pressure/name", data, hostname="test.mosquitto.org")

    def close(self):
        i2c.close()

    def publish(self):
        data = i2c.read(2)
        topic = 'pressure/'+self.name
        data = int.from_bytes(data,byteorder='big', signed=True)
        print(str(topic)+ " : " +str(data) + " : " + self.hostname)
        infot = publish.single(topic, data, qos=2, hostname =  self.hostname)
        
        return infot

    def on_message(self, client, userdata, msg):
        payload_string = msg.payload.decode('utf-8')
        print("Topic1111111: {}. Payload: {}".format(msg.topic, payload_string))
#     wiringpi.digitalWrite(PORT,not data['status'])
        # status = gpio.input(port.PA10)
        # gpio.output(port.PA10, not status)
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