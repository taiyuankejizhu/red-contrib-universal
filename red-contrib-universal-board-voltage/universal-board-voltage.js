var bone = require('bonescript');

module.exports = function(RED) {
    function UniversalBoardVoltageNode(config) {
        RED.nodes.createNode(this, config);
		this.onlinepin = config.onlinepin;
		this.topic = config.topic;
		this.voltpin = config.voltpin;
		this.maxvolt = config.maxvolt;
		this.minvolt = config.minvolt;
		this.volt = 0.0;
		
        var node = this;
        
        node.on('input', function(msg) {
            var payload = {
                "progress": 0,
                "value": 0
            };
            
            if (msg.topic != node.topic) return;
            
            if (msg.payload == "begin") {
                node.progress = 0;
                payload.progress = node.progress;
                node.ticker = setInterval(Ticker, 50);
            } else if (msg.payload == "progress") {
                payload.progress = node.progress;
            } else {
                node.progress = 10;
                payload.progress = node.progress;
                if (node.ticker) clearInterval(node.ticker);
            }
            
            payload.value = node.volt;
            
            msg.topic = node.topic;
            msg.payload = payload;
            node.send(msg);
        });
        
        function Ticker() {
            if (node.progress < 10) {
                node.volt = bone.analogRead(node.voltpin) * 1.8;
                node.volt = node.volt.toFixed(2)
                /* node.volt = node.progress; */
                node.progress++;
            } else {
                node.progress = 10;
                clearInterval(node.ticker);
            }
        }
    }
    RED.nodes.registerType("universal-board-voltage",UniversalBoardVoltageNode);
}