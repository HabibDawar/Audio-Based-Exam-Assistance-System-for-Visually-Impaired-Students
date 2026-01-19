Sistem Pemutaran Audio Berbasis Barcode
Arduino Mega + EP1870 TTL + MP3 TF-16P + OLED SSD1306

Deskripsi Proyek :
Sistem ini digunakan untuk memutar file audio MP3 berdasarkan hasil
scan barcode. Ketika barcode terbaca, hasil scan akan ditampilkan di
OLED kemudian audio yang sesuai dengan nomor barcode akan diputar.



Fitur Utama :
Membaca barcode TTL Scanner EP1870
Menampilkan hasil scan pada OLED SSD1306
Memutar audio MP3 via MP3 TF-16P v3.0
Sistem cepat dan stabil menggunakan Arduino Mega
Struktur folder audio rapi dan mudah diatur

Daftar Komponen :
Arduino Mega 2560
Barcode Scanner EP1870 TTL
MP3 Player TF-16P v3.0
OLED SSD1306 I2C 0.96"
MicroSD FAT32 berisi audio
Speaker aktif atau amplifier audio
Kabel jumper dan catu daya 5V

Wiring/Skema Koneksi:

Barcode Scanner EP1870 TTL
TX → Arduino Mega RX1 (Pin 19)
RX → Arduino Mega TX1 (Pin 18)
VCC → 5V
GND → GND

MP3 TF-16P v3.0
TX → Pin 17 
RX → Pin 16
VCC → 5V
GND → GND

OLED SSD1306 I2C
SDA → Pin 20
SCL → Pin 21
VCC → 5V
GND → GND

Catatan (opsional):
Tambahkan kapasitor 100–470 µF di jalur power MP3 bila diperlukan
Disarankan sumber 5V yang stabil, hindari mengambil langsung dari USB laptop

Struktur Folder Audio
MicroSD FAT32

/
├── 01/
│ ├── 001.mp3
│ ├── 002.mp3
│ └── dst...
└── 002/
├── 001.mp3
└── dst...

Barcode → L1S01 (L(1/2/3) = untuk level, S/A = soal/answer, 01 - 15 = untuk nomor soal/folder)
Contoh:
Barcode = L1S01 → File: /001/001.mp3 (Soal)

Alur Kerja Sistem (Algoritma) :
Sistem mulai dan inisialisasi OLED, Serial, MP3
OLED menampilkan "SCAN NOW"
Sistem menunggu input dari barcode scanner
Jika barcode masuk:
Tampilkan hasil di OLED
Konversi ke angka
Panggil file MP3 sesuai nomor
Kembali ke mode tunggu scan

Library yang Digunakan :
Adafruit SSD1306
Adafruit GFX
DFRobotDFPlayerMini
Semua tersedia di Arduino Library Manager.

Pengaturan Baud Rate :
UART1 (Barcode Scanner) : 9600
SoftwareSerial (MP3) : 9600

Troubleshooting
Masalah: Barcode tidak terbaca
Solusi: Cek TX-RX scanner, pastikan baudrate 9600

Masalah: OLED tidak menyala
Solusi: Cek alamat I2C (0x3C), pastikan SDA/SCL benar

Masalah: MP3 tidak mengeluarkan suara
Solusi: MicroSD harus FAT32, kapasitas < 32GB, file format .mp3

Masalah: Saat play audio modul reset
Solusi: Perkuat catu daya MP3 (gunakan adapter 5V eksternal)

Catatan Khusus
Arduino Nano tidak direkomendasikan karena keterbatasan UART
Arduino Mega paling stabil untuk 3 perangkat komunikasi
Speaker menggunakan amplifier tambahan (opsional)