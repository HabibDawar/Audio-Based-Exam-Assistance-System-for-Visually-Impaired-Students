#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DFRobotDFPlayerMini.h>

// OLED Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

// Initialize objects
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DFRobotDFPlayerMini myDFPlayer;

// Variables
String barcodeData = "";

void setup() {
  // Initialize Serial for debugging
  Serial.begin(9600);
  
  // Initialize Serial1 for MP3 (Pin 18=TX1, 19=RX1)
  Serial1.begin(9600);
  
  // Initialize Serial2 for barcode scanner (Pin 17=RX2)
  Serial2.begin(9600);
  
  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("OLED failed");
    while(1);
  }
  
  Serial.println("System starting...");
  
  // Display initial message
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();
  
  delay(2000);  // Give time for DFPlayer to boot
  
  // Initialize DFPlayer Mini
  if (!myDFPlayer.begin(Serial1)) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("MP3 Error!");
    display.println("Check:");
    display.println("1. SD Card");
    display.println("2. Wiring");
    display.display();
    Serial.println("DFPlayer init failed");
    while(1);
  }
  
  // Configure DFPlayer
  myDFPlayer.volume(30);  // Set volume to max (0-30)
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  
  Serial.println("DFPlayer ready");
  
  // Show ready message
  display.clearDisplay();
  display.setCursor(10, 20);
  display.setTextSize(2);
  display.println("SCAN");
  display.setCursor(30, 40);
  display.println("& PLAY");
  display.display();
  
  delay(2000);
  
  // Show instruction
  showInstructions();
}

void loop() {
  // Read barcode data
  if (Serial2.available()) {
    char c = Serial2.read();
    
    if (c == '\r' || c == '\n') {
      if (barcodeData.length() > 0) {
        playBarcodeAudio(barcodeData);
        barcodeData = "";
      }
    } else {
      barcodeData += c;
    }
  }
  
  delay(10);
}

void playBarcodeAudio(String barcode) {
  Serial.print("Scanned: ");
  Serial.println(barcode);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Scanned:");
  display.println(barcode);
  display.display();
  
  // Level 1
  if (barcode.startsWith("L1S") && barcode.length() == 5) {
    int qNum = barcode.substring(3, 5).toInt();
    if (qNum >= 1 && qNum <= 15) playAudio(qNum, 1);
    else showError("Invalid soal 1-15");
  }
  else if (barcode.startsWith("L1A") && barcode.length() == 5) {
    int qNum = barcode.substring(3, 5).toInt();
    if (qNum >= 1 && qNum <= 15) playAudio(qNum, 2);
    else showError("Invalid jawaban 1-15");
  }

  // Level 2 (Folder: 21-35)
  else if (barcode.startsWith("L2S") && barcode.length() == 5) {
    int qNum = barcode.substring(3, 5).toInt();
    if (qNum >= 1 && qNum <= 15) playAudio(20 + qNum, 1);
    else showError("Invalid soal 1-15");
  }
  else if (barcode.startsWith("L2A") && barcode.length() == 5) {
    int qNum = barcode.substring(3, 5).toInt();
    if (qNum >= 1 && qNum <= 15) playAudio(20 + qNum, 2);
    else showError("Invalid jawaban 1-15");
  }

  // Level 3 (Folder: 41-50)
  else if (barcode.startsWith("L3S") && barcode.length() == 5) {
    int qNum = barcode.substring(3, 5).toInt();
    if (qNum >= 1 && qNum <= 10) playAudio(40 + qNum, 1);
    else showError("Invalid soal 1-10");
  }
  else if (barcode.startsWith("L3A") && barcode.length() == 5) {
    int qNum = barcode.substring(3, 5).toInt();
    if (qNum >= 1 && qNum <= 10) playAudio(40 + qNum, 2);
    else showError("Invalid jawaban 1-10");
  }

  else {
    showError("Invalid barcode");
  }
}

void playAudio(int folder, int file) {
  Serial.print("Playing folder ");
  Serial.print(folder);
  Serial.print(", file ");
  Serial.println(file);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Playing...");
  
  String level = "";
  if (folder >= 1 && folder <= 15) level = "Level 1";
  else if (folder >= 21 && folder <= 35) level = "Level 2";
  else if (folder >= 41 && folder <= 50) level = "Level 3";
  
  display.print("Level: ");
  display.println(level);
  display.print("Folder: ");
  display.println(folder);
  display.print("File: ");
  display.println(file);
  display.display();
  
  myDFPlayer.playFolder(folder, file);
  delay(100);
}

void showError(String message) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("ERROR:");
  display.println(message);
  display.display();
  delay(2000);
  showInstructions();
}

void showInstructions() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Ready to scan");
  display.println("");
  display.println("Format:");
  display.println("L1S01 - L1A15");
  display.println("L2S01 - L2A15");
  display.println("L3S01 - L3A10");
  display.display();
}
