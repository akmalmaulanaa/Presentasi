# ⚡ Penerapan HTML untuk IoT

Proyek ini menunjukkan bagaimana **HTML digunakan dalam sistem IoT** untuk membangun **dashboard monitoring futuristik** menggunakan **ESP32** dan **sensor DHT11** 🌐

---

## 🧠 Deskripsi Proyek
Proyek ini memungkinkan pengguna untuk:
- 📊 Memantau **suhu**, **kelembapan**, dan **tegangan** secara *real-time*  
- 💻 Menampilkan data dalam **web dashboard futuristik** berbasis HTML + CSS  
- 🔘 Mengontrol LED langsung dari browser  

Semua berjalan **tanpa server eksternal**, karena **ESP32** berperan sebagai *web server mini*.

---

## ⚙️ Komponen & Library

### 🔩 **Perangkat Keras**
- ESP32 Dev Board  
- Sensor DHT11  
- LED (opsional untuk kontrol)  
- Kabel jumper & breadboard  

### 📚 **Library yang Digunakan**
| Library | Deskripsi |
|----------|------------|
| `WiFi.h` | Menghubungkan ESP32 ke jaringan WiFi |
| `WebServer.h` | Membuat web server di ESP32 |
| `DHT sensor library by Adafruit` | Membaca data suhu & kelembapan |
| `Adafruit Unified Sensor` | Dukungan sensor universal untuk DHT |

---

## 🏗️ Struktur Label dalam Kode `.ino`

| 🔖 Label | 🧩 Fungsi |
|-----------|------------|
| **[LABEL: LIBRARY_SETUP]** | Import semua library & inisialisasi sensor |
| **[LABEL: SENSOR_SETUP]** | Menentukan pin dan tipe sensor DHT11 |
| **[LABEL: WIFI_SETUP]** | Menghubungkan ESP32 ke jaringan WiFi |
| **[LABEL: HTML_DASHBOARD]** | HTML + CSS futuristik untuk dashboard web |
| **[LABEL: SERVER_ROUTE]** | Mengatur route `/` dan `/data` |
| **[LABEL: SENSOR_READ]** | Membaca data dari sensor DHT11 |
| **[LABEL: DATA_ENDPOINT]** | Mengirim data sensor dalam format JSON |
| **[LABEL: LOOP_CONTROL]** | Menjalankan server dan memperbarui data |

---

## 🌐 Tampilan Dashboard

Tampilan web menggunakan **tema futuristik** dengan:
- 🎨 Gradasi gelap biru-ungu  
- ✨ Efek neon lembut  
- 🧊 Elemen transparan (*glassmorphism*)  
- 🔄 Pembaruan data otomatis setiap 1 detik  

Contoh elemen:
```html
<div class="card">
  <p>Suhu: <span id="suhu">--</span> °C</p>
  <p>Kelembapan: <span id="kelembapan">--</span> %</p>
  <p>Tegangan: <span id="tegangan">--</span> V</p>
</div>
