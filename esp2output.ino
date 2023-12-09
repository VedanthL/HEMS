#include <WiFi.h>
#include <ThingSpeak.h>
#define RXp0 16
#define TXp0 17
#define CURRENT_SENSOR_PIN A0
#define VOLTAGE_SENSOR_PIN 34
#define CURRENT_SENSOR_SENSITIVITY 0.185
#define VOLTAGE_SENSOR_VREF 5.0
#define VOLTAGE_SENSOR_DIVIDER_RATIO 11.0
const char *ssid = "Ved +Nord";
const char *password = "lifesucks";
const char *thingSpeakApiKey = "WWDVT1MNBBZ7AAQP";
const float costPerUnit = 7.0;
WiFiClient client;
void setup(){
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp0, TXp0);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  ThingSpeak.begin(client);
}
void loop(){
  if (WiFi.status() == WL_CONNECTED){
    float current;
    float voltage;
    int rawCurrent = analogRead(CURRENT_SENSOR_PIN);
    current = (rawCurrent - 512) * CURRENT_SENSOR_SENSITIVITY;
    int rawVoltage = analogRead(VOLTAGE_SENSOR_PIN);
    voltage = (rawVoltage / 4095.0) * VOLTAGE_SENSOR_VREF * VOLTAGE_SENSOR_DIVIDER_RATIO;
    float power = current * voltage;
    ThingSpeak.setField(1, current);
    ThingSpeak.setField(2, voltage);
    ThingSpeak.setField(3, power);
    float energyConsumed = (power / 1000.0);
    float cost = energyConsumed * costPerUnit;
    ThingSpeak.setField(4, cost);
    Serial.println("CONVERSION: ");
    if (Serial2.available()) {
      String receivedData = Serial2.readString();
      Serial.println(receivedData);
    } else {
      Serial.println("No data received from Serial2.");
    }
    int httpCode = ThingSpeak.writeFields(2373416, thingSpeakApiKey);
    if (httpCode == 200){
      Serial.println("Data sent to ThingSpeak successfully!");
    }
    else{
      Serial.println("Failed to send data to ThingSpeak. HTTP error code: " + String(httpCode));
    }
  }
  else{
    Serial.println("WiFi not connected. Please check your WiFi credentials.");
  }
  delay(5000);
}
