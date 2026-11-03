# 📦 Smart Environmental Sensing System (ESS) - 3D CAD Enclosure & Hardware

**Bengkel Mekatronika Politeknik Kota Malang (POLTEKOM)**  
*Dokumentasi Resmi Desain Mekanik 3D (CAD), Fabrikasi Laser Cutting Akrilik, Gambar Kerja Teknik Skala 1:1, dan Firmware IoT.*

- **Pengembang:** Zakky Satrya ([@Zakkysyy](https://github.com/Zakkysyy))
- **Platform CAD:** [Onshape Free / Professional](https://cad.onshape.com/)
- **Metode Fabrikasi:** Akrilik Bening/Warna Tebal 3.0 mm (Laser Cutting CNC & Drilling)
- **Live Dashboard Web:** [https://poltekom-ess.web.app/](https://poltekom-ess.web.app/)

---

## 📐 1. Spesifikasi Teknis & Dimensi Enclosure V2

Enclosure V2 dirancang dengan konsep **Integrated Horizontal Dual-Chamber** (Ruang Depan untuk Elektronika/PCB + Ruang Belakang untuk Lorong Aliran Gas/Tunnel) yang kokoh, rapi, dan mudah dibongkar-pasang.

| Parameter | Dimensi Teknis | Catatan / Toleransi |
| :--- | :--- | :--- |
| **Dimensi Luar Bodi Dinding** | $120.0 	imes 90.0 	imes 50.0\text{ mm}$ | Sambungan purus mortise-tenon sudut interlocking |
| **Dimensi Pelat Atas & Bawah** | $134.0 	imes 104.0\text{ mm}$ | Overhang keliling $7.0\text{ mm}$, 4 sudut fillet $R=3.5\text{ mm}$ |
| **Tebal Bahan Akrilik** | $3.00\text{ mm}$ | Toleransi slot lubang purus: **$3.10\text{ mm}$** (pas tanpa seret) |
| **Sistem Pengunci Dinding** | 10 Slot Purus Tertutup | Daging akrilik luar $7.0\text{ mm}$ (sangat kokoh & tidak mudah pecah) |
| **Tiang Penyangga (Standoff)** | 4x Hex Spacer M3 ($50.0\text{ mm}$)| Male-to-Female Nylon Hex ($5.4\text{ mm}$ AF, stud bawah $6.0\text{ mm}$) |
| **Baut Pengunci Utama** | 8x Pan Head M3 ($10.0\text{ mm}$) | Kepala $\varnothing 5.0\text{ mm}$ sesuai standar datasheet |
| **Saluran Kipas (Dinding Kanan)** | Bore $\varnothing 28.20\text{ mm}$ | **Grille Palang Plus (+)** tebal **$2.50\text{ mm}$** pelindung baling-baling |

---

## 🗂️ 2. Struktur Repositori Bersih & Bebas Duplikat

Repositori ini telah dirapikan secara ketat agar tidak ada file versi lama (`v2_` atau nama ganda) yang saling bertabrakan:

```text
poltekom-ess-enclosure/
├── 📁 01_dxf_akrilik_laser/             <-- 7 Part Akrilik Satuan (Siap Import ke Onshape / CorelDRAW)
│   ├── 01_pelat_penutup_atas.dxf       (134 x 104 mm, 4 lubang spacer M3, 10 slot purus tertutup)
│   ├── 02_pelat_dasar_bawah.dxf        (134 x 104 mm, dasar solid pelindung PCB dari debu)
│   ├── 03_dinding_depan.dxf            (120 x 50 mm, jendela OLED 0.96", DHT22, LED RGB 5mm)
│   ├── 04_sekat_tengah.dxf             (120 x 50 mm, dudukan MQ-2, MQ-7, PCB ESS 5, slot fan)
│   ├── 05_dinding_belakang.dxf         (120 x 50 mm, solid polos penutup lorong gas belakang)
│   ├── 06_dinding_sisi_kiri.dxf        (84 x 50 mm, kisi pendingin ESP32 & 37 lubang Honeycomb)
│   └── 07_dinding_sisi_kanan.dxf       (84 x 50 mm, Port DC Jack & Kipas 3010 Grille Plus 2.5mm)
│
├── 📁 02_model_3d_stl/                 <-- 6 Model Solid 3D Watertight (Untuk Onshape / 3D Print)
│   ├── 08_spacer_nylon_m3_50mm.stl     (Spacer Male-to-Female M3 tinggi 50mm hex 5.4mm)
│   ├── 09_baut_pan_head_m3_10mm.stl    (Baut Pan Head M3x10mm kepala 5.0mm)
│   ├── 10_mur_hex_m3.stl               (Mur Hexagon M3 tebal 2.4mm lebar 5.5mm)
│   ├── 11_modul_sensor_mq2.stl         (Modul MQ-2 PCB 20x32mm, tabung sensor Dia 20.5mm)
│   ├── 12_modul_sensor_mq7.stl         (Modul MQ-7 PCB 20x32mm, tabung sensor Dia 18.4mm)
│   └── 13_pcb_ess_5.stl                (Modul PCB ESS 5 70x40mm pitch baut 64.4x34.4mm)
│
├── 📁 03_siap_potong_laser_cutting/    <-- Berkas Gabungan Lembar Kerja Mesin Laser Cutting CNC
│   ├── laser_cutting_v2_integrated_box.dxf  (AutoCAD DXF Hairline 0.2mm Red Cut)
│   ├── laser_cutting_v2_integrated_box.svg  (Scalable Vector Graphics untuk CorelDRAW)
│   └── laser_cutting_v2_integrated_box_1to1.pdf (PDF Vektor Skala 1:1)
│
├── 📁 04_gambar_kerja_cetak_a4_1to1/   <-- Gambar Kerja Teknik Resmi A4 / A3
│   ├── Gambar_Kerja_A4_3Halaman_Skala_1to1.pdf (Standar Fabrikasi 3 Halaman ISO A4)
│   ├── Gambar_Kerja_A4_MultiHalaman_Skala_1to1.pdf (Format 1 Part Per Halaman)
│   └── Gambar_Kerja_Teknik_A3_Skala_1to1.pdf (Format Gambar Teknik A3 Studio)
│
├── 📁 05_firmware_dan_skematik/        <-- Kode Sumber IoT & Jalur Sirkuit Elektronika
│   ├── sketch.ino                      (Firmware ESP32-C3 SuperMini Telemetri Firebase)
│   ├── panduan_wiring_c3.md            (Tabel koneksi pinout ESP32, Sensor, I2C, dan Power)
│   ├── wiring_pinout.txt               (Catatan teknis jalur jumper kabel)
│   ├── PCB_PCB-ESS-5_2026-10-09.svg    (Skematik jalur sirkuit PCB EasyEDA)
│   └── PCB_PCB_ESS_5_2026-10-09.json   (Netlist & komponen PCB format JSON)
│
└── 📁 06_dokumentasi_visual/           <-- Diagram Skematis & Hasil Render
    ├── preview_dinding_kanan_grille.png (Preview Grille Palang Plus Kipas Dia 28.2mm)
    ├── preview_laser_cutting_v2.png    (Tampilan susunan cutting sheet)
    ├── arsitektur_stack_tunnel_dan_case.png (Diagram penempatan komponen)
    └── panduan_mate_baut_dan_mur_onshape.png (Tutorial perakitan Assembly Onshape)
```

---

## 🛠️ 3. Rincian Lubang Mounting Komponen & Toleransi

Seluruh lubang baut di desain CAD **sudah diberi toleransi normal clearance $+0.20\text{ mm}$** dari ukuran nominal baut agar tidak seret dan mencegah akrilik retak saat dirakit:

1. **Lubang Baut M3 (Nominal $3.00\text{ mm}$): Dibuat $\varnothing 3.20\text{ mm}$**
   * 4 Lubang Dudukan PCB ESS 5 pada Sekat Tengah (*Pitch $64.40 \times 34.40\text{ mm}$*).
   * 4 Lubang Modul Sensor MQ-2 pada Sekat Tengah (*Pitch $15.00 \times 27.00\text{ mm}$*).
   * 4 Lubang Modul Sensor MQ-7 pada Sekat Tengah (*Pitch $15.00 \times 27.00\text{ mm}$*).
   * 4 Lubang Dudukan Kipas Exhaust 3010 pada Dinding Kanan (*Pitch $24.00 \times 24.00\text{ mm}$*).
   * 4 Lubang Spacer Luar pada Pelat Penutup Atas & Alas Bawah (*Margin $3.50\text{ mm}$*).
   * 1 Lubang PCB Sensor DHT22 pada Dinding Depan (*Posisi bawah*).

2. **Lubang Baut M2.5 / M2 (Nominal $2.00 - 2.50\text{ mm}$):**
   * 4 Lubang Layar OLED 0.96" pada Dinding Depan: **$\varnothing 2.50\text{ mm}$** (*Pitch $21.00 \times 22.00\text{ mm}$*).
   * 1 Lubang Kuping Sensor DHT22 pada Dinding Depan: **$\varnothing 2.60\text{ mm}$** (*Posisi atas, pitch vertikal tepat $28.00\text{ mm}$*).

3. **Port & Saluran Khusus:**
   * **Bore Kipas 3010:** $\varnothing 28.20\text{ mm}$ dengan **Palang Plus (+) Tebal $2.50\text{ mm}$** terpusat di $(Y=63.0, Z=25.0)$.
   * **Port DC Jack (DC-022 Pasaran):** $\varnothing 11.60\text{ mm}$ di samping terminal daya PCB.
   * **LED RGB 5mm:** Lubang tembus $\varnothing 5.50\text{ mm}$ tegak lurus port LED D1 PCB.
   * **Inlet Udara Sensor Gas:** Filter Honeycomb 37 lubang heksagonal $\varnothing 2.30\text{ mm}$.
   * **Slot Jalur Kabel Kipas:** Lubang sudut tumpul $8.0 \times 4.5\text{ mm}$ ($R=1.2\text{ mm}$) pada Sekat Tengah.

---


### 📋 Tabel Rekap Kebutuhan Fastener & Lokasi Pemakaian (Final)

| No | Nama Barang & Ukuran | Dipakai di Mana (Lokasi & Komponen) | Jumlah Pas | Saran Beli (+ Cadangan) | Keterangan Bahan & Catatan |
| :---: | :--- | :--- | :---: | :---: | :--- |
| **1** | **Spacer Hex M3 $\times 50\text{ mm}$** *(Male-to-Female)* | **4 Sudut Luar Enclosure**<br>— Tiang penyangga antara Pelat Atas dan Pelat Bawah | 4 pcs | **4 – 5 pcs** | Nylon Putih / Hitam<br>*(Hex 5.4 mm, male stud 6.0 mm)* |
| **2** | **Baut Pan Head M3 $\times 10\text{ mm}$** | • **Pelat Atas** (4 pcs ke lubang atas spacer)<br>• **PCB ESS 5** (4 pcs di Sekat Tengah)<br>• **Modul Sensor MQ-7** (4 pcs di Sekat Tengah)<br>• **Modul Sensor MQ-2** (4 pcs di Sekat Tengah)<br>• **Sensor DHT22 Bawah** (1 pc di Dinding Depan) | 17 pcs | **20 – 25 pcs** | Stainless / Besi Hitam<br>*(Kepala $\varnothing 5.0\text{ mm}$, seragam & universal)* |
| **3** | **Baut Panjang M3 $\times 16\text{ mm}$** *(atau $15\text{ mm}$)* | **Dinding Sisi Kanan**<br>— Dudukan Kipas Exhaust 3010 (tembus akrilik 3mm + bodi kipas 10mm) | 4 pcs | **6 pcs** | Stainless / Besi Hitam |
| **4** | **Spacer Mini PCB M3 $\times 5\text{ mm}$** *(atau $6\text{ mm}$)* | **Sekat Tengah ke PCB ESS 5**<br>— Ganjal antara akrilik dan PCB agar kaki solderan tidak nempel/konslet | 4 pcs | **6 – 10 pcs** | Nylon / Kuningan<br>*(Female-to-Female)* |
| **5** | **Mur Hexagon M3** *(Nut M3)* | • **Pelat Alas Bawah** (4 pcs kunci stud spacer)<br>• **Kipas Exhaust 3010** (4 pcs)<br>• **PCB ESS 5** (4 pcs)<br>• **Modul Sensor MQ-7** (4 pcs)<br>• **Modul Sensor MQ-2** (4 pcs)<br>• **Sensor DHT22 Bawah** (1 pc) | 21 pcs | **25 – 30 pcs** | Stainless / Besi Hitam |
| **6** | **Baut Pan Head M2 $\times 8\text{ mm}$** | • **Layar OLED 0.96\"** (4 pcs di Dinding Depan)<br>• **Sensor DHT22 Atas** (1 pc di kuping gantung bodi putih) | 5 pcs | **8 – 10 pcs** | Stainless / Besi Hitam |
| **7** | **Mur Hexagon M2** *(Nut M2)* | • **Layar OLED 0.96\"** (4 pcs)<br>• **Sensor DHT22 Atas** (1 pc) | 5 pcs | **8 – 10 pcs** | Stainless / Besi Hitam |

---

## 🖨️ 4. Panduan Cetak Kertas Skala 1:1 (Anti-Menyusut)

Di setiap lembar PDF pada folder `04_gambar_kerja_cetak_a4_1to1/`, terdapat **"PENGGARIS KALIBRASI CETAK 100 mm (10 cm)"** di pojok kanan atas.

Saat mencetak ke printer fisik:
1. Buka file PDF menggunakan **Adobe Acrobat Reader** atau browser (Google Chrome / Edge).
2. Tekan `Ctrl + P`.
3. **PENTING:** Pada pengaturan ukuran cetak (*Page Sizing*), **PILIH "Actual size"** atau ubah *Scale* menjadi **"Custom: 100%"**.
4. **JANGAN** memilih *"Fit"* atau *"Shrink oversized pages"*, karena printer otomatis mengecilkan gambar sekitar 4%–6% jika opsi ini aktif.
5. Setelah tercetak, ukur garis kalibrasi dengan mistar fisik. Jika tepat $10.0\text{ cm}$, maka hasil cetak akrilik dijamin pas $100\%$ milimeter nyata!

---

## 💻 5. Firmware IoT ESP32-C3 & Pinout Singkat

File firmware `sketch.ino` di folder `05_firmware_dan_skematik/` menghubungkan ESP32-C3 SuperMini dengan sensor lingkungan dan mengirim data secara live ke Firebase Realtime Database:

| Komponen | Pin ESP32-C3 | Fungsi |
| :--- | :---: | :--- |
| **Layar OLED 0.96"** | `GPIO 8` (SDA) / `GPIO 9` (SCL) | I2C Display Telemetri & Status K3 |
| **Sensor DHT22** | `GPIO 2` | Pembaca Suhu (°C) & Kelembapan (% RH) |
| **Sensor MQ-7** | `GPIO 0` (ADC1_CH0) | Deteksi Gas Karbon Monoksida (CO PPM) |
| **Sensor MQ-2** | `GPIO 1` (ADC1_CH1) | Deteksi Gas Asap & LPG (PPM) |
| **LED RGB Indikator** | `GPIO 3` (Red) / `GPIO 4` (Green) / `GPIO 5` (Blue) | Indikator Status K3 Visual |
| **Kipas Exhaust 3010** | `5V` (DC Jack / Terminal) | Aliran udara aktif hisap gas ke lorong |

---

## 📜 Lisensi & Hak Cipta
Dikembangkan untuk Proyek Magang **Smart Environmental Sensing System (ESS)** di **Politeknik Kota Malang (POLTEKOM)**, 2026.
Bebas digunakan dan dimodifikasi untuk keperluan akademik dan pengembangan sistem IoT bengkel.
