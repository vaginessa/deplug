const path = require('path')
const kitpath = path.join(__dirname, '../bin/plugkit/plugkit.node')
  .replace(/\bapp\.asar\b/, 'app.asar.unpacked')
try {
  module.exports = require(kitpath)
} catch (err) {
  module.exports = require('bindings')('plugkit.node')
}
