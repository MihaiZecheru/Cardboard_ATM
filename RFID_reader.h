// HEADER => RFID Reader Class

#include "User.h"

#ifndef RFID_READER_H
#define RFID_READER_H

class RFIDreader : public MFRC522
{
    private:
      bool READER_AVAILABLE;
      uint32_t PAST_RFID;
      byte tick = 0;
      bool previous_ticks[2];

      inline bool IsNewCard(const uint32_t ID)
      {
        const bool isNew = this->PAST_RFID != ID;
        PAST_RFID = ID;
        return isNew;
      }

      inline const uint32_t strtoul(String str)
      {
        str.replace('a', '1');
        str.replace('b', '2');
        str.replace('c', '3');
        str.replace('d', '4');
        str.replace('e', '5');
        str.replace('f', '6');
        return str.toInt();
      }
      
    public:
      /* SDA pin = 53; RESET pin = 2 */
      RFIDreader(const uint8_t SDA_PIN, const uint8_t RST_PIN) : MFRC522(SDA_PIN, RST_PIN)
      {
        this->READER_AVAILABLE = true;
        this->PAST_RFID = 0;
      }

      inline const bool CheckForNewCard(void)
      {
        tick++;
        if (previous_ticks[0]) tick ++; // make sure the position of the ticks is correct
        if (tick > 1) tick = 0;
        
        if(!this->PICC_IsNewCardPresent())
        {
          previous_ticks[tick] = false;
        }
        else
        {
          previous_ticks[tick] = true;
        }

        if (!this->PICC_ReadCardSerial())
          return false;
          

        String card_content = "";

        for (byte i = 0; i < this->uid.size; i++) 
        {
           card_content.concat(this->uid.uidByte[i] < 0x10 ? "0" : "");
           card_content.concat(String(this->uid.uidByte[i], HEX));
        }

        return this->IsNewCard(
          this->strtoul(card_content)
        );
      }

      const bool exists()
      {
        for (int i = 0; i < USERS_NUM; i++)
        {
          if (this->PAST_RFID == RFIDS[i]) return true;
        }

        return false;
      }

      User* GetUser()
      {
        return FindUser(this->PAST_RFID);
      }

      const bool CardRemoved()
      {
        return !this->previous_ticks[1];
      }

      void AllowSameUser()
      {
        PAST_RFID = 0;
      }
};

#endif
