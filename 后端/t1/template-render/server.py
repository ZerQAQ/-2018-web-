from flask import Flask, render_template
from flask import request
import json

sql = [ [], [], [], ['123456', '654321']]

app = Flask(__name__, static_folder='../frontend', static_url_path='', )

key_name_zh = ['姓名', '性别', '年龄', '电话']
msg = ['不能为空', '已经被提交过', '√']

@app.route('/')
def index():
    return render_template('index.html', data = [])

@app.route('/loginInfoSubmit')
def Login():
    data = [request.args.get('name'),
            request.args.get('gender'),
            request.args.get('age'),
            request.args.get('phone')]
    ret = []
    p = 1
    for i in range(len(data)):
        if (data[i] in sql[i]):
            ret.append(key_name_zh[i] + msg[1])
            p = 0
        elif (data[i] == ''):
            ret.append(key_name_zh[i] + msg[0])
            p = 0
        else:
            ret.append('')
            if (i == 3):
                sql[i].append(data[i])
    if(p == 1):
        ret.append('提交成功！')
    return render_template('index.html', data = ret)


app.run(debug=True)
