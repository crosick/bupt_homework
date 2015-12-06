from app import db

class Record(db.Model):
    __tablename__ = 'records'

    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(32))    
    phone = db.Column(db.String(32))
    email = db.Column(db.String(64))
    qq = db.Column(db.String(32))
    address = db.Column(db.String(128))

    def __repr__(self):
        return '<Record %r>' % self.name

class User(db.Model):
    __tablename__ = 'users'

    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(32), unique=True)    
    password = db.Column(db.String(32))

    def verify_password(self, password):
        return self.password == password

    @property 
    def is_authenticated(self):
        return True 
 
    def is_active(self):
        return True 

    @property 
    def is_anonymous(self):
        return False 

    def get_id(self):
        return unicode(self.id)

    def __repr__(self):
        return '<User %r>' % self.username

    



