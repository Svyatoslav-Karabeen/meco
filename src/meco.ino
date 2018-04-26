/*
 * Project meco
 * TODO: Description: IoT Devices
 * Author: Svyatoslav Polishchuk
 * Date: 25/04/2018
 *
 */

/* Include the RFID library */
/* SEE RFID.h for selecting Hardware or Software SPI modes */
#include "RFID.h"

/* Define the pins used for the SS (SDA) and RST (reset) pins for BOTH hardware and software SPI */
/* Change as required */
#define SS_PIN      A2      // Same pin used as hardware SPI (SS)
#define RST_PIN     D2

/* Define the pins used for the DATA OUT (MOSI), DATA IN (MISO) and CLOCK (SCK) pins for SOFTWARE SPI ONLY */
/* Change as required and may be same as hardware SPI as listed in comments */
#define MOSI_PIN    D3      // hardware SPI: A5
#define MISO_PIN    D4      //     "     " : A4
#define SCK_PIN     D5      //     "     " : A3

/* Create an instance of the RFID library */
#if defined(_USE_SOFT_SPI_)
    RFID RC522(SS_PIN, RST_PIN, MOSI_PIN, MISO_PIN, SCK_PIN);    // Software SPI
#else
    RFID RC522(SS_PIN, RST_PIN);                                 // Hardware SPI
#endif


void setup()
{
    Serial.begin(9600);                                                         // Open serial over USB
    while(!Serial.isConnected()) Particle.process();                            // Wait if terminal isn't connected
    Serial.println("What's up Serial!");

    #if !defined(_USE_SOFT_SPI_)
        SPI.setDataMode(SPI_MODE0);                                             // Enable the HW SPI interface
        SPI.setBitOrder(MSBFIRST);
        SPI.setClockDivider(SPI_CLOCK_DIV8);
        SPI.begin();
    #endif
 
    RC522.init();                                                               // Initialise the RFID reader
}

void loop()
{
  uint8_t i;                                                                    // Temporary loop counter

  if (RC522.isCard())                                                           // Has a card been detected?
  {
    RC522.readCardSerial();                                                     // If so then get its serial number
    Serial.println("Card detected:");

    for(i = 0; i <= 4; i++)                                                     // Output the serial number to the UART
    {
      Serial.print(RC522.serNum[i],HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
  else
      Serial.println("Card NOT detected :(");

  delay(1000);
}
