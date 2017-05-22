'''
Created on Jan 17, 2560 BE

@author: chatchaivichai
'''
from devices import Device
from abc import abstractmethod

class Pump(Device):
    '''
    classdocs
    '''


    
    @abstractmethod
    def on(self):
        '''
        On Pump
        '''
        pass
    
    @abstractmethod
    def off(self):
        '''
        Off Pump
        '''
        pass
    @abstractmethod
    def status(self):
        '''
        status 
        '''
        pass