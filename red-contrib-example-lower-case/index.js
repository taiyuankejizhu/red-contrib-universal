var addon = require('./addon/build/Release/addon.node');
var bone = require('bonescript');

var state = bone.LOW;

var SchedulerRunTime = {
    "timestamp": {
        "begin_timestamp": -1,
        "current_timestamp": -1,
        "end_timestamp": -1
    },
    "items": [ 
        {
            "running": false,
            "name": "volt_3.3"
        },
        {
            "running": false,
            "name": "volt_12.0"
        },
        {
            "running": false,
            "name": "volt_1.15"
        }
    ]
}

bone.pinMode("USR0", bone.OUTPUT);

setInterval(toggle, 1000);

function toggle() {
    for (var i = 0; i < SchedulerRunTime.items.length; i++) {
        console.log(SchedulerRunTime.items[i].name)
    }
    
    if(state == bone.LOW) state = bone.HIGH;
    else state = bone.LOW;
    bone.digitalWrite("USR0", state);
    console.log(Date.now());
}