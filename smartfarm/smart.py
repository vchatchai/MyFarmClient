'''
Created on Dec 14, 2559 BE

@author: chatchai vichai
'''

from flask import Flask
from devices.example import example
from devices.motor import motor
#import ptvsd
#ptvsd.enable_attach("my_secret",address = ('0.0.0.0', 5111))
#ptvsd.wait_for_attach()


app = Flask(__name__)
# app.register_blueprint(example)
app.register_blueprint(motor)

@app.route('/articles')
def api_articles():
    return 'Test '

if __name__ == '__main__':
    app.run("0.0.0.0", debug=True)
