from flask import Flask
from flask.ext.sqlalchemy import SQLAlchemy
from flask.ext.login import LoginManager
from config import config

app = Flask(__name__)
app.config.from_object(config['default'])

db = SQLAlchemy(app)
lm = LoginManager(app)

from app import views, models
