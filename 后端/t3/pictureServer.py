from flask import Flask, render_template
from flask import request, redirect, url_for
import random
import urllib
import json

user = {'user1' : '123', 'user2' : '456'}
aukeys = {}

app = Flask(__name__, static_folder='../frontend', static_url_path='')

@app.route('/authorization') 
def index():
    userName = request.args.get('username')
    password = str(request.args.get('password'))
    url = request.args.get('url')
    if(userName and password):
        if(userName in user and user[userName] == password):
            aukey = str(random.random())
            aukeys[aukey] = userName
            openurl = url + '/' + aukey
            print(openurl)
            urllib.request.urlopen(openurl) #发送授权码
            return '授权成功！\n发送的授权码为：' + str(aukey)
        else: #未登录 跳转到login
            return redirect(url_for('login') + '?url=' + url + '&status=1')
    else:
        return redirect(url_for('login') + '?url=' + url + '&status=1')

@app.route('/login')
def login():
    url = request.args.get('url')
    status = request.args.get('status')
    return render_template('pictureIndex.html', url = url, status = status)



app.run(debug=True, port=6002)