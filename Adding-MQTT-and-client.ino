#include <WiFiS3.h> // Include the WiFiS3 library for Arduino R4
#include <LiquidCrystal.h> // Include Liquid Crystal library
#include <PubSubClient.h>  // MQTT library
#include <WiFiSSLClient.h> // SSL support, encrypted communication when connecting to servers

// Define ultrasonic sensor pins
#define trigPin 10
#define echoPin 13

// Create LCD object (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// WiFi credentials
const char* ssid = "toob-AE62D3";       // Your WiFi network name
const char* password = "dibayujnqx";  // Your WiFi password

// MQTT Broker 
const char* mqtt_server = "0f994b563d484ad08066fb1db2fc482e.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "Shey-Mathurin";
const char* mqtt_pass = "Demorified1#";
const char* mqtt_topic = "parking/status";

WiFiSSLClient wifiClient;
PubSubClient client(wifiClient);

int status = WL_IDLE_STATUS;
float previousDistance = 0;
float threshold = 5;  // Threshold for distance change in cm
int totalSpaces = 1; // Total number of parking spaces
int availableSpaces = 1;

// Message timing
unsigned long lastMsg = 0;
unsigned long interval = 3000;

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

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  // keep mqtt running
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop(); // keeps connection going
  
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

   // MQTT publish every few seconds
  if (millis() - lastMsg > interval) {
    lastMsg = millis();
    String msg = carParked ? "occupied" : "available";
    client.publish(mqtt_topic, msg.c_str());
    Serial.print("Published MQTT: ");
    Serial.println(msg);
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
    Serial.print("Trying to Connect to WiFi... Check Password Or SSID!");
    status = WiFi.begin(ssid, password);
    delay(10000);
  }

  
  Serial.println("Connected to Wi-Fi");
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

// reconnect when disconnected
void reconnectMQTT() {
  while (!client.connected()) {
    String clientId = "arduinoClient_" + String(random(1000, 9999));
    Serial.print("Connecting to MQTT as: "); 
    Serial.println(clientId); 
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      Serial.println("connected to MQTT Broker!");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}
