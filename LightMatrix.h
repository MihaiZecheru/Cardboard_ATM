// HEADER => LED Matrix Class

#ifndef MATRIX_H
#define MATRIX_H

const uint8_t SMILE[8]                           = {0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C};
const uint8_t NEUTRAL[8]                         = {0x3C, 0x42, 0xA5, 0x81, 0xBD, 0x81, 0x42, 0x3C};
const uint8_t SEMI_NEUTRAL[8]                    = {0x3C, 0x42, 0xA5, 0x81, 0x81, 0x99, 0x42, 0x3C};

const uint8_t SEMI_NEUTRAL_LOOK_SLIGHTLY_DOWN[8] = {0x3C, 0x42, 0x81, 0x91, 0x85, 0x99, 0x42, 0x3C};
const uint8_t SEMI_NEUTRAL_LOOK_SLIGHTLY_UP[8]   = {0x3C, 0x42, 0x85, 0x91, 0x81, 0x99, 0x42, 0x3C};
const uint8_t ARROW[8]                           = {0x18, 0x3C, 0x7E, 0xDB, 0x99, 0x18, 0x18, 0x18};
const uint8_t CLEAR[8]                           = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t SMILE_BLINK[8]                     = {0x3C, 0x42, 0x81, 0x81, 0xA5, 0x99, 0x42, 0x3C};
const uint8_t NEUTRAL_BLINK[8]                   = {0x3C, 0x42, 0x81, 0x81, 0xBD, 0x81, 0x42, 0x3C};
const uint8_t SEMI_NEUTRAL_BLINK[8]              = {0x3C, 0x42, 0x81, 0x81, 0x81, 0x99, 0x42, 0x3C};

#include <LedControl.h>

class Matrix : public LedControl
{
  private:
    static const uint8_t animation_delay = 75;
    static const uint8_t blink_delay = 200;
    uint8_t MOUTH_STATE;
    uint8_t DIN;
    uint8_t CS;
    uint8_t CLK;

    void printByte(const uint8_t characters[8])
    {
      for (int i = 0; i < 8; i++)
        this->setRow(0, i, characters[i]);
    }

    void adelay()
    {
      delay(Matrix::animation_delay);
    }

    void bdelay()
    {
      delay(Matrix::blink_delay);
    }

  public:
    bool called = false;
  
    Matrix(const uint8_t din, const uint8_t cs, const uint8_t clk) : DIN(din), CS(cs), CLK(clk), LedControl(din, clk, cs)
    {
      this->shutdown(0, false);       //The MAX72XX is in power-saving mode on startup
      this->setIntensity(0, 15);      // Set the brightness to maximum value
      this->clearDisplay(0);         // and clear the display     
      this->neutral();
    }

    void smile()
    {
      this->MOUTH_STATE = 1;
      this->printByte(SMILE);
    }

    void neutral()
    {
      this->MOUTH_STATE = 2;
      this->printByte(NEUTRAL);
    }

    void semi_neutral()
    {
      this->MOUTH_STATE = 3;
      this->printByte(SEMI_NEUTRAL);
    }

    void arrow()
    {
      this->MOUTH_STATE = 4;
      this->printByte(ARROW);
    }

    void credit_card_removed_animation()
    {
      if (this->called) return;

      this->called = true;
      this->semi_neutral();
      this->adelay();
      this->printByte(SEMI_NEUTRAL_LOOK_SLIGHTLY_DOWN);
      delay(1500);
      this->semi_neutral();
      this->adelay();
      this->neutral();
    }

    void look_at_7seg()
    {
      this->MOUTH_STATE = 2;
      this->semi_neutral();
      this->adelay();
      this->printByte(SEMI_NEUTRAL_LOOK_SLIGHTLY_UP);
      this->MOUTH_STATE = 5;
    }

    void blink()
    {
      switch (this->MOUTH_STATE)
      {
        case 1:
          this->printByte(SMILE_BLINK);
          this->bdelay();
          this->smile();
          break;

        case 2:
          this->printByte(NEUTRAL_BLINK);
          this->bdelay();
          this->neutral();
          break;

        case 3:
          this->printByte(SEMI_NEUTRAL_BLINK);
          this->bdelay();
          this->semi_neutral();
          break;

        case 4:
          this->printByte(CLEAR);
          this->bdelay();
          this->arrow();
          break;

        case 5:
          this->printByte(SEMI_NEUTRAL_BLINK);
          this->bdelay();
          this->printByte(SEMI_NEUTRAL_LOOK_SLIGHTLY_UP);
          break;
      }
    }

    void sell_animation()
    {
      this->arrow();
      
      for (int i = 0; i < 3; i++)
      {
        this->bdelay();
        this->blink();
      }
    }
};


#endif
