from flask import Flask, render_template
from flask import request, redirect, url_for
import urllib
import json
import random
import urllib

staus = {}
aukeys = {}
data = {}

app = Flask(__name__, static_folder='../frontend', static_url_path='', )

@app.route('/print/<key>')
def kindex(key):
    staus[key] = 0 #标记获取授权的状态
    return render_template('ptIndex.html', key = key)


@app.route('/check/<key>')
def check(key): #获取授权状态
    if(key in staus and staus[key] == 1):
        return json.dumps(aukeys[key])
    else:
        return json.dumps('fail')

@app.route('/print')
def index():
    return redirect(url_for('kindex', key = str(random.random()))) #跳转到带ID的print网页 用来唯一的识别用户

@app.route('/getkey/<idkey>/<key>')
def printPics(idkey, key):
    staus[idkey] = 1 #成功获取授权码
    aukeys[idkey] = key
    return 'ok'

app.run(debug=True, port = 6001)