#include "movement.h"

// Move forward: all wheels move forward
void moveForward(float distance_m)
{
    // Disable rotation motors
    digitalWrite(WHEEL_LEFT_ROTATION_PIN, LOW);
    digitalWrite(WHEEL_RIGHT_ROTATION_PIN, LOW);

    // Pure movement: both wheels move forward
    digitalWrite(WHEEL_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(WHEEL_RIGHT_BACKWARD_PIN, LOW);

    digitalWrite(WHEEL_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(WHEEL_LEFT_BACKWARD_PIN, LOW);

    delay(distance_m * 2000);

    moveStop();
};

// Move backward: all wheels move backward
void moveBackward(float distance_m) 
{
    // Disable rotation motors
    digitalWrite(WHEEL_LEFT_ROTATION_PIN, LOW);
    digitalWrite(WHEEL_RIGHT_ROTATION_PIN, LOW);

    // Pure movement: both wheels move backward
    digitalWrite(WHEEL_RIGHT_FORWARD_PIN, LOW);
    digitalWrite(WHEEL_RIGHT_BACKWARD_PIN, HIGH);

    digitalWrite(WHEEL_LEFT_FORWARD_PIN, LOW);
    digitalWrite(WHEEL_LEFT_BACKWARD_PIN, HIGH);

    delay(distance_m * 2000);

    moveStop();
};

// Move forward while turning right
void moveRight() 
{
    // Turn wheels to the right
    digitalWrite(WHEEL_LEFT_ROTATION_PIN, HIGH);
    digitalWrite(WHEEL_RIGHT_ROTATION_PIN, LOW);

    // All wheels move forward
    digitalWrite(WHEEL_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(WHEEL_RIGHT_BACKWARD_PIN, LOW);

    digitalWrite(WHEEL_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(WHEEL_LEFT_BACKWARD_PIN, LOW);

    moveStop();
};

// Move forward while turning left
void moveLeft() 
{
    // Turn wheels to the left
    digitalWrite(WHEEL_LEFT_ROTATION_PIN, LOW);
    digitalWrite(WHEEL_RIGHT_ROTATION_PIN, HIGH);
    
    // All wheel move forward
    digitalWrite(WHEEL_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(WHEEL_RIGHT_BACKWARD_PIN, LOW);

    digitalWrite(WHEEL_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(WHEEL_LEFT_BACKWARD_PIN, LOW);
  
    moveStop();
};

// Rotate 90º to the left
void rotateLeft90()
{
  digitalWrite(WHEEL_LEFT_ROTATION_PIN, LOW);
  digitalWrite(WHEEL_RIGHT_ROTATION_PIN, LOW);

  digitalWrite(WHEEL_RIGHT_FORWARD_PIN, HIGH);
  digitalWrite(WHEEL_RIGHT_BACKWARD_PIN, LOW);
  digitalWrite(WHEEL_LEFT_FORWARD_PIN, LOW);
  digitalWrite(WHEEL_LEFT_BACKWARD_PIN, HIGH);

  delay(900); // adjust timing for 90°
  moveStop();
}

// Rotate 90° to the right (in place)
void rotateRight90()
{
  digitalWrite(WHEEL_LEFT_ROTATION_PIN, LOW);
  digitalWrite(WHEEL_RIGHT_ROTATION_PIN, LOW);

  digitalWrite(WHEEL_RIGHT_FORWARD_PIN, LOW);
  digitalWrite(WHEEL_RIGHT_BACKWARD_PIN, HIGH);
  digitalWrite(WHEEL_LEFT_FORWARD_PIN, HIGH);
  digitalWrite(WHEEL_LEFT_BACKWARD_PIN, LOW);

  delay(900);
  moveStop();
}

// Rotate 180° in place
void rotate180()
{
  digitalWrite(WHEEL_LEFT_ROTATION_PIN, LOW);
  digitalWrite(WHEEL_RIGHT_ROTATION_PIN, LOW);

  digitalWrite(WHEEL_RIGHT_FORWARD_PIN, LOW);
  digitalWrite(WHEEL_RIGHT_BACKWARD_PIN, HIGH);
  digitalWrite(WHEEL_LEFT_FORWARD_PIN, HIGH);
  digitalWrite(WHEEL_LEFT_BACKWARD_PIN, LOW);

  delay(1800);
  moveStop();
}

// Stop moving
void moveStop() 
{
  // Disable all movement and rotation pins
  digitalWrite(WHEEL_RIGHT_FORWARD_PIN, LOW);
  digitalWrite(WHEEL_RIGHT_BACKWARD_PIN, LOW);
  digitalWrite(WHEEL_LEFT_FORWARD_PIN, LOW);
  digitalWrite(WHEEL_LEFT_BACKWARD_PIN, LOW);
  digitalWrite(WHEEL_LEFT_ROTATION_PIN, LOW);
  digitalWrite(WHEEL_RIGHT_ROTATION_PIN, LOW);
};

// Move forward until obstacle at given distance
void moveUntilObstacle(int stopDistance_cm)
{
  unsigned long duration;            // Store the time taken for the ultrasonic pulse to return
  int distance;                      // Store the calculated distance in cm
  
  // Ultrasonic pins
  const int TRIG_PIN = A0; 
  const int ECHO_PIN = A1;

  pinMode(TRIG_PIN, OUTPUT); // Send the pulse   
  pinMode(ECHO_PIN, INPUT);  // Receive the pulse

  // Keep moving forward until we detect an obstacle
  while (true)
  {
    // Send ultrasonic pulse
    digitalWrite(TRIG_PIN, LOW);            // Ensure trigger is LOW
    delayMicroseconds(2);                   // Short pause to stabilize the signal
    digitalWrite(TRIG_PIN, HIGH);           // Send a 10 µs pulse to start measurement
    delayMicroseconds(10);                  // Keep the trigger HIGH for 10 µs
    digitalWrite(TRIG_PIN, LOW);            // Pull it LOW again to finish the pulse

    duration = pulseIn(ECHO_PIN, HIGH);     // Measure the time the echo pin stays HIGH
    
    // Convert time (µs) to distance (cm): sound speed ~ 0.034 cm/µs, divide by 2 (go and return)
    distance = duration * 0.034 / 2;

    // If the measured distance is less or equal to the limit
    if (distance <= stopDistance_cm)
    {
      moveStop();                     // stop the robot immediately
      break;
    }

    // Keep moving forward
    digitalWrite(WHEEL_RIGHT_FORWARD_PIN, HIGH);  // right wheel forward
    digitalWrite(WHEEL_RIGHT_BACKWARD_PIN, LOW);  // make sure backward is off
    digitalWrite(WHEEL_LEFT_FORWARD_PIN, HIGH);   // left wheel forward
    digitalWrite(WHEEL_LEFT_BACKWARD_PIN, LOW);   // make sure backward is off
  }
}