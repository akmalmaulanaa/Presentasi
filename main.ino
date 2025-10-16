/*
  ================================================
  PENERAPAN HTML UNTUK IoT (Versi Lengkap)
  Akmal Maulana – SMKN 4 Bandung
  ================================================
  Fitur:
  - Monitoring suhu & kelembapan (DHT11)
  - Simulasi tegangan
  - Kontrol LED dari web
  - Tampilan (HTML + CSS + JS)
*/

#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// ====== 1. Koneksi WiFi ======
const char* ssid = "ESP-32_DHT11";
const char* password = "12345678";

// ====== 2. Inisialisasi WebServer ======
WebServer server(80);

// ====== 3. Inisialisasi Sensor DHT11 ======
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ====== 4. Pin LED ======
#define LED_PIN 2

// ====== 5. Variabel data ======
float suhu = 0;
float kelembapan = 0;
float tegangan = 220.0; // Simulasi tegangan PLN

// ====== 6. HTML Tampilan Web ======
const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="id">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>IoT Monitoring Dashboard</title>
<style>
  body {
    margin: 0; font-family: 'Segoe UI'; background: radial-gradient(circle at top, #0a192f, #020c1b);
    color: #e6f1ff; text-align: center; overflow-x: hidden;
  }
  h1 { color: #64ffda; text-shadow: 0 0 10px #64ffda; margin-top: 20px; }
  .container {
    display: flex; flex-wrap: wrap; justify-content: center; gap: 20px; margin-top: 40px;
  }
  .card {
    background: rgba(255,255,255,0.05); border: 1px solid rgba(100,255,218,0.3);
    border-radius: 20px; width: 250px; padding: 25px;
    box-shadow: 0 0 15px rgba(100,255,218,0.2); backdrop-filter: blur(10px);
    transition: 0.3s;
  }
  .card:hover { transform: scale(1.05); }
  .value { font-size: 2em; color: #64ffda; margin: 10px 0; }
  button {
    background: #64ffda; border: none; padding: 10px 20px;
    border-radius: 10px; font-weight: bold; cursor: pointer;
    transition: 0.3s;
  }
  button:hover { background: #52d7ba; }
  footer { margin-top: 40px; font-size: 0.8em; color: #8892b0; }
</style>
</head>
<body>
  <h1>IoT Monitoring Dashboard</h1>

  <div class="container">
    <div class="card">
      <h3>Suhu</h3>
      <div id="suhu" class="value">-- °C</div>
    </div>
    <div class="card">
      <h3>Kelembapan</h3>
      <div id="kelembapan" class="value">-- %</div>
    </div>
    <div class="card">
      <h3>Tegangan</h3>
      <div id="tegangan" class="value">-- V</div>
    </div>
    <div class="card">
      <h3>Kontrol LED</h3>
      <button onclick="ledOn()">Hidupkan</button>
      <button onclick="ledOff()">Matikan</button>
    </div>
  </div>

  <footer>Akmal Maulana • SMKN 4 Bandung</footer>

  <script>
    function updateData() {
      fetch('/data')
        .then(res => res.json())
        .then(data => {
          document.getElementById("suhu").innerHTML = data.suhu + " °C";
          document.getElementById("kelembapan").innerHTML = data.kelembapan + " %";
          document.getElementById("tegangan").innerHTML = data.tegangan + " V";
        });
    }

    function ledOn() { fetch('/led/on'); }
    function ledOff() { fetch('/led/off'); }

    setInterval(updateData, 2000);
  </script>
</body>
</html>
)rawliteral";

// ====== 7. Fungsi Web Handler ======
void handleRoot() { server.send(200, "text/html", MAIN_page); }

void handleData() {
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();
  tegangan = 220 + random(-5, 5); // simulasi fluktuasi

  String json = "{";
  json += "\"suhu\":" + String(suhu, 1) + ",";
  json += "\"kelembapan\":" + String(kelembapan, 1) + ",";
  json += "\"tegangan\":" + String(tegangan, 1);
  json += "}";

  server.send(200, "application/json", json);
}

void handleLedOn() {
  digitalWrite(LED_PIN, HIGH);
  server.send(200, "text/plain", "LED ON");
}

void handleLedOff() {
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/plain", "LED OFF");
}

// ====== 8. Setup ======
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  dht.begin();
  pinMode(LED_PIN, OUTPUT);

  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nTerhubung!");
  Serial.print("Alamat IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.on("/led/on", handleLedOn);
  server.on("/led/off", handleLedOff);
  server.begin();

  Serial.println("Server web berjalan...");
}

// ====== 9. Loop utama ======
void loop() {
  server.handleClient();
}
