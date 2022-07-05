// HEADER => Laser Class

#ifndef LASER_H
#define LASER_H

class Laser
{
  private:
    uint8_t detectPin;
    uint8_t signalPin;

  public:
    Laser(const uint8_t detect_pin, const uint8_t signal_pin) : detectPin(detect_pin), signalPin(signal_pin)
    {
      pinMode(detectPin, INPUT);
      pinMode(signalPin, OUTPUT);

      // activate laser
      digitalWrite(signalPin, HIGH);
    }

    const bool Interrupted()
    {
      
      const bool interrupted = digitalRead(detectPin) == LOW;

      if (interrupted)
      {
        // wait until token is gone to prevent bug where the token would be scanned twice
        while (digitalRead(detectPin) == LOW)
          delay(5);
      }

      return interrupted;
    }
};

#endif
