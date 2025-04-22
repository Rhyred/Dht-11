#include <DHT.h> // Mengimpor library DHT

#define DHTPIN 2          // Pin yang terhubung ke sensor DHT11
#define DHTTYPE DHT11     // Menentukan tipe sensor DHT yang digunakan

DHT dht(DHTPIN, DHTTYPE); // Membuat objek DHT

// Mendefinisikan pin untuk LED dan buzzer
#define LED_HIJAU 3       // Pin untuk LED hijau
#define LED_KUNING 4      // Pin untuk LED kuning
#define BUZZER 5          // Pin untuk buzzer

void setup() {
  Serial.begin(9600);      // Memulai komunikasi serial
  dht.begin();             // Memulai sensor DHT
  pinMode(LED_HIJAU, OUTPUT); // Mengatur pin LED hijau sebagai output
  pinMode(LED_KUNING, OUTPUT); // Mengatur pin LED kuning sebagai output
  pinMode(BUZZER, OUTPUT); // Mengatur pin buzzer sebagai output
}

void loop() {
  // Membaca suhu dan kelembapan dari sensor DHT
  float suhu = dht.readTemperature(); // Membaca suhu dalam Celsius
  float kelembapan = dht.readHumidity(); // Membaca kelembapan

  // Memeriksa apakah pembacaan gagal dan keluar jika gagal
  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("Gagal membaca dari sensor DHT!");
    return;
  }

  // Menampilkan suhu dan kelembapan ke Serial Monitor
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" °C, Kelembapan: ");
  Serial.print(kelembapan);
  Serial.println(" %");

  // Mengatur batas suhu normal
  float suhuMin = 20.0; // Batas suhu minimum (misalnya 20°C)
  float suhuMax = 30.0; // Batas suhu maksimum (misalnya 30°C)

  // Memeriksa kondisi suhu
  if (suhu < suhuMin || suhu > suhuMax) {
    // Jika suhu terlalu dingin atau panas
    digitalWrite(LED_KUNING, HIGH); // Nyalakan LED kuning
    digitalWrite(BUZZER, HIGH);      // Nyalakan buzzer
    digitalWrite(LED_HIJAU, LOW);    // Matikan LED hijau
  } else {
    // Jika suhu dalam rentang normal
    digitalWrite(LED_HIJAU, HIGH);   // Nyalakan LED hijau
    digitalWrite(BUZZER, LOW);        // Matikan buzzer
    digitalWrite(LED_KUNING, LOW);    // Matikan LED kuning
  }

  delay(2000); // Tunggu 2 detik sebelum membaca lagi
}
