// HEADER => Keypad Class

#include <Keypad.h>

#ifndef CUSTOM_KEYPAD_H
#define CUSTOM_KEYPAD_H

const byte ROWS = 4; 
const byte COLS = 4; 

const byte rowPins[ROWS] = { 43, 42, 41, 40 };
const byte colPins[COLS] = { 39, 38, 37, 36 };

const char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad kp_(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

class CustomKeypad
{
  private:
    String USER_INPUT = "";

    void Append_USER_INPUT(const char key)
    {
      if (this->USER_INPUT.length() < 6)
        this->USER_INPUT += key;
    }
    
    void PrintKey(const char key)
    {
      Serial.println(lcdf.GetScreen());
      switch (lcdf.GetScreen())
      {
        case 4:
          this->Append_USER_INPUT(key);
          lcdf.print(key);
          matrix.neutral();
          break;
      }
    }

    void DeleteKey()
    {
      this->USER_INPUT = this->USER_INPUT.substring(0, this->USER_INPUT.length() - 1);

      switch(lcdf.GetScreen())
      {
        case 4:
          lcdf.setCursor(0, 3);
          lcdf.print("                    "); // clear line
          lcdf.setCursor(0, 3);
          lcdf.print("Enter Amount: " + this->USER_INPUT);
          break;
      }
    }

    void Enter()
    {
      matrix.blink();
        
      switch (lcdf.GetScreen())
      {
        case 2:
          matrix.called = false;
          lcdf.screen3();
          break;

        case 4:
          if (USER_INPUT == "") return;

          matrix.smile();
          double amount = USER_INPUT.toDouble();

          if (!CURRENT_USER->BalanceSub(amount * TOKEN.VALUE))
          {
            lcdf.screen9(amount);
            Reset_USER_INPUT();
            return;
          }

          // update stat
          if (amount > CURRENT_USER->most_tokens_bought_at_once)
            CURRENT_USER->most_tokens_bought_at_once = amount;
          
          while(amount--)
          {
            lcdf.screen8(amount + 1);
            CURRENT_USER->PurchaseToken();
          }

          lcdf.screen8(0);
          Reset_USER_INPUT();
          break;
      }
    }

    void GoBack()
    {
      switch (lcdf.GetScreen())
      {
        case 2:
          // todo: show "remove card" and blink the led red
          break;

        case 3:
          lcdf.screen2();
          break;

        case 4:
          lcdf.screen3();
          break;

        case 5:
          lcdf.screen3();
          break;

        case 6:
          lcdf.screen3();
          break;

        case 7:
          lcdf.screen3();
          break;

        case 9:
          lcdf.screen4();
          break;
      }
    }

    void OptionsMenu(const char option)
    {
      switch (option)
      {
        case 'A':
          matrix.smile();
          lcdf.screen4();
          delay(750);
          matrix.blink();
          break;

        case 'B':
          lcdf.screen5();
          matrix.sell_animation();
          break;

        case 'C':
          lcdf.screen6();
          matrix.look_at_7seg();
          break;

        case 'D':
          lcdf.screen7();
          matrix.look_at_7seg();
          break;
      }
    }

    void LetterPressed(const char letter)
    {
      if (letter == 'C' && lcdf.GetScreen() != 3)
      {
        TOKEN.DisplayValue();
        return;
      }

      switch(lcdf.GetScreen())
      {
        case 3:
          OptionsMenu(letter);
          break;

        case 4:
          if (letter == 'D')
            DeleteKey();
          break;

        case 6:
        lcdf.LeaderboardOrStatsScroll(false, letter == 'A' ? 0 : letter == 'B' ? 1 : -1);
        break;

        case 7:
          lcdf.LeaderboardOrStatsScroll(true, letter == 'A' ? 0 : letter == 'B' ? 1 : -1);
          break;
      }
    }
    
  public:

    void Reset_USER_INPUT()
    {
      USER_INPUT = "";
    }
    
    inline void HandleKeypress()
    {
      char keypress = kp_.getKey();

      if (keypress)
      {
        switch (keypress)
        {
          case '1': case '2':
          case '3': case '4':
          case '5': case '6':
          case '7': case '8':
          case '9': case '0':
            this->PrintKey(keypress);
            break;

          case 'A':
          case 'B':
          case 'C':
          case 'D':
            this->LetterPressed(keypress);
            break;

          case '*':
            this->GoBack();
            break;

          case '#':
            this->Enter();
            break;
        }
      }
    }
};

#endif
