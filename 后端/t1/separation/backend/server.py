from flask import Flask
from flask import request
import json

app = Flask(__name__, static_folder='../frontend', static_url_path='', )
sql = [[], [], [], ['123456', '654321']]


@app.route('/loginInfoSubmit')
def Login():
    data = [request.args.get('name'),
            request.args.get('gender'),
            request.args.get('age'),
            request.args.get('phone')]
    ret = []
    for i in range(len(data)):
        if (data[i] in sql[i]):
            ret.append(2)
        elif (data[i] == ''):
            ret.append(1)
        else:
            ret.append(0)
            if (i == 3):
                sql[i].append(data[i])
    print(sql)
    return json.dumps(ret)


app.run(debug=True)
