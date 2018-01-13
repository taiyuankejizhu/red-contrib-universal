const opencv_featrue = require('./opencv_featrue/build/Release/opencv_featrue');

module.exports = function(RED) {
    function UniversalBoardOpencvFeatrueNode(config) {
        RED.nodes.createNode(this, config);
		this.topic = config.topic;
        var node = this;
        
        node.on('input', function(msg) {
            var ret = opencv_featrue.captrue(800, 600);
            msg.topic = node.topic;
            if (ret > 0) {
                msg.payload = {
                    file : ret + '.png',
                    timestamp : ret
                }
            } else {
                msg.payload = {
                    file : 'test.jpeg',
                    timestamp : ret
                }
            }
            node.send(msg);
        });
    }
    RED.nodes.registerType("universal-board-opencv-featrue", UniversalBoardOpencvFeatrueNode);
}