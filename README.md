# RFID_Cloner
Clone a high frequency card -- Mifare 1Kb cards (13.56 Mhz)

Initial steps required before the cloning process is initiated:

-Download the Arduino IDE \n
-Connect the Arduino micro-controller to the module RC522 using jumper wires (the connection data is mentioned at the initial lines of the code).\n
-Connect the arduino to the machine.
-Import the library MFRC522.h to the arduino IDE. (https://github.com/miguelbalboa/rfid/blob/master/MFRC522.h)

Steps required to clone to the card:
-Let's say that card A is the primary card and a clone has to be made to the Card B.
-Open the code in the arduino IDe and switch on the "Serial Monitor".
-Place the card A onto the RC522 module and then upload the clone_except_block0.ino to the arduino micro-controller.
-Once the values from Card A has been copied the user will be prompted on the "Serial Monitor" console, to place card B onto the RC522 module.
-It will start writing the values of Card A into Card B sector by sector.
-Once the cloning is done the values of block0 is printed in the "Serial Monitor".
-User can then use the "ChangeUID" code which comes bundled in with the MFRC522.h library to change the block0.

NOTE-
The code clone_except_block0.ino doesn't clone block0, it clones the other 1-63 blocks of data. Block 0 is the most important block for a card and it's a more efficient approach to write it separately. If a user happens to move the card and if that happens at the time when the code is trying to write into the block 0, an error at that moment might leave the card useless.
