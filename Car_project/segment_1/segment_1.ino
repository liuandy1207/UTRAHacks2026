// =================================

// =================================

// Segment 1
void loop {

// Follow Black Line
   moveAndCheckColor(4, 'l', 0);

// follow red line 
   moveAndCheckColor(1, 'l', 0);

// pick up cube
   backward();
   delay(1500);
   turnRight();
   delay(1000);

   rotate(90);
   delay(50);
   forward();
   delay(2000);
   rotate(0);
   delay(50);

   turnLeft();
   delay(1000);

   while (1 != identifyColor()) {
      forward();
      delay(200);
   }
   // reup here

}

