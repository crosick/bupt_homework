from Flask import render_template
from app import app 


@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login')
def login():
    return render_template('login.html')

@app.route('/add')
def add_addr():
    return render_template('add_addr.html')

@app.route('/image/<path:path>')
def send_img(path):
    return send_from_directory('static/image',path)

@app.route('/font/<path:path>')
def send_font(path):
    return send_from_directory('static/font',path)