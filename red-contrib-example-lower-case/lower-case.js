const addon = require('./addon/build/Release/addon');
var bone = require('bonescript');

module.exports = function(RED) {
    function LowerCaseNode(config) {
        RED.nodes.createNode(this,config);
		this.logfile = config.logfile;
        var node = this;
        node.on('input', function(msg) {
            msg.payload = bone.analogRead(node.logfile) * 1.8;
            node.send(msg);
        });
    }
    RED.nodes.registerType("lower-case",LowerCaseNode);
}