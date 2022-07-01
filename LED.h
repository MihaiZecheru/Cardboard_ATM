// HEADER => LED Class

#ifndef LED_H
#define LED_H

class LED
{
  private:
    uint8_t PIN;

  public:
    LED(const uint8_t pin)
    {
      PIN = pin;
    }

    void Show()
    {
      digitalWrite(PIN, HIGH);
    }

    void Hide()
    {
      digitalWrite(PIN, LOW);
    }
};

#endif
