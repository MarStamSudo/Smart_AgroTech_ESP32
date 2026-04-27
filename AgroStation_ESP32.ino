#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <DHT.h>
#include "config.h" // 🆕 Εισαγωγή των ρυθμίσεων από το κρυφό αρχείο

// --- ΡΥΘΜΙΣΕΙΣ ΑΙΣΘΗΤΗΡΩΝ ---
#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BME280 bme;

bool bmeAvailable = false;

void setup() {
  Serial.begin(115200);
  delay(1000);

  dht.begin();

  // Δοκιμή I2C για τον BME280 (0x76 ή 0x77)
  if (bme.begin(0x76) || bme.begin(0x77)) {
    bmeAvailable = true;
    Serial.println(F("BME280 Sensor Found"));
  } else {
    bmeAvailable = false;
    Serial.println(F("BME280 Not Found! Fallback to DHT22."));
  }

  // Σύνδεση στο WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print(F("Connecting to WiFi"));
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(F("\nConnected!"));
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float t, h, p = 0;

    // Λογική Ανάγνωσης με Redundancy
    if (bmeAvailable) {
      t = bme.readTemperature();
      h = bme.readHumidity();
      p = bme.readPressure() / 100.0F; // Pa to hPa

      if (isnan(t) || isnan(h)) {
        t = dht.readTemperature();
        h = dht.readHumidity();
      }
    } else {
      t = dht.readTemperature();
      h = dht.readHumidity();
    }

    // --- CALIBRATION OFFSETS ---
    // Προσαρμογή βάσει σύγκρισης (π.χ. με το Xiaomi σου)
    t = t - 0.9; 
    h = h + 3.4;

    // Έλεγχος εγκυρότητας τιμών
    if (isnan(t)) t = 0.0;
    if (isnan(h)) h = 0.0;

    Serial.printf("Temp: %.2f | Hum: %.2f | Pres: %.2f hPa\n", t, h, p);

    // Αποστολή Δεδομένων
    HTTPClient http;
    http.begin(SERVER_URL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Χρήση String για το POST data
    String httpRequestData = "api_key=" + API_KEY +
                             "&station_id=" + STATION_ID +
                             "&temp=" + String(t, 2) +
                             "&hum=" + String(h, 2) +
                             "&pres=" + String(p, 2);

    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      Serial.print(F("HTTP Response: "));
      Serial.println(httpResponseCode);
    } else {
      Serial.printf("Error occurred during HTTP POST: %s\n", http.errorToString(httpResponseCode).c_str());
    }

    http.end();
  } else {
    Serial.println(F("WiFi Connection Lost"));
  }

  // Αναμονή 30 δευτερολέπτων (Στόχος: Deep Sleep για εξοικονόμηση ενέργειας)
  delay(30000);
}
