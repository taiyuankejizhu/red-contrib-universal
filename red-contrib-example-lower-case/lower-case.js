const addon = require('./addon/build/Release/addon');

module.exports = function(RED) {
    function LowerCaseNode(config) {
        RED.nodes.createNode(this,config);
		this.logfile = config.logfile;
        var node = this;
        node.on('input', function(msg) {
			var get_tst_log = 
			{
    			"method": "get_tst_log",
    			"params": {
        			"index": 0
    			},
    			"version": "1.0"
			};
			get_tst_log.params.index = msg.payload;
			get_tst_log.crc = addon.crc32(JSON.stringify(get_tst_log));
			msg.payload = JSON.stringify(get_tst_log);
            node.send(msg);
        });
    }
    RED.nodes.registerType("lower-case",LowerCaseNode);
}