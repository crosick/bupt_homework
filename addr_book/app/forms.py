from flask.ext.wtf import Form
from wtforms import StringField, SubmitField, PasswordField
from wtforms.validators import Required, Length, Email
from wtforms import ValidationError

class LoginForm(Form):
    username = StringField('username', validators=[Required()])
    password = PasswordField('password', validators=[Required()])
    submit = SubmitField('Login')

class RecordForm(Form):
    name = StringField('name', validators=[Required(), Length(1,32)])
    phone = StringField('phone')
    email = StringField('email')
    qq = StringField('qq')
    address = StringField('address')
    
  