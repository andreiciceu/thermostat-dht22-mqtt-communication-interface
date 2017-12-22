const CommunicationInterface = require('../../CommunicationInterface');
const mqtt = require('mqtt');
const params = require('./parameters.js');
const fs = require('fs');
const path = require('path');

class Communication extends CommunicationInterface {
  constructor(opt) {
    super();
    const mqttClient = mqtt.connect(params.mqtt.SERVER, {
      username: params.mqtt.USER,
      password: params.mqtt.PASSWORD,
      keepalive: 0,
      protocol: 'MQTT',
    });
    mqttClient.subscribe(params.mqtt.TOPIC_OUTPUT);
    mqttClient.on('message', (topic, message) => {
      const strMessage = message.toString();
      if (opt && opt.debug) console.log('[MQTT] message recv', topic, '=>', strMessage);

      switch (topic) {
        case params.mqtt.TOPIC_OUTPUT:
          let status = false;
          if (strMessage === '1' || strMessage === 1) status = true;
          else if (strMessage === '0' || strMessage === 0) status = false;
          else throw new Error('Invalid message received on output topic');
          this._heatingStateUpdate(status);
          break;
        default:
      }
    });
    this.mqttClient = mqttClient;
    this._lastTempTimestamp = null;
  }


  requestTemp() {
    const data = fs.readFileSync(path.join(__dirname, '/temp-reading/dht22/temp'), 'utf8');
    const lines = data.split('\n');
    if (lines.length < 2) return false;

    const timestamp = lines[0].trim();
    if (this._lastTempTimestamp === timestamp) return false;

    const regex = /Temperature = (\d*.\d*)/;
    let temp = regex.exec(lines[1]);
    if (!temp || !temp.length || temp.length < 2) return false;

    temp = parseFloat(temp[1]);
    this._lastTempTimestamp = timestamp;
    this._temperatureUpdate(temp, new Date(timestamp));

    return true;
  }

  // Heating
  requestHeatingState() {
    this.mqttClient.publish(params.mqtt.TOPIC_INPUT, 'status');
  }

  toggleHeating(state) {
    this.mqttClient.publish(params.mqtt.TOPIC_INPUT, state ? 'on' : 'off');
  }

  requestSomeoneIsHome() {
    // TODO
    this._someoneIsHomeStatusUpdate(true);
  }

  logState(state) {
    fs.appendFile(
      path.join(__dirname, '../../var/logs/state.log'), `${Communication.prettyDate()}] dTemp: ${state.desiredTemp}, cTemp: ${state.cTemp} (${Communication.prettyDate(state.lastTempUpdate)}) | heatingOn: ${state.heatingOn}, someoneIsHome: ${state.someoneIsHome}\n`,
      (err) => {
        if (err) console.warn(err, 'Failed to save log');
      },
    );
  }

  // UTILS
  static prettyDate(date) {
    const d = date ? new Date(date) : new Date();
    return `${d.getFullYear()}-${d.getMonth() + 1}-${d.getDate()} ${d.getHours()}:${d.getMinutes()}:${d.getSeconds()}`;
  }
}


module.exports = new Communication();

