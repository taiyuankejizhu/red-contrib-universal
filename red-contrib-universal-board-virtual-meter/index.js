var SerialPort = require('serialport');
var buffertools = require('buffertools');
const dlt645 = require('./dlt645/build/Release/dlt645');

var serial = new SerialPort('/dev/ttyS1', {
  baudRate: 9600,
  dataBits: 8,
  parity: 'even',
  stopBits: 1,
  flowControl: false
}, serialDebug);

function serialDebug (err) {
  if (err) {
    return console.log('Error: ', err.message);
  }
};

var read = '';
var write = '';

serial.on('data', function (data) {
  setTimeout(Timeout, 100);
  read += buffertools.toHex(data);
});

function Timeout() {
  try {
    if (read.length > 10) {
      console.log("Read: " + read);
      write = dlt645.unpacket07(read);
      console.log("Write: " + write);
      serial.write(Buffer.from(write, 'hex'), serialDebug);
    }
  } catch (e) {
    console.log(e);
  }
  write = '';
  read = '';
}