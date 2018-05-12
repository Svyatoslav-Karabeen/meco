// Include the RFID library
#include "RFID.h"

// Define the pins used for the SS (SDA) and RST (reset) pins for
// BOTH hardware and software SPI
#define SS_PIN      A2
#define RST_PIN     D2

// Define the pins used for the DATA OUT (MOSI), DATA IN (MISO) and CLOCK (SCK)
// pins for SOFTWARE SPI ONLY
#define MOSI_PIN    D3
#define MISO_PIN    D4
#define SCK_PIN     D5

// Create an instance of the RFID library
#if defined(_USE_SOFT_SPI_)
    RFID RC522(SS_PIN, RST_PIN, MOSI_PIN, MISO_PIN, SCK_PIN);    // Software SPI
#else
    RFID RC522(SS_PIN, RST_PIN);                                 // Hardware SPI
#endif

void setup()
{
    /* ========================== Serial Monitor ========================== */
    Serial.begin(9600);

    Serial.println("Initilasing setup process");



    /* ============================ Components ============================ */
    pinMode(D7, OUTPUT);

    #if !defined(_USE_SOFT_SPI_)                                // Initialise the RFID reader
      SPI.setDataMode(SPI_MODE0);
      SPI.setBitOrder(MSBFIRST);
      SPI.setClockDivider(SPI_CLOCK_DIV8);
      SPI.begin();
    #endif

    RC522.init();

    Serial.println("Componenets setup completed");



    /* ================+========= Particle Cloud ========================== */
    Particle.function("trigger", trigger);                      // Create a function called "trigger" that can be called from the cloud

    Serial.println("Cloud setup completed");
    Serial.println("\n \n \n");
}

// when "trigger" is called from the cloud, it will be accompanied by a string
int trigger(String command)
{

    Serial.println("\n \n \n Trigger received! \n \n \n");

    // if the string is "now", ring the gong once.
    if(command == "now")
    {
        Serial.println("Starting routine \n");
        delay(1000);


        /* ==================== First action ===================== */

        Serial.println("Action 1: Drink Water \n");
        delay(1000);

        for (int actionTime = 10; actionTime > -999; actionTime--) {

            delay(1000);

            Serial.print("Time left: ");
            Serial.print(actionTime);
            Serial.print(" seconds \n");

            if ( RC522.isCard())
            {

                RC522.readCardSerial();
                String cardID = String(RC522.serNum[0], HEX) + String(RC522.serNum[1], HEX) + String(RC522.serNum[2], HEX) + String(RC522.serNum[3], HEX);

                if ( cardID == "eaff17a" )
                {

                    for (int i = 0; i < 3; i++)
                    {
                        digitalWrite(D7, HIGH); // flash the LED
                        delay(100);             // wait 100 ms
                        digitalWrite(D7, LOW);  // turn LED off
                        delay(100);             // wait 100 ms
                    }

                    actionTime = -9999;
                    Serial.println("\n Action completed \n \n \n");
                }


                else
                {
                    Serial.println("***Wrong tag***");
                }
            }
        }



        /* ==================== Second action ===================== */

        Serial.println("Action 2: Take a shower \n");
        delay(1000);

        for (int actionTime = 30; actionTime > -999; actionTime--) {

            delay(1000);

            Serial.print("Time left: ");
            Serial.print(actionTime);
            Serial.print(" seconds \n");

            if ( RC522.isCard())
            {

                RC522.readCardSerial();
                String cardID = String(RC522.serNum[0], HEX) + String(RC522.serNum[1], HEX) + String(RC522.serNum[2], HEX) + String(RC522.serNum[3], HEX);

                if ( cardID == "7abb16a" )
                {

                    for (int i = 0; i < 3; i++)
                    {
                        digitalWrite(D7, HIGH); // flash the LED
                        delay(100);             // wait 100 ms
                        digitalWrite(D7, LOW);  // turn LED off
                        delay(100);             // wait 100 ms
                    }

                    actionTime = -9999;
                    Serial.println("\n Action completed \n \n \n");
                }


                else
                {
                    Serial.println("***Wrong tag***");
                }
            }
        }



        /* ==================== Third action ===================== */

        Serial.println("Action 3: Make a cup of coffee");
        delay(1000);

        for (int actionTime = 15; actionTime > -999; actionTime--) {

            delay(1000);

            Serial.print("Seconds left: ");
            Serial.print(actionTime);
            Serial.print(" seconds \n");

            if ( RC522.isCard())
            {

                RC522.readCardSerial();
                String cardID = String(RC522.serNum[0], HEX) + String(RC522.serNum[1], HEX) + String(RC522.serNum[2], HEX) + String(RC522.serNum[3], HEX);

                if ( cardID == "baaa8a" )
                {

                    for (int i = 0; i < 3; i++)
                    {
                        digitalWrite(D7, HIGH); // flash the LED
                        delay(100);             // wait 100 ms
                        digitalWrite(D7, LOW);  // turn LED off
                        delay(100);             // wait 100 ms
                    }

                    actionTime = -9999;
                    Serial.println("\n Action completed \n \n \n");
                }


                else
                {
                    Serial.println("***Wrong tag***");
                }
            }
        }

        delay(1000);

        Serial.println("\n \n \n Routine complited \n \n \n \n \n \n");
        return 1;
    }

    else if(command == "test")     // if the string is "alarm",
    {
        for (int i = 0; i < 3; i++)
        {
            digitalWrite(D7, HIGH); // flash the LED
            delay(100);             // wait 100 ms
            digitalWrite(D7, LOW);  // turn LED off
            delay(100);             // wait 100 ms
        }
        Serial.println("Test complited");
        return 2;
    }

    else
    {
        Serial.println("Error");
        return 0;
    }
}


void loop()
{
    // Has a card been detected?
    if (RC522.isCard())
    {
        // If so then get its serial number
        RC522.readCardSerial();
        String cardID = String(RC522.serNum[0], HEX) + String(RC522.serNum[1], HEX) + String(RC522.serNum[2], HEX) + String(RC522.serNum[3], HEX);

        // Print this serial number
        Serial.print("Oooops! Tag detected: " + cardID + "\n");
    }


    // If not then wait for trigger
    else
    {
        Serial.println("Waiting for trigger function");
    }

    delay(5000);
}
