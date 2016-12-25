from flask import Blueprint, render_template, abort
from flask import Flask, jsonify
from flask import Response
from flask import json


# from jinja2 import TemplateNotFound
motor = Blueprint('motor', __name__)
 
@motor.route('/motor/<name>')
def status(name):
# return "Test motsor by " + name
#     try:
#         return render_template('pages/%s.html' % page)
#     except TemplateNotFound:
#         abort(404)
    data = {
    'hello'  : name,
    'number' : 3
    }
    js = json.dumps(data)
    
    resp = Response(js, status=200, mimetype='application/json')
    resp.headers['Link'] = 'http://luisrei.com'
    
    return resp

