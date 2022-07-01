// HEADER => 7-Segment Display Class

#ifndef SEVEN_SEGMENT_DISPLAY_H
#define SEVEN_SEGMENT_DISPLAY_H

class SevenSegmentDisplay
{
  private:
    uint8_t pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDot, D1, D2, D3, D4;

    void TurnOn(const uint8_t digit)
    {
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH);
       
      if (digit == 1)
        digitalWrite(D1, LOW);
      else if (digit == 2)
        digitalWrite(D2, LOW);
      else if (digit == 3)
        digitalWrite(D3, LOW);
      else
        digitalWrite(D4, LOW);
    }

    /*
                A
               ---
            F |   | B
              | G |
               ---
            E |   | C
              |   |
               ---
                D
    */

    void _setNumber(const uint8_t x)
    { 
      switch (x)
      {
        case 0:
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, HIGH);
          digitalWrite(pinE, HIGH);
          digitalWrite(pinF, HIGH);
          digitalWrite(pinG, LOW);
          break;
    
        case 1:
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          break;
      
        case 2:
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, HIGH);
          digitalWrite(pinE, HIGH);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, HIGH);
          break;
          
        case 3:
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, HIGH);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, HIGH);
          break;
    
        case 4:
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, HIGH);
          digitalWrite(pinG, HIGH);
          break;
      
        case 5:
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, HIGH);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, HIGH);
          digitalWrite(pinG, HIGH);
          break;
      
        case 6:
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, HIGH);
          digitalWrite(pinE, HIGH);
          digitalWrite(pinF, HIGH);
          digitalWrite(pinG, HIGH);
          break;     
      
        case 7:
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          break;
      
        case 8:
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, HIGH);
          digitalWrite(pinE, HIGH);
          digitalWrite(pinF, HIGH);
          digitalWrite(pinG, HIGH);
          break;
    
        case 9:
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, HIGH);
          digitalWrite(pinG, HIGH);
          break;
      }
    }
    
  public:
    SevenSegmentDisplay
      (
        const uint8_t a, const uint8_t b, const uint8_t c, const uint8_t d, const uint8_t e,
        const uint8_t f, const uint8_t g, const uint8_t dot, const uint8_t common1, const uint8_t common2,
        const uint8_t common3, const uint8_t common4
      ) :
    pinA(a), pinB(b), pinC(c), pinD(d), pinE(e), pinF(f), pinG(g), pinDot(dot),
    D1(common1), D2(common2), D3(common3), D4(common4)
    {
      pinMode(pinA, OUTPUT);
      pinMode(pinB, OUTPUT);
      pinMode(pinC, OUTPUT);
      pinMode(pinD, OUTPUT);
      pinMode(pinE, OUTPUT);
      pinMode(pinF, OUTPUT);
      pinMode(pinG, OUTPUT);
      pinMode(pinDot, OUTPUT);
      pinMode(D1, OUTPUT);
      pinMode(D2, OUTPUT);
      pinMode(D3, OUTPUT);
      pinMode(D4, OUTPUT);
      
      this->off();
    }

    inline void setNumber(uint16_t x)
    {
      // it's assumed that only 4 digits are given
      uint8_t digits[4];
      
      digits[0] = x / 1000;
      x %= 1000;

      digits[1] = x / 100;
      x %= 100;

      digits[2] = x / 10;
      digits[3] = x % 10;

      if (digits[0] != 0)
      {
        this->TurnOn(1);
        this->_setNumber(*digits);
      }

      for (uint8_t i = 1; i < 4; i++)
      {
        this->TurnOn(i + 1);
        digitalWrite(pinDot, i == 1);
        this->_setNumber(digits[i]);
        delay(5);
      }
    }

    void off()
    {
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH);
      digitalWrite(pinDot, LOW);
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
    }
};

#endif
