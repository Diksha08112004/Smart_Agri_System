#define BLYNK_TEMPLATE_ID "TMPL3jxp05Y-n"
#define BLYNK_TEMPLATE_NAME "smartsoil"
#define BLYNK_AUTH_TOKEN "l-oG7kP3x8WMEjgLSTsIju43R29QhMob"
#include <DHT.h>
#include <BlynkSimpleEsp32.h>

// Blynk Auth Token
char auth[] = "l-oG7kP3x8WMEjgLSTsIju43R29QhMob";  // Replace with your Blynk Auth Token

// Pin Definitions
#define DHT_PIN 4              // Pin for DHT sensor (if used)
#define DHT_TYPE DHT11         // DHT11 or DHT22 sensor

#define SOIL_MOISTURE_PIN1 34  // Soil Moisture Sensor 1 (Analog input)
#define SOIL_MOISTURE_PIN2 35  // Soil Moisture Sensor 2 (Analog input)

#define RELAY_PIN1 16          // Relay control pin for Pump 1
#define RELAY_PIN2 17          // Relay control pin for Pump 2

// Blynk Virtual Pins for Soil Moisture and Pump Control
#define VPIN_SOIL_MOISTURE1 V1
#define VPIN_SOIL_MOISTURE2 V2
#define VPIN_PUMP1 V3
#define VPIN_PUMP2 V4

DHT dht(DHT_PIN, DHT_TYPE);  // Initialize DHT sensor

void setup() {
  // Start Serial Monitor for debugging
  Serial.begin(115200);

  // Initialize DHT sensor
  dht.begin();

  // Set Relay pins as OUTPUT
  pinMode(RELAY_PIN1, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);

  // Set soil moisture sensor pins as INPUT
  pinMode(SOIL_MOISTURE_PIN1, INPUT);
  pinMode(SOIL_MOISTURE_PIN2, INPUT);

  // Connect to Blynk
  Blynk.begin(auth, "network", "1122334455");  // Replace with your WiFi credentials
}

void loop() {
  // Read Soil Moisture levels from both sensors (Analog readings)
  int soilMoisture1 = analogRead(SOIL_MOISTURE_PIN1);
  int soilMoisture2 = analogRead(SOIL_MOISTURE_PIN2);

  // Read temperature and humidity (if needed)
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if DHT readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print temperature, humidity, and soil moisture levels to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\n");

  Serial.print("Soil Moisture 1: ");
  Serial.println(soilMoisture1);
  Serial.print("Soil Moisture 2: ");
  Serial.println(soilMoisture2);

  // Define a threshold value for soil moisture (indicating dry soil)
  int moistureThreshold = 3000;  // Moisture value below 400 indicates dry soil (calibrate as needed)

  // Check if soil moisture is below threshold and start the pump if dry
  if (soilMoisture1 < moistureThreshold) {
    Serial.println("Soil 1 is dry! Activating Pump 1.");
    digitalWrite(RELAY_PIN1, HIGH);  // Turn on Pump 1
    Blynk.virtualWrite(VPIN_PUMP1, HIGH); // Update Blynk Button to ON
  } else {
    Serial.println("Soil 1 is wet! Deactivating Pump 1.");
    digitalWrite(RELAY_PIN1, LOW);   // Turn off Pump 1
    Blynk.virtualWrite(VPIN_PUMP1, LOW); // Update Blynk Button to OFF
  }

  if (soilMoisture2 < moistureThreshold) {
    Serial.println("Soil 2 is dry! Activating Pump 2.");
    digitalWrite(RELAY_PIN2, HIGH);  // Turn on Pump 2
    Blynk.virtualWrite(VPIN_PUMP2, HIGH); // Update Blynk Button to ON
  } else {
    Serial.println("Soil 2 is wet! Deactivating Pump 2.");
    digitalWrite(RELAY_PIN2, LOW);   // Turn off Pump 2
    Blynk.virtualWrite(VPIN_PUMP2, LOW); // Update Blynk Button to OFF
  }

  // Send soil moisture levels to Blynk app
  Blynk.virtualWrite(VPIN_SOIL_MOISTURE1, soilMoisture1);
  Blynk.virtualWrite(VPIN_SOIL_MOISTURE2, soilMoisture2);

  // Update DHT data (temperature and humidity) to Blynk (Optional)
  Blynk.virtualWrite(V5, temperature);  // Virtual Pin 5 for temperature
  Blynk.virtualWrite(V6, humidity);     // Virtual Pin 6 for humidity

  // Run Blynk in the background
  Blynk.run();

  // Delay before checking again
  delay(2000);  // Delay in milliseconds (e.g., 2 seconds)
}