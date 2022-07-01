// ---------------------------------------------------------------------- Libs

#include <SPI.h>
#include <MFRC522.h>

// ---------------------------------------------------------------------- Token

#include "Token.h"
Token TOKEN(4.25);

// ---------------------------------------------------------------------- LEDs

#include "LED.h"
LED GreenLED(46);
LED RedLED(47);
bool PREVENT_GLED_SHOW = false;

// ---------------------------------------------------------------------- Laser

#include "Laser.h"
Laser laser(3, 13);

// ---------------------------------------------------------------------- Dispenser

#include "Dispenser.h"
Dispenser DISPENSER(9, 10, 11, 12);

// ---------------------------------------------------------------------- User

#include "User.h"

// ---------------------------------------------------------------------- RFID

#include "RFID_reader.h"
RFID_reader RFID(53, 2);
bool CARD_ALREADY_REMOVED = true;

// ---------------------------------------------------------------------- LCD

#include "LiquidCrystalDisplay.h"
LiquidCrystalDisplay20x4 lcdf;

// ---------------------------------------------------------------------- Keypad

#include "CustomKeypad.h"
CustomKeypad kp;

// ---------------------------------------------------------------------- 7-seg

#include "7seg.h"
SevenSegmentDisplay sevseg(27, 29, 5, 30, 26, 28, 34, 33, 48, 32, 49, 31);

void Token::DisplayValue()
{
  uint8_t loops = 133; // 2000 (ms) / 15 (ms per call) = 133
  while (loops--)
    sevseg.setNumber(TOKEN.VALUE * 100);
  sevseg.off();
}

// ---------------------------------------------------------------------- Main

void setup()
{
//  RESET_USER_DATABASE();

  lcdf.init();

  InitializeUsers();
  SPI.begin(); 
  RFID.PCD_Init();

  lcdf.finish_setup();
  Serial.begin(9600);     
}

void loop()
{
  /* check for coin deposit */
  if (CURRENT_USER != nullptr && laser.Interrupted())
  {
    // update balance
    CURRENT_USER->TradeInToken();

    // show the new balance if the user is on a screen where the balance was being displayed
    if (lcdf.GetScreen() == 2 || lcdf.GetScreen() == 5)
    {
      lcdf.setCursor(10, 1 + (lcdf.GetScreen() == 5));
      lcdf.print(String(CURRENT_USER->balance));
    }
  }

  kp.HandleKeypress();
  
  if (RFID.CheckForNewCard())
  {
    if (!RFID.exists())
    {
      lcdf.screen10();
      GreenLED.Hide();
      RedLED.Show();
      delay(3500);
      RedLED.Hide();
      lcdf.screen1();
      return;
    }

    CURRENT_USER = RFID.GetUser();
    lcdf.screen2();
    CARD_ALREADY_REMOVED = false;
    PREVENT_GLED_SHOW = false;
  }

  if (RFID.CardRemoved())
  {
    if (!CARD_ALREADY_REMOVED)
    {
      GreenLED.Hide();
      RedLED.Hide();
      
      lcdf.screen1();
      RFID.AllowSameUser();
      kp.Reset_USER_INPUT();
      
      CURRENT_USER = nullptr;
      CARD_ALREADY_REMOVED = true;
    }
  }
  else
  {
    if (RFID.exists() && !PREVENT_GLED_SHOW)
      GreenLED.Show();
  }
  
  return;
}
