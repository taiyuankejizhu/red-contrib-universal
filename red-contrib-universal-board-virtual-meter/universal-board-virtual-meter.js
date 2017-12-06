const dlt645 = require('./dlt645/build/Release/dlt645');
var SerialPort = require('serialport');
var buffertools = require('buffertools');

module.exports = function(RED) {
    function UniversalBoardVirtualMeterNode(config) {
        RED.nodes.createNode(this,config);
		this.meter = config.meter;
		this.serial = config.serial;
        var node = this;
        
        var read = '';
        var write = '';
        var serial = new SerialPort(node.serial, {
            baudRate: 9600,
            dataBits: 8,
            parity: 'even',
            stopBits: 1,
            flowControl: false
        }, serialDebug);
            
        serial.on('data', function (data) {
            setTimeout(serialTimeout, 100);
            read += buffertools.toHex(data);
        });
        
        node.on('input', function(msg) {
            node.send(msg);
        });
        
        function serialTimeout() {
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
        
        function serialDebug (err) {
            if (err) {
                return console.log('Error: ', err.message);
            }
        };
    }
    RED.nodes.registerType("universal-board-virtual-meter",UniversalBoardVirtualMeterNode);
}