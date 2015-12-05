from flask import Flask, render_template, send_from_directory, redirect
from flask.ext.sqlalchemy import SQLAlchemy
from flask.ext.script import Manager, Shell
from flask.ext.migrate import Migrate, MigrateCommand

from config import config
from forms import LoginForm, RecordForm
from models import *

app = Flask(__name__)

db = SQLAlchemy(app)
manager = Manager(app)
app.config.from_object(config['default'])


def make_shell_context():
    return dict(app=app, db=db, Record=Record, User=User)

manager.add_command("shell", Shell(make_context= make_shell_context))
manager.add_command('db', MigrateCommand)


@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login')
def login():
    return render_template("login.html")


@app.route('/add')
def add_addr():
    form = RecordForm()
    if form.validate_on_submit():
        return redirect('/')
    return render_template('add_addr.html', form=form)

@app.route('/edit/<int:id>')
def edit_addr(id):
    return render_template('edit_addr.html') 

@app.route('/image/<path:path>')
def send_img(path):
    return send_from_directory('static/image',path)

@app.route('/font/<path:path>')
def send_font(path):
    return send_from_directory('static/font',path)

@app.route('/css/<path:path>')
def send_css(path):
    return send_from_directory('static/css',path)

@app.route('/js/<path:path>')
def send_js(path):
    return send_from_directory('static/js',path)


if __name__ == '__main__':
    manager.run()

