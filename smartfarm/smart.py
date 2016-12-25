'''
Created on Dec 14, 2559 BE

@author: chatchai vichai
'''

from flask import Flask

from devices.example import example
from devices.motor import motor


app = Flask(__name__)
# app.register_blueprint(example)
app.register_blueprint(motor)

@app.route('/articles')
def api_articles():
    return 'Test ' 

if __name__ == '__main__':
    app.run();