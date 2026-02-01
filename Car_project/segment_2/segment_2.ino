// paste the base.ino here

// Run path finding function (red line detection)
    // should reach obstacle avoidance sequence
    // return to red line 
    // should reach obstacle avoidance sequence again
    // return to red line

moveAndCheckColor(1,'l',0)

// should stop at blue line 

// drop cube, copioed from pick up not sure if itll work
backward();
delay(1500);
turnLeft();
delay(1000);

rotate(0);
delay(50);
forward();
delay(2000);
rotate(0);
delay(50);

turnRight();
delay(1000);

// run path finding red again (turn right first priority)
    // terminate on green / black  

// turn left 315 deg

// run path finding green 
    // terminate on blue 

// turn right 90 deg

// pick up cube

// turn 180 degrees left

// drop cube 

// turn 90 deg 90

// re-up
