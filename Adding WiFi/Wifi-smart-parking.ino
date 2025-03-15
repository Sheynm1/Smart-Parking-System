#include <WiFiS3.h> // Include the WiFiS3 library for Arduino R4
#include <LiquidCrystal.h> //includes liquid crystal library
#define trigPin 10
#define echoPin 13

LiquidCrystal lcd(12,11,5,4,3,2);//creates LCD object.Parameters:(rs, enable, d4,d5,d6,d7)

// Define WiFi credentials
const char* ssid = "YOUR_SSID";      // Replace with your WiFi network name
const char* password = "YOUR_PASSWORD"; // Replace with your WiFi password

int status = WL_IDLE_STATUS;

void setup() {
  // Start serial communication
  pinMode(trigPin, OUTPUT);//Sets the trigPin as an Output
  pinMode(echoPin, INPUT);//Sets the echoPin as an Input
  lcd.begin(16,2);
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect (required for native USB)
  }

  Serial.println("Attempting to connect to WiFi...");

  // Check if the WiFi module is available
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi module not found!");
    while (true); // Stop if no WiFi module is found
  }

  // Check WiFi firmware version
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // Attempt to connect to WiFi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to WiFi...");
    status = WiFi.begin(ssid, password);
    delay(5000); // Wait 5 seconds before retrying
  }

  Serial.println("Connected to WiFi!");
  printWiFiStatus();
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

// Function to print WiFi status
void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}