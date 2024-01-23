#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define TRIG_PIN D2
#define ECHO_PIN D1

const char *ssid = "Farhan_Abadi";
const char *password = "farhanabadi2020";
const char *serverAddress = "http://192.168.1.18/sensor_sonic/kirim_data.php";

WiFiClient wifiClient;  // Deklarasikan objek WiFiClient di sini

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  connectToWiFi();
}

void loop() {
  long duration, distance;
  long totalDistance = 0;
  int numMeasurements = 5;  // Jumlah pengukuran untuk dirata-ratakan

  for (int i = 0; i < numMeasurements; i++) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    totalDistance += duration * 0.034 / 2;

    delay(50);  // Beri waktu sebentar sebelum pengukuran berikutnya
  }

  distance = totalDistance / numMeasurements;

  if (WiFi.status() == WL_CONNECTED) {
    send(distance);
  }

  delay(1000);  // Delay 1 detik sebelum mengukur lagi
}

void connectToWiFi() {
  Serial.println("Connecting To Wifi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Menghubungkan....");
  }

  Serial.println("Terhubung Wifi");
}

void send(long distance) {
  HTTPClient http;

  String url = String(serverAddress) + "?data=" + String(distance);

  // Gunakan objek WiFiClient yang sudah dideklarasikan
  http.begin(wifiClient, url);

  // Gunakan metode sendRequest yang sesuai
  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.println("Data terkirim ke server");
  } else {
    Serial.println("Gagal mengirim data ke server");
  }

  http.end();
}
