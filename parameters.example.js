module.exports = {
  mqtt: {
    SERVER: 'localhost',
    PORT: 1883,
    USER: 'user',
    PASSWORD: 'password',
    TOPIC_INPUT: '/heating/in',
    TOPIC_OUTPUT: '/heating/out',
    RECONNECT_INTERVAL: 120,
  },
  mysql: {
    SERVER: 'localhost',
    USER: '',
    PASSWORD: '',
    DATABASE: 'thermostat',
    STATE_TABLE: 'temperatures',
  },
  log: {
    logInterval: (60 * 3) - 5, // seconds
  }
};
