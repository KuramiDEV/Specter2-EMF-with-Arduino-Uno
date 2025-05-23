from flask import Flask, render_template, request
import serial

budegaveiadesite = Flask(__name__, template_folder='site')
arduino = serial.Serial('COM3', 9600)

@budegaveiadesite.route('/')
def index():
    return render_template('index.html')

@budegaveiadesite.route('/set_level', methods=['POST'])
def set_level():
    level = request.form['level']
    arduino.write(f"L{level}\n".encode())
    return ('', 204)

@budegaveiadesite.route('/use_pot', methods=['POST'])
def use_pot():
    arduino.write(b'P\n')
    return ('', 204)


budegaveiadesite.run(host='0.0.0.0', port=5000, debug=True)
