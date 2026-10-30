/*
  =============================================================================
  PROYEK IoT ENVIRONMENTAL & GAS SENSING
  Target Board : ESP32-C3 Super Mini
  Sensor       : DHT22 (Suhu & Kelembapan), MQ-2 (LPG/Asap), MQ-7 (Karbon Monoksida / CO)
  Aktuator     : LED Merah (Indikator Bahaya Visual - Tanpa Buzzer)
  Cloud        : Firebase Realtime Database (via HTTPS REST API)
  =============================================================================
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "DHT.h"

// ---------------------- 1. KONFIGURASI WIFI & FIREBASE ----------------------
// Ganti dengan kredensial WiFi Anda
const char* WIFI_SSID = "NAMA_WIFI_ANDA";
const char* WIFI_PASSWORD = "PASSWORD_WIFI_ANDA";

// URL Firebase Realtime Database Anda (akhiri dengan /sensor_data.json)
// Contoh: "https://proyek-iot-kamu-default-rtdb.asia-southeast1.firebasedatabase.app/sensor_data.json"
// Atau: "https://proyek-iot-kamu-default-rtdb.firebaseio.com/sensor_data.json"
const char* FIREBASE_HOST = "https://NAMA_PROJECT_FIREBASE_ANDA-default-rtdb.firebaseio.com/sensor_data.json";

// Opsional: Database Secret / Auth Token jika database Anda diproteksi Rules (biarkan kosong jika mode pengujian)
const char* FIREBASE_AUTH = ""; 

// ---------------------- 2. PINOUT ESP32-C3 SUPER MINI -----------------------
#define DHTPIN   4      // GPIO 4: Data DHT22
#define DHTTYPE  DHT22  // Tipe Sensor DHT22 (AM2302)
#define MQ2PIN   0      // GPIO 0: ADC1_CH0 (MQ-2 LPG & Asap)
#define MQ7PIN   1      // GPIO 1: ADC1_CH1 (MQ-7 Karbon Monoksida / CO)
#define LED_PIN  5      // GPIO 5: Lampu LED Indikator Bahaya Merah

DHT dht(DHTPIN, DHTTYPE);

// Interval pengiriman data ke Firebase (milidetik)
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 2500; // Kirim tiap 2.5 detik

// ---------------------- 3. INISIALISASI SISTEM -----------------------------
void connectWiFi() {
  Serial.print("Menghubungkan ke WiFi: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 25) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Terhubung!");
    Serial.print("IP Address ESP32-C3: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nGagal terhubung ke WiFi. Berjalan dalam mode offline/lokal.");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n==================================================");
  Serial.println(" Sistem Monitoring Lingkungan IoT - ESP32-C3 Super Mini");
  Serial.println("==================================================");

  // Inisialisasi LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Matikan LED saat awal start

  // Inisialisasi Sensor
  dht.begin();
  pinMode(MQ2PIN, INPUT);
  pinMode(MQ7PIN, INPUT);

  // Sambungkan ke WiFi
  connectWiFi();
}

// ---------------------- 4. FUNGSI KIRIM KE FIREBASE ------------------------
void sendToFirebase(float temperature, float humidity, float mq2PPM, float mq7PPM, bool isDanger) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[Firebase] WiFi tidak terhubung, melewati pengiriman.");
    return;
  }

  WiFiClientSecure client;
  client.setInsecure(); // Mengabaikan validasi SSL fingerprint agar kompatibel & hemat memori

  HTTPClient http;
  
  // Format URL dengan Auth Token jika ada
  String url = String(FIREBASE_HOST);
  if (strlen(FIREBASE_AUTH) > 0) {
    url += "?auth=" + String(FIREBASE_AUTH);
  }

  if (http.begin(client, url)) {
    http.addHeader("Content-Type", "application/json");

    // Bentuk JSON Payload
    String statusStr = isDanger ? "BAHAYA" : "AMAN";
    String jsonPayload = "{";
    jsonPayload += "\"suhu\":" + String(temperature, 1) + ",";
    jsonPayload += "\"kelembapan\":" + String(humidity, 1) + ",";
    jsonPayload += "\"mq2_ppm\":" + String((int)mq2PPM) + ",";
    jsonPayload += "\"mq7_ppm\":" + String((int)mq7PPM) + ",";
    jsonPayload += "\"status_lingkungan\":\"" + statusStr + "\",";
    jsonPayload += "\"is_danger\":" + String(isDanger ? "true" : "false") + ",";
    jsonPayload += "\"led_status\":" + String(isDanger ? "true" : "false") + ",";
    jsonPayload += "\"last_updated\":" + String(millis());
    jsonPayload += "}";

    // Kirim menggunakan HTTP PUT agar menggantikan node /sensor_data
    int httpResponseCode = http.PUT(jsonPayload);

    if (httpResponseCode > 0) {
      Serial.print("[Firebase] Data terkirim sukses! HTTP Response: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("[Firebase] Gagal kirim data, Error: ");
      Serial.println(http.errorToString(httpResponseCode).c_str());
    }
    http.end();
  } else {
    Serial.println("[Firebase] Gagal menginisialisasi koneksi HTTPClient.");
  }
}

// ---------------------- 5. LOOP UTAMA --------------------------------------
void loop() {
  // Reconnect WiFi otomatis jika terputus
  if (WiFi.status() != WL_CONNECTED && millis() > 10000) {
    WiFi.reconnect();
  }

  // 1. Baca Sensor Suhu & Kelembapan DHT22
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Validasi pembacaan DHT22
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("[Warning] Gagal membaca sensor DHT22! Memeriksa koneksi...");
    humidity = 0.0;
    temperature = 0.0;
  }

  // 2. Baca Sensor Gas MQ-2 (ADC 0 - 4095 di ESP32-C3)
  int rawMQ2 = analogRead(MQ2PIN);
  // Estimasi kasar PPM Gas LPG/Asap (Ambang batas jurnal: normal < 300 PPM)
  float mq2PPM = map(rawMQ2, 0, 4095, 50, 600);

  // 3. Baca Sensor Gas MQ-7 (ADC 0 - 4095)
  int rawMQ7 = analogRead(MQ7PIN);
  // Estimasi kasar PPM Karbon Monoksida (CO) (Standar aman WHO: < 50 PPM)
  float mq7PPM = map(rawMQ7, 0, 4095, 5, 200);

  // 4. Logika Bahaya & Kontrol LED Merah (Tanpa Buzzer)
  // Bahaya jika: Gas MQ2 >= 300 PPM ATAU Gas MQ7 >= 50 PPM ATAU Suhu >= 35°C
  bool isDanger = (mq2PPM >= 300 || mq7PPM >= 50 || temperature >= 35.0);

  if (isDanger) {
    digitalWrite(LED_PIN, HIGH); // Nyalakan LED Merah Bahaya
  } else {
    digitalWrite(LED_PIN, LOW);  // Matikan LED
  }

  // 5. Cetak ke Serial Monitor untuk Debugging
  Serial.println("----------------------------------------------");
  Serial.printf("Suhu: %.1f *C | Lembap: %.1f %%\n", temperature, humidity);
  Serial.printf("MQ-2 (Raw: %d) -> Estimasi: %.0f PPM\n", rawMQ2, mq2PPM);
  Serial.printf("MQ-7 (Raw: %d) -> Estimasi: %.0f PPM\n", rawMQ7, mq7PPM);
  Serial.printf("Status Sistem : %s | LED Merah: %s\n", 
                isDanger ? "🚨 BAHAYA" : "✅ AMAN", 
                isDanger ? "MENYALA" : "PADAM");
  Serial.println("----------------------------------------------");

  // 6. Kirim Data Berkala ke Firebase
  if (millis() - lastSendTime >= sendInterval) {
    lastSendTime = millis();
    sendToFirebase(temperature, humidity, mq2PPM, mq7PPM, isDanger);
  }

  delay(1000);
}
