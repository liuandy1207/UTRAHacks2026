// Base


void loop() {
    findBall();
    while (identifyColor() != 1) {
        forward();
        delay(250);
    }
    brake();
}


