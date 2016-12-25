from flask import Blueprint, render_template, abort
from jinja2 import TemplateNotFound


example = Blueprint('example', __name__)

@example.route('/', defaults={'page': 'index'})
@example.route('/<page>')
def show(page):
    return "Test by Chatchai Vichai" 
#     try:
#         return render_template('pages/%s.html' % page)
#     except TemplateNotFound:
#         abort(404)


