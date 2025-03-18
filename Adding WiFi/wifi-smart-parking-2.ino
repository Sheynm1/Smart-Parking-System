#include <WiFiS3.h> // Include the WiFiS3 library for Arduino R4
#include <LiquidCrystal.h> // Include Liquid Crystal library

// Define ultrasonic sensor pins
#define trigPin 10
#define echoPin 13

// Create LCD object (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// WiFi credentials
const char* ssid = "toob-295415";       // Your WiFi network name
const char* password = "4Jd2Ferf58GE";  // Your WiFi password

int status = WL_IDLE_STATUS;
float previousDistance = 0;
float threshold = 5;  // Threshold for distance change in cm
int totalSpaces = 1; // Total number of parking spaces
int availableSpaces = 1;

void setup() {
  // Start serial communication
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }

  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize LCD (16 columns, 2 rows)
  lcd.begin(16, 2);

  // Attempt to connect to WiFi
  connectToWiFi();
}

void loop() {
  float duration, currentDistance;
  bool carParked = false;

  // Clear trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10-microsecond pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the pulse width to determine distance
  duration = pulseIn(echoPin, HIGH);
  currentDistance = (duration * 0.0343) / 2;

  // Print to Serial Monitor
  Serial.print("Current Distance: ");
  Serial.print(currentDistance);
  Serial.println(" cm");

  // Check if there's a significant distance change
  if (abs(currentDistance - previousDistance) > threshold) {
    Serial.println("Distance Changed");
    previousDistance = currentDistance;
  }

  // Parking logic
  if (currentDistance < 10) {
    carParked = true;
  } else {
    carParked = false;
  }

  // Update available spaces
  if (carParked) {
    availableSpaces = totalSpaces - 1;
  } else {
    availableSpaces = totalSpaces;
  }

  // Display parking info on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  
  if (availableSpaces == 0) {
    lcd.print("No Spaces Left");
    Serial.println("No Spaces Left");
  } else {
    lcd.print("Spaces Available: ");
    lcd.setCursor(0, 1);
    lcd.print(availableSpaces);
    Serial.print("Available Spaces: ");
    Serial.println(availableSpaces);
  }

  delay(1000); // Refresh every second
}

// Function to connect to WiFi
void connectToWiFi() {
  Serial.println("Attempting to connect to WiFi...");

  // Check if WiFi module is available
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi module not found!");
    while (true);
  }

  // Check WiFi firmware version
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // Attempt to connect to WiFi network
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to WiFi...");
    status = WiFi.begin(ssid, password);
    delay(5000);
  }

  Serial.println("Connected to WiFi!");
  printWiFiStatus();
}

// Function to print WiFi status
void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("Signal Strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}
