#include <LiquidCrystal.h> //includes liquid crystal library
#define trigPin 10
#define echoPin 13
 
 
LiquidCrystal lcd(12,11,5,4,3,2);//creates LCD object.Parameters:(rs, enable, d4,d5,d6,d7)

void setup() {
  pinMode(trigPin, OUTPUT);//Sets the trigPin as an Output
  pinMode(echoPin, INPUT);//Sets the echoPin as an Input
  lcd.begin(16,2);
  Serial.begin(9600);
}
 
void loop() {
   delay(10000);
   float Duration, Distance, CarParked, AvailableSpaces, CurrentDistance, PreviousDistance, Threshold = 50, maxValue = 800;
  //clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  //Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  //Reads the echoPin, returns the sound wave travel time in miroseconds
  Duration = pulseIn(echoPin, HIGH);
  CurrentDistance = (Duration / 2) * 0.0344;
  lcd.setCursor(0,0);
 
  if (abs(CurrentDistance - PreviousDistance) > Threshold) {
    Serial.println("DistanceChanged");
    
    PreviousDistance = CurrentDistance;
  }
  delay(100);
 
  if (CurrentDistance < 10) {
    CarParked = 1;
  }
  if (CurrentDistance > 10) {
    CarParked = 0;
  }
  AvailableSpaces = 1;
 
  if (CarParked) {
    AvailableSpaces = AvailableSpaces - 1;
    }
    else if (CarParked = 0) {
      AvailableSpaces = AvailableSpaces + 1;
      Serial.println(AvailableSpaces);
    }
 
  if (AvailableSpaces = 0) {
    Serial.println("No Spaces");
    }
    else if (AvailableSpaces > 0) {
      Serial.print("Spaces Available");
    lcd.print("No more spaces");
  }
    else if (Distance <= 2) {
      lcd.print(Distance);
      delay(10);
    }
  else {
    String Duration = "Space Taken";
    String Distance = "Check spaces";
    lcd.print(CarParked);
    Serial.println(Distance); 
    Serial.println(Duration);
    
    lcd.print(" Available Spaces");
    delay(10);
  }
  delay(10);
  lcd.clear();
 
  
  // Read the new value (e.g., from a sensor or input pin)
  CurrentDistance = analogRead(A0); // Example: reading from analog pin A0
  // Check if the current value exceeds the maximum allowed value
  if (CurrentDistance > maxValue) {
    Serial.println("Value exceeds maximum limit. Stopping execution.");
    return; // Stop running further code in this loop iteration
  }
  // Check if the difference exceeds the threshold
  if (abs(CurrentDistance - PreviousDistance) > Threshold) {
    // Significant change detected, run the desired code
    Serial.print("Significant change detected. New value: ");
    Serial.println(CurrentDistance);
    
    // Update the previous value
    PreviousDistance = CurrentDistance;
  }
  // Small delay to prevent excessive polling (adjust as needed)
  delay(100);
}
