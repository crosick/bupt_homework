from flask import render_template, redirect, send_from_directory, session, g, url_for, flash
from flask.ext.login import login_user, login_required, current_user, logout_user
from .forms import RecordForm, LoginForm
from app import app, db, lm
from models import Record, User

@lm.user_loader
def load_user(id):
    return User.query.get(int(id))

@app.before_request
def before_request():
    g.user = current_user

@app.route('/')
@app.route('/index')
def index():
    if g.user is None or not g.user.is_active():
        return redirect(url_for('login'))
    records = Record.query.all()
    return render_template('index.html', records=records)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if g.user is not None and g.user.is_active():
        return redirect(url_for('index'))
    form = LoginForm()
    if form.validate_on_submit():
        user = User.query.filter_by(username=form.username.data).first()
        if user is not None and user.verify_password(form.password.data):
            login_user(user, True)
            return redirect(url_for('index'))
        flash('Invalid username or password.')
    return render_template('login.html', form=form)

@login_required
@app.route('/logout')
def logout():
    logout_user()
    return redirect(url_for('login'))


@login_required
@app.route('/add', methods=["POST", "GET"])
def add_addr():
    form = RecordForm()
    if form.validate_on_submit():
        record = Record(name = form.name.data, 
                        phone = form.phone.data,
                        email = form.email.data,
                        qq = form.qq.data,
                        address = form.address.data)
        db.session.add(record)
        db.session.commit()
        return redirect('/')
    return render_template('add_addr.html', form=form)

@login_required
@app.route('/delete/<int:id>')
def del_addr(id):
    record = Record.query.get_or_404(id)
    db.session.delete(record)
    db.session.commit()
    return redirect(url_for('index'))

@login_required
@app.route('/edit/<int:id>', methods=["POST", "GET"])
def edit_addr(id):
    form = RecordForm()
    record = Record.query.get_or_404(id)
    if form.validate_on_submit():
        record.name = form.name.data
        record.phone = form.phone.data
        record.email = form.email.data
        record.qq = form.qq.data
        record.address = form.address.data
        db.session.commit()
        return redirect(url_for('index'))
    
    form.name.data = record.name
    form.phone.data = record.phone
    form.email.data = record.email
    form.qq.data = record.qq
    form.address.data = record.address
    return render_template('edit_addr.html', form=form, id=id)


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
