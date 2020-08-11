from flask import Flask, request
app = Flask(__name__)

@app.route('/', methods = ['POST'])
def hello():
    req = request.get_json()
    print(req)
    return "Thanks", 200

if __name__ == "__main__":
    app.run(host = '0.0.0.0', port = 8090, debug = True)