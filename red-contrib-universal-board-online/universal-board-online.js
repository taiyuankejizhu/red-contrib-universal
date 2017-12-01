var bone = require('bonescript');

var inputPin = "P8_11";
var lastState = bone.LOW;

module.exports = function(RED) {
    function UniversalBoardOnlineNode(config) {
        RED.nodes.createNode(this, config);
		this.onlinepin = config.onlinepin;
		this.topic = config.topic;
        var node = this;
        
        bone.pinMode(inputPin, bone.INPUT);
        lastState = bone.digitalRead(inputPin);
        
        node.on('input', function(msg) {
            inputPin = node.onlinepin;
            var state = bone.digitalRead(inputPin);
            if (state != lastState && state == bone.HIGH)
                msg.payload = "OnlinePluse";
            if (state != lastState && state == bone.LOW)
                msg.payload = "OfflinePluse";
            if (state == lastState && state == bone.HIGH)
                msg.payload = "Online";
            if (state == lastState && state == bone.LOW)
                msg.payload = "Offline";
            lastState = state;
            msg.topic = node.topic;
            node.send(msg);
        });
    }
    RED.nodes.registerType("universal-board-online",UniversalBoardOnlineNode);
}