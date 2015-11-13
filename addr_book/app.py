from flask import Flask, render_template, send_from_directory

app = Flask(__name__)

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
def senf_img(path):
    return send_from_directory('static/image',path)

@app.route('/font/<path:path>')
def senf_font(path):
    return send_from_directory('static/font',path)

if __name__ == '__main__':
    app.run(debug=True)