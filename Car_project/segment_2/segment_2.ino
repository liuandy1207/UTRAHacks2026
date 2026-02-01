// paste the base.ino here

// Run path finding function (red line detection)
    // should reach obstacle avoidance sequence
    // return to red line 
    // should reach obstacle avoidance sequence again
    // return to red line

// should stop at blue line 

// turn 90 deg left 

// drop cube

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

void loop{
    //const
    int red = 1;
    int green = 2;
    int blue = 3;
    int black = 4;
    int white = 0;
    int unc = 0;

    //
    //trace red (left)
    //trace red (left)
    moveAndCheckColor(red, 'l', white);
    //returns when hit object

    //object deterance
    obstacle_avoidance_sequence();

    //trace red (right)
    moveAndCheckColor(red, 'r', white);
    //returns when hit object
    obstacle_avoidance_sequence();
    //trace red (left)
    moveAndCheckColor(red, 'l', white);
    //returns when blue


    //putdown!!
    
    //left 90
    turnLeft();
    delay(1250);
    //omething bout butt
    //rotte(0)
    rotate(0);
    delay(50);
    //bckwrd()
    backward();
    delay(1500);
    turnRight();
    delay(1250);

    //trace red (left)
    moveAndCheckColor(red, 'l', white);
    //turn
    moveAndCheckColor(green, 'l', white);
    //top bc pick up put down
    //
        //call pick up (check what pick up returns check finl tte)
    backward();
    delay(1500);
    turnRight();
    delay(1250);
    forward();
    delay(1000);
    rotate(90);
    delay(50);
    forward();
    delay(2000);
    rotate(0);
    delay(50);

    turnLeft();
    delay(2500);
    forward();
    delay(1000);
    rotate(0);
    delay(50);
    backward();
    delay(1000);
    turnRight();
    delay(1250);
    //
    //
    moveAndCheckColor(green, 'l', white);
    moveAndCheckColor(black, 'l', brown);

}