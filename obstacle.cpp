// ================= MOTOR DRIVER PINS =================
// Left Motor
int ENA = 5;   // Speed control (PWM)
int IN1 = 6;   // Direction control
int IN2 = 7;

// Right Motor
int ENB = 9;   // Speed control (PWM)
int IN3 = 10;  // Direction control
int IN4 = 11;


// ================= ULTRASONIC SENSOR PINS =================
int trigPin = 2;   // Trigger pin (sends signal)
int echoPin = 3;   // Echo pin (receives signal)

long duration;     // Time taken for echo to return
int distance;      // Calculated distance in cm


// ================= SETUP FUNCTION =================
void setup() {

  // Set motor pins as OUTPUT
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Set ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Start serial monitor (for debugging)
  Serial.begin(9600);
}


// ================= MAIN LOOP =================
void loop() {

  // Get distance from ultrasonic sensor
  distance = getDistance();

  // Print distance in Serial Monitor
  Serial.println(distance);

  // ===== DECISION MAKING =====
  if (distance > 20) {
    // If no obstacle nearby → move forward
    moveForward();
  } 
  else {
    // If obstacle detected → avoid it
    stopMotors();     // Stop first
    delay(300);

    moveBackward();   // Move back a little
    delay(500);

    turnRight();      // Turn to avoid obstacle
    delay(500);
  }
}


// ================= DISTANCE MEASUREMENT FUNCTION =================
int getDistance() {

  // Ensure trigger is LOW initially
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send HIGH pulse for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time (time taken for sound wave to return)
  duration = pulseIn(echoPin, HIGH);

  // Convert time into distance (cm)
  distance = duration * 0.034 / 2;

  return distance;
}


// ================= MOVEMENT FUNCTIONS =================

// Move robot forward
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Move robot backward
void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Turn robot right
void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Stop all motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}