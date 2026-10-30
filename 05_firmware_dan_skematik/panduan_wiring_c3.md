# 🔌 Panduan Praktis Wiring Hardware ESP32-C3 Super Mini

> **Target Board:** ESP32-C3 Super Mini (16 Pin)  
> **Sensor:** DHT22 (Suhu & Kelembapan), MQ-2 (LPG/Asap), MQ-7 (Karbon Monoksida / CO)  
> **Aktuator:** LED Merah (Indikator Bahaya Gas / Suhu)  
> *(Catatan: Buzzer ditiadakan sesuai konfigurasi terbaru)*

---

## 1. 📋 Tabel Pinout ESP32-C3 Super Mini

Cocokkan koneksi kabel dari ESP32-C3 Super Mini ke masing-masing komponen:

| Pin ESP32-C3 | Terhubung ke Komponen | Jalur Kabel | Fungsi / Keterangan |
| :--- | :--- | :--- | :--- |
| **`3.3V`** | **VCC** Sensor DHT22 | 🟠 Daya 3.3V | Catu daya stabil DHT22 |
| **`5V (VBUS)`** | **VCC** MQ-2 & **VCC** MQ-7 | 🔴 Daya 5V | Catu daya elemen pemanas (*heater*) gas |
| **`GND`** | **GND** Semua Sensor & Katoda LED | ⚫ Ground | Ground bersama (*common ground*) |
| **`GPIO 4`** | **DATA** Sensor DHT22 | 🟣 Sinyal Digital | Pembacaan suhu dan kelembapan ruangan |
| **`GPIO 0`** | **A0 (Analog Out)** Sensor MQ-2 | 🔵 Sinyal Analog | Input ADC1_CH0 (Deteksi asap / gas LPG) |
| **`GPIO 1`** | **A0 (Analog Out)** Sensor MQ-7 | 🟡 Sinyal Analog | Input ADC1_CH1 (Deteksi gas Karbon Monoksida) |
| **`GPIO 5`** | **Anoda (+)** Lampu LED Merah | 🟢 Output Digital | Melalui resistor 220Ω - 330Ω ke kaki anoda LED |

---

## 2. 🧩 Rincian Pemasangan Per Komponen

### A. Sensor DHT22 (Suhu & Kelembapan)
* **Pin 1 (VCC)** ➔ Hubungkan ke pin **`3.3V`** ESP32-C3
* **Pin 2 (DATA)** ➔ Hubungkan ke pin **`GPIO 4`** ESP32-C3 *(Tambahkan resistor pull-up 10kΩ antara VCC & DATA jika modul DHT22 belum memiliki resistor bawaan)*
* **Pin 3 (NC)** ➔ Kosongkan
* **Pin 4 (GND)** ➔ Hubungkan ke rel **`GND`** ESP32-C3

---

### B. Sensor Gas MQ-2 (Deteksi Asap & Gas Metana/LPG)
* **Pin VCC** ➔ Hubungkan ke pin **`5V (VBUS)`** ESP32-C3 *(Wajib 5V agar pemanas sensor bekerja optimal)*
* **Pin GND** ➔ Hubungkan ke rel **`GND`** ESP32-C3
* **Pin A0 (Analog)** ➔ Hubungkan ke pin **`GPIO 0`** ESP32-C3 *(Membaca tegangan analog 0 - 3.3V)*
* **Pin D0 (Digital)** ➔ Kosongkan (tidak digunakan)

---

### C. Sensor Gas MQ-7 (Deteksi Karbon Monoksida / CO)
* **Pin VCC** ➔ Hubungkan ke pin **`5V (VBUS)`** ESP32-C3
* **Pin GND** ➔ Hubungkan ke rel **`GND`** ESP32-C3
* **Pin A0 (Analog)** ➔ Hubungkan ke pin **`GPIO 1`** ESP32-C3
* **Pin D0 (Digital)** ➔ Kosongkan (tidak digunakan)

---

### D. Lampu LED Merah (Indikator Bahaya Visual)
* **Kaki Panjang / Anoda (+)** ➔ Hubungkan ke **Resistor 220Ω atau 330Ω** ➔ lalu ke pin **`GPIO 5`** ESP32-C3
* **Kaki Pendek / Katoda (-)** ➔ Hubungkan ke rel **`GND`** ESP32-C3

---

## 3. 🚨 Logika Ambang Batas Keselamatan

Sistem memantau ambang batas bahaya berdasarkan referensi jurnal dan standar keselamatan:

| Kondisi | Parameter | Status LED Fisik | Status Web Dashboard |
| :--- | :--- | :--- | :--- |
| **Aman / Normal** | Suhu < 35°C **dan** MQ-2 < 300 PPM **dan** MQ-7 < 50 PPM | **MATI** | 🟢 **NORMAL & AMAN** |
| **Waspada / Bahaya**| Suhu ≥ 35°C **atau** MQ-2 ≥ 300 PPM **atau** MQ-7 ≥ 50 PPM | **MENYALA** | 🔴 **PERINGATAN BAHAYA DETEKSI GAS/SUHU** |

---

## 4. 💡 Catatan Penting Pemasangan di Breadboard

1. **Jalur Rel Daya Breadboard:**
   * Sambungkan kabel dari pin **`5V (VBUS)`** ESP32-C3 ke **rel garis merah (+)** breadboard untuk mendistribusikan daya 5V ke sensor MQ-2 dan MQ-7.
   * Sambungkan kabel dari pin **`GND`** ESP32-C3 ke **rel garis biru/hitam (-)** breadboard untuk semua ground.
2. **Kebutuhan Daya Listrik:**
   * Sensor MQ-2 dan MQ-7 memiliki elemen pemanas internal yang mengonsumsi arus sekitar 300 - 350 mA. Pastikan catu daya USB yang terhubung ke ESP32-C3 mampu mengeluarkan arus minimal 1.5A–2A stabil.
3. **Pemanasan Awal (*Preheat Time*):**
   * Sensor seri MQ memerlukan waktu pemanasan awal sekitar 1–2 menit saat pertama kali dinyalakan agar pembacaan nilai gas stabil.
