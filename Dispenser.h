// HEADER => Dispenser Class

#ifndef DISPENSER_H
#define DISPENSER_H

class Dispenser
{
  private:
    uint8_t pins[4];
    uint8_t motor_position;
    uint8_t motor_delay; // lowest possible delay is 2
    uint16_t dispense_steps;

    void SendByte(const uint8_t a, const uint8_t b, const uint8_t c, const uint8_t d)
    {
      digitalWrite(this->pins[0], a);
      digitalWrite(this->pins[1], b);
      digitalWrite(this->pins[2], c);
      digitalWrite(this->pins[3], d);
    }

    void TakeOneStep(void)
    {
      switch (this->motor_position)
      {
        case 0:
          this->SendByte(0, 0, 0, 1);
          break;
        case 1:
          this->SendByte(0, 0, 1, 0);
          break;
        case 2:
          this->SendByte(0, 1, 0, 0);
          break;
        case 3:
          this->SendByte(1, 0, 0, 0);
          break;
      }
    
      this->motor_position++;
      if (this->motor_position > 3) this->motor_position = 0;
    }
    
  public:
    Dispenser(const uint8_t a, const uint8_t b, const uint8_t c, const uint8_t d)
    {
      this->pins[0] = a;
      this->pins[1] = b;
      this->pins[2] = c;
      this->pins[3] = d;

      this->motor_position = 0;
      this->motor_delay = 4;
      this->dispense_steps = 0;

      /* initialize motor */
      for (int i = 0 ; i < 4; i++)
        pinMode(this->pins[i], OUTPUT);
    }

    void DispenseToken(void)
    {
      while (this->dispense_steps < 1000)
      {
        this->TakeOneStep();
        delay(this->motor_delay);
    
        this->dispense_steps++;
        
        if (this->dispense_steps > 100) 
          this->motor_delay = 2;
      }
      
      this->motor_delay = 4;
      this->dispense_steps = 0;
    }
};


#endif
