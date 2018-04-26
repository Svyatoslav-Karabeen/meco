/*
 * Project meco
 * TODO: Description: IoT Devices
 * Author: Svyatoslav Polishchuk
 * Date: 25/04/2018
 *
 * https://www.hackster.io/ravee-tansangworn/reading-rfid-card-or-key-ring-and-display-on-lcd-b2f70d
 */

 // #include "LiquidCrystal_I2C.h"
 #include "RFID.h"

 #define SS_PIN      A2
 #define RST_PIN     D3

 // int led1 = D7;

 MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance.
 // LiquidCrystal_I2C lcd(0x27,20,4);

 void setup()
 {
     Serial.begin(9600);                                                         // Open serial over USB
     while(!Serial.isConnected()) Particle.process();                            // Wait if terminal isn't connected
     Serial.println("What's up  Serial! 2 ");
   // lcd.init();
   // lcd.backlight();
    //  SPI.begin();
    //  SPI.setClockDivider(SPI_CLOCK_DIV8);
 // 	pinMode(led1, OUTPUT);
     mfrc522.PCD_Init();
 }

 void loop() {

    //  digitalWrite(led1, LOW);
     // Look for new cards, if nothing found, quit
     if ( ! mfrc522.PICC_IsNewCardPresent()) {
     	return;
        Serial.println("New card found");
     }

     // Select one of the cards, if nothing found, quit
     if ( ! mfrc522.PICC_ReadCardSerial()) {
     	return;
        Serial.println("Something found");
     }

     String cardID = "";

     for (byte i = 0; i < mfrc522.uid.size; i++) {
         cardID += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
         cardID += String(mfrc522.uid.uidByte[i], HEX);
     }
    //  digitalWrite(led1, HIGH);
     Serial.println(cardID);
     mfrc522.PICC_HaltA();
     Serial.println("Nothing found");
     delay(1000);

    //  lcd.clear();
 }
