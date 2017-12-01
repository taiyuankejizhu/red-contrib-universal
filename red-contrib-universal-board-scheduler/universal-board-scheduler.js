var SchedulerRunTime = {
    "running": false,
    "items": [
        {
            "running": false,
            "name": "online",
            "max_time": 1000,
            "used_time": 0,
            "complete": false,
            "timestamp": {
                "begin_timestamp": -1,
                "current_timestamp": -1,
                "end_timestamp": -1
            },
            "type": 0
        },
        {
            "running": false,
            "name": "volt_3.3",
            "max_time": 1000,
            "used_time": 0,
            "complete": false,
            "timestamp": {
                "begin_timestamp": -1,
                "current_timestamp": -1,
                "end_timestamp": -1
            },
            "type": 1
        },
        {
            "running": false,
            "name": "volt_12.0",
            "max_time": 1000,
            "used_time": 0,
            "complete": false,
            "timestamp": {
                "begin_timestamp": -1,
                "current_timestamp": -1,
                "end_timestamp": -1
            },
            "type": 1
        },
        {
            "running": false,
            "name": "volt_1.15",
            "max_time": 1000,
            "used_time": 0,
            "complete": false,
            "timestamp": {
                "begin_timestamp": -1,
                "current_timestamp": -1,
                "end_timestamp": -1
            },
            "type": 1
        }
    ]
};

var innerMessage = {
    "topic": "",
    "payload": "",
    "_msgid": ""
};

module.exports = function(RED) {
    function UniversalBoardScheduleNode(config) {
        RED.nodes.createNode(this, config);
		this.onlinepin = config.onlinepin;
        var node = this;
        
        setInterval(allInnerTicker ,50);
        setInterval(oneInnerTicker ,100);
        
        node.on('input', function(msg) {
            var i = 0;
            
            if (msg.topic == "online" && msg.payload == "OfflinePluse") {
                SchedulerRunTime.running = false;
            }
            if (msg.topic == "online" && msg.payload == "OnlinePluse") {
                SchedulerRunTime.running = true;
                for (i = 0; i < SchedulerRunTime.items.length; i++) {
                    if (SchedulerRunTime.items[i].type == 1) {
                        SchedulerRunTime.items[i].used_time = 0;
                        SchedulerRunTime.items[i].complete = false;
                        SchedulerRunTime.items[i].running = false;
                        SchedulerRunTime.items[i].timestamp.begin_timestamp = -1;
                        SchedulerRunTime.items[i].timestamp.current_timestamp = -1;
                        SchedulerRunTime.items[i].timestamp.end_timestamp = -1;
                    }
                }
            }
        });
        
        function allInnerTicker() {
            var i = 0;
            
            /* Update the alltime item */
            for (i = 0; i < SchedulerRunTime.items.length; i++) {
                if (SchedulerRunTime.items[i].type == 0
                    && SchedulerRunTime.items[i].running == false)
                {
                    SchedulerRunTime.items[i].running = true;
                    SchedulerRunTime.items[i].timestamp.begin_timestamp = Date.now();
                    
                    innerMessage.topic = SchedulerRunTime.items[i].name;
                    innerMessage.payload = "begin";
                    innerMessage._msgid = RED.util.generateId();
                    node.send(innerMessage);
                } else if (SchedulerRunTime.items[i].type == 0
                    && SchedulerRunTime.items[i].running == true)
                {
                    SchedulerRunTime.items[i].timestamp.current_timestamp = Date.now();
                    SchedulerRunTime.items[i].used_time = 
                        SchedulerRunTime.items[i].timestamp.current_timestamp - 
                        SchedulerRunTime.items[i].timestamp.begin_timestamp;
                    
                    innerMessage.topic = SchedulerRunTime.items[i].name;
                    innerMessage.payload = "progress";
                    innerMessage._msgid = RED.util.generateId();
                    node.send(innerMessage);
                } else continue;
            }
        }
        
        function oneInnerTicker() {
            var i = 0;
            
            /* Update the onetime item */
            for (i = 0; i < SchedulerRunTime.items.length; i++) {
                if (SchedulerRunTime.items[i].type == 1 
                    && SchedulerRunTime.items[i].complete == false)
                {
                    if (SchedulerRunTime.items[i].running == false) {
                        SchedulerRunTime.items[i].running = true;
                        SchedulerRunTime.items[i].timestamp.begin_timestamp = Date.now();
                        
                        innerMessage.topic = SchedulerRunTime.items[i].name;
                        innerMessage.payload = "begin";
                        innerMessage._msgid = RED.util.generateId();
                        node.send(innerMessage);  
                    } else {
                        SchedulerRunTime.items[i].timestamp.current_timestamp = Date.now();
                        SchedulerRunTime.items[i].used_time =
                            SchedulerRunTime.items[i].timestamp.current_timestamp -
                            SchedulerRunTime.items[i].timestamp.begin_timestamp;
                        
                        if (SchedulerRunTime.items[i].used_time < 
                            SchedulerRunTime.items[i].max_time) {
                            innerMessage.topic = SchedulerRunTime.items[i].name;
                            innerMessage.payload = "progress";
                            innerMessage._msgid = RED.util.generateId();
                            node.send(innerMessage); 
                        } else {
                            SchedulerRunTime.items[i].timestamp.end_timestamp = Date.now();
                            SchedulerRunTime.items[i].running = false;
                            SchedulerRunTime.items[i].complete = true;
                            
                            innerMessage.topic = SchedulerRunTime.items[i].name;
                            innerMessage.payload = "end";
                            innerMessage._msgid = RED.util.generateId();
                            node.send(innerMessage);
                        }
                    }
                    
                    break;
                }
            }
        }
    }
    RED.nodes.registerType("universal-board-scheduler", UniversalBoardScheduleNode);
}