from flask.ext.wtf import Form
from wtforms import StringField, SubmitField, PasswordField
from wtforms.validators import Required, Length, Email
from wtforms import ValidationError

class LoginForm(Form):
    username = StringField('username', validators=[Required(), Email()])
    password = PasswordField('password', validators=[Required()])
    submit = SubmitField('Login')

class RecordForm(Form):
    name = StringField('name', validators=[Required(), Length(1,32)])
    phone = StringField('phone', validators=[Length(1,32)])
    email = StringField('email', validators=[Length(1,64), Email()])
    qq = StringField('qq', validators=[Length(1,32)])
    address = StringField('address', validators=[Length(1,128)])
    submit = SubmitField('Add a new contact')
  