from flask import Blueprint, render_template, abort
from flask import Flask, jsonify
from flask import Response
from flask import json
#import devices.WaterPump
#from devices.WaterPump import WaterPump
#from devices.Pump import Pump

#import wiringpi

# from jinja2 import TemplateNotFound

motor = Blueprint('motor', __name__)

# wiringpi.wiringPiSetupSys()
# wiringpi.wiringPiSetup()

PORT = 10

data = {
'name'  : "test",
'status' : True
}
# wiringpi.wiringPiSetupGpio()
# wiringpi.pinMode(PORT,1)
# wiringpi.digitalWrite(PORT,not data['status'])
print("Motor started!")

#pump = WaterPump()
@motor.route('/motor/<name>')
def status(name):
    data['name']= name
#     wiringpi.digitalWrite(PORT,not data['status'])
    data['status'] = True
    js = json.dumps(data)
    resp = Response(js, status=200, mimetype='application/json')
    resp.headers['Link'] = 'http://luisrei.com'
    
    return resp
@motor.route('/motor/<name>/on')
def on(name):
    data['name']= name
    data['status'] = True
#     wiringpi.digitalWrite(PORT,not data['status'])
    js = json.dumps(data)
    resp = Response(js, status=200, mimetype='application/json')
    resp.headers['Link'] = 'http://luisrei.com'
    return resp

@motor.route('/motor/<name>/off')
def off(name):
    data['name']= name
    data['status'] = 0
#     wiringpi.digitalWrite(PORT,not data['status'])
    js = json.dumps(data)
    resp = Response(js, status=200, mimetype='application/json')
    resp.headers['Link'] = 'http://luisrei.com'
    
    return resp

@motor.route('/motor/<name>/toggle')
def toggle(name):
    data['name']= name
    data['status'] = not data['status']
#     wiringpi.digitalWrite(PORT,not data['status'])
    js = json.dumps(data)
    resp = Response(js, status=200, mimetype='application/json')
    resp.headers['Link'] = 'http://luisrei.com'
    
    return resp


