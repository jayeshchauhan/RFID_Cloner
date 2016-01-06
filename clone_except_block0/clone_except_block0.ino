/*
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 * 
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

MFRC522::MIFARE_Key key;

/**
 * Initialize.
 */
    byte sector;
    byte status;
    byte newsec[18];
    //three buffers for the 3 blocks below trailer block
    byte buffer0[18],buffer1[18],buffer2[18],buffer3[18],buffer4[18],buffer5[18],buffer6[18],buffer7[18],buffer8[18],buffer9[18],buffer10[18],buffer11[18],buffer12[18],buffer13[18],buffer14[18],buffer15[18],buffer16[18],buffer17[18],buffer18[18],buffer19[18],buffer20[18],buffer21[18],buffer22[18],buffer23[18],buffer24[18],buffer25[18],buffer26[18],buffer27[18],buffer28[18],buffer29[18],buffer30[18],buffer31[18],buffer32[18],buffer33[18],buffer34[18],buffer35[18],buffer36[18],buffer37[18],buffer38[18],buffer39[18],buffer40[18],buffer41[18],buffer42[18],buffer43[18],buffer44[18],buffer45[18],buffer46[18],buffer47[18],buffer48[18],buffer49[18],buffer50[18],buffer51[18],buffer52[18],buffer53[18],buffer54[18],buffer55[18],buffer56[18],buffer57[18],buffer58[18],buffer59[18],buffer60[18],buffer61[18],buffer62[18],buffer63[18];
    byte size = sizeof(buffer0);

    
void setup() {
 
    card_A();
    card_B();

}

void loop(){
  
}
void card_A() {
  Serial.begin(9600); // Initialize serial communications with the PC
    while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card

    // Prepare the key (used both as key A and as key B)
    // using FFFFFFFFFFFFh which is the default at chip delivery from the factory
    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

    //Serial.println(F("Scan a MIFARE Classic PICC to demonstrate read and write."));
    Serial.print(F("Using key (for A and B):"));
    dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);
    Serial.println();
    
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent())
      return;

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())
      return;
    
    // Show some details of the PICC (that is: the tag/card)
    Serial.print(F("Card UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();
    Serial.print(F("PICC type: "));
    byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));

    // Check for compatibility
    if (    piccType != MFRC522::PICC_TYPE_MIFARE_MINI
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_1K
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        Serial.println(F("This sample only works with MIFARE Classic cards."));
        return;
    }


    Serial.println("Code reading and writing started");

    read_sector_0(buffer1, buffer2);
    read_sector(1, buffer4, buffer5, buffer6);
    read_sector(2, buffer8, buffer9, buffer10);
    read_sector(3, buffer12, buffer13, buffer14);
    read_sector(4, buffer16, buffer17, buffer18);
    read_sector(5, buffer20, buffer21, buffer22);
    read_sector(6, buffer24, buffer25, buffer26);
    read_sector(7, buffer28, buffer29, buffer30);
    read_sector(8, buffer32, buffer33, buffer34);
    read_sector(9, buffer36, buffer37, buffer38);
    read_sector(10, buffer40, buffer41, buffer42);
    read_sector(11, buffer44, buffer45, buffer46);
    read_sector(12, buffer48, buffer49, buffer50);
    read_sector(13, buffer52, buffer53, buffer54);
    read_sector(14, buffer56, buffer57, buffer58);
    read_sector(15, buffer60, buffer61, buffer62);


    Serial.println();Serial.println();
    Serial.println("Put the card to be cloned in 10 seconds .... ");
    Serial.println();Serial.println();
    Serial.println(F("BEWARE: Data will be written to the PICC !!! "));
    Serial.println();Serial.println();
    delay(10000);
}

void card_B() {
  Serial.begin(9600); // Initialize serial communications with the PC
    while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card

    // Prepare the key (used both as key A and as key B)
    // using FFFFFFFFFFFFh which is the default at chip delivery from the factory
    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

    //Serial.println(F("Scan a MIFARE Classic PICC to demonstrate read and write."));
    Serial.println();
    Serial.print(F("Using key (for A and B):"));
    dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);
    Serial.println();
    
    Serial.println();
    
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent())
      return;

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())
      return;
        

    // Show some details of the PICC (that is: the tag/card)
    Serial.print(F("Card UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();
    Serial.print(F("PICC type: "));
    byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));

    // Check for compatibility
    if (    piccType != MFRC522::PICC_TYPE_MIFARE_MINI
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_1K
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        Serial.println(F("This sample only works with MIFARE Classic cards."));
        return;
    }


    write_sector_0(buffer1, buffer2);
    write_sector(1, buffer4, buffer5, buffer6);
    write_sector(2, buffer8, buffer9, buffer10);
    write_sector(3, buffer12, buffer13, buffer14);
    write_sector(4, buffer16, buffer17, buffer18);
    write_sector(5, buffer20, buffer21, buffer22);
    write_sector(6, buffer24, buffer25, buffer26);
    write_sector(7, buffer28, buffer29, buffer30);
    write_sector(8, buffer32, buffer33, buffer34);
    write_sector(9, buffer36, buffer37, buffer38);
    write_sector(10, buffer40, buffer41, buffer42);
    write_sector(11, buffer44, buffer45, buffer46);
    write_sector(12, buffer48, buffer49, buffer50);
    write_sector(13, buffer52, buffer53, buffer54);
    write_sector(14, buffer56, buffer57, buffer58);
    write_sector(15, buffer60, buffer61, buffer62);

    Serial.println();Serial.println();
    Serial.println("Writing sectors done !!!");
}

void read_sector_0(byte *buffer1, byte *buffer2)
{
    // Authenticate using key A
    //Serial.println(F("Authenticating using key A..."));
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 3, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }
     Serial.print(F("Copying data from sector ")); Serial.print("0");
    Serial.println(F(" ..."));
    status = mfrc522.MIFARE_Read(0, buffer0, &size);
    status = mfrc522.MIFARE_Read(1, buffer1, &size);
    status = mfrc522.MIFARE_Read(2, buffer2, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Read() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
    }

}

void read_sector(byte sector, byte *buffer0, byte *buffer1, byte *buffer2)
{

  // Authenticate using key A
    //Serial.println(F("Authenticating using key A..."));
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, sector*4+3, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }
    
    Serial.print(F("Copying data from sector ")); Serial.print(sector);
    Serial.println(F(" ..."));
    status = mfrc522.MIFARE_Read(sector*4, buffer0, &size);
    status = mfrc522.MIFARE_Read(sector*4+1, buffer1, &size);
    status = mfrc522.MIFARE_Read(sector*4+2, buffer2, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Read() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
}


void write_sector_0(byte *buffer1, byte *buffer2)
{
    Serial.println();
          // Authenticate using key A
    //Serial.println(F("Authenticating using key A..."));
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 3, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }
    Serial.print("Writing data into sector "); Serial.print("0");
    //trying to write the entire block 0
    //status = mfrc522.MIFARE_Write(0, buffer0, 16);
    status = mfrc522.MIFARE_Write(1, buffer1, 16);
    status = mfrc522.MIFARE_Write(2, buffer2, 16);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Write() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
    }

}


void write_sector(byte sector, byte *buffer0, byte *buffer1, byte *buffer2) {
   
    Serial.println();
          // Authenticate using key A
    //Serial.println(F("Authenticating using key A..."));
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, sector*4+3, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }
    Serial.print("Writing data into sector "); Serial.print(sector);
    status = mfrc522.MIFARE_Write(sector*4, buffer0, 16);
    status = mfrc522.MIFARE_Write(sector*4+1, buffer1, 16);
    status = mfrc522.MIFARE_Write(sector*4+2, buffer2, 16);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Write() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
    }

}

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}
