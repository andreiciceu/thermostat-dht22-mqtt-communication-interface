module.exports = {
  // mosquitto_sub -h ycasper.go.ro -u flying_high -P bite_nails -t '#'
  mqtt: {
    TOPICS: {
      HEATING_INPUT: '/relay/heating/in',
      HEATING_OUTPUT: '/relay/heating/out',
      TEMPERATURE_INPUT: '/temp/in',
      TEMPERATURE_OUTPUT: '/temp/out',
    },
  },
  log: {
    logInterval: (60 * 3) - 5, // seconds
  },
};
