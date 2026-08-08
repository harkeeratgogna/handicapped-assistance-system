#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int ecgPin = A0;
unsigned long lastPrint = 0;
const unsigned long interval = 2000;

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // Comment this line to HIDE ECG from Serial Monitor
   //int ecgValue = analogRead(ecgPin);
 // Serial.println(ecgValue); // <--- Uncomment only if you want ECG in Plotter

  if (millis() - lastPrint >= interval) {
    lastPrint = millis();

    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" °C\tHumidity: ");
    Serial.print(hum);
    Serial.println(" %");
  }

  delay(10);
}
