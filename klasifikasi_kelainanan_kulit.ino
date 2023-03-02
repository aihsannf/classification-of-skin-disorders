//IR
int IRSensor1 = A0;
int IRSensor2 = A1;
int IRSensor3 = A2;
float Teg1;
float Teg2;
float Teg3;

//Ultrasonic
int trigPin = 6;
int echoPin = 7;
long duration;
float distance;

void setup() {
  Serial.begin(9600);

  //IR
  pinMode (IRSensor1, INPUT);
  pinMode (IRSensor2, INPUT);
  pinMode (IRSensor3, INPUT);

  //Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  //Ultrasonic
  /// Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  /// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  /// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  /// Calculating the distance
  distance = duration * 0.034 / 2;

  //IR
  int statusSensor1 = analogRead(IRSensor1);
  int statusSensor2 = analogRead(IRSensor2);
  int statusSensor3 = analogRead(IRSensor3);
  float Teg1 = statusSensor1*0.00488;
  float Teg2 = statusSensor2*0.00488;
  float Teg3 = statusSensor3*0.00488;
  float average = (Teg1 + Teg2 + Teg3)/3;

  // Prints to the HC05
  if (distance > 0) {
    Serial.print(distance);
    Serial.print("-");
  } else {
    Serial.print("Loading...");
    Serial.print("-");
  }

  if (Teg1 > 0 && Teg2 > 0 && Teg3 > 0) {
    Serial.print(Teg1,3);
    Serial.print(" ");
    Serial.print(Teg2,3);
    Serial.print(" ");
    Serial.print(Teg3,3);
    Serial.print("-");
  } else {
    Serial.print("Loading...");
    Serial.print("-");
  }
  
  if (average >= 0.142 && average <= 0.158) {
    Serial.print("Keloid");
    Serial.print("-");
  } else if (average >= 0.189 && average <= 0.245) {
    Serial.print("Jerawat");
    Serial.print("-");
  } else {
    Serial.print("Bukan Jerawat/Keloid");
    Serial.print("-");
  }
  
  delay(1000);
}