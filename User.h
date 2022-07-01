// HEADER => User Struct

#include "Dispenser.h"

//#include <EEPROM.h>
  
#ifndef USER_H
#define USER_H

const uint8_t USERS_NUM = 10;
const String USERNAMES[USERS_NUM] = { "Chris", "Daria", "Tudor", "Ilinca", "Emma", "Kevin", "Andie", "Bianca", "Vlad", "Lia" };
const uint32_t RFIDS[USERS_NUM] = { 43314803, 60212316, 01102216, 23452316, 76472316, 65212316, 35832116, 51362216, 99922216, 32522216 };

struct User
{
  uint32_t id;                        // user rfid
  String name;                        // username
  double balance;                     // user balance
  uint8_t mem_loc;                    // position in EEPROM
  
  uint16_t tokens_purchased;          // STAT: amount of tokens purchased
  uint16_t tokens_traded;             // STAT: amount of tokens traded
  
  double highest_balance;             // STAT: greatest balance achieved
  double lowest_balance;              // STAT: weakest balanace acheived
  
  uint8_t best_leaderboard_position;  // STAT: highest position on leaderboard
  uint8_t worst_leaderboard_position; // STAT: lowest position on leaderboard

  uint8_t most_tokens_bought_at_once; // STAT: most tokens bought in one go
  uint8_t most_tokens_traded_at_once; // STAT: most tokens traded in one go

  void BalanceAdd(const double x)
  {
    this->balance += x;
    this->UpdateUserDataInMemory();

    // check user stats for possible update
    if (this->balance > this->highest_balance)
      this->highest_balance = this->balance;
  }

  bool BalanceSub(const double x)
  {
    if (this->balance < x)
        return false; // fail
      
      this->balance -= x;
      this->UpdateUserDataInMemory();

      // check user stats for possible update
      if (this->balance < this->lowest_balance)
        this->lowest_balance = this->balance;
        
      return true;
  }

  void UpdateUserDataInMemory()
  {
//     // balance
//    EEPROM.put(this->mem_loc * sizeof(double), this->balance);
//
//    // tokens_purchased
//    EEPROM.put(
//      USERS_NUM *
//      sizeof(double) +
//      (this->mem_loc * sizeof(uint16_t)), 
//      this->tokens_purchased
//    );
//
//    // tokens_traded
//    EEPROM.put(
//      USERS_NUM * 
//      (sizeof(double) + sizeof(uint16_t)) + 
//      (this->mem_loc * sizeof(uint16_t)),
//      this->tokens_traded
//    );
//
//    // highest_balanace
//    EEPROM.put(
//      USERS_NUM *
//      (sizeof(double) + (sizeof(uint16_t) * 2)) +
//      (this->mem_loc * sizeof(double)),
//      this->highest_balance
//    );
//
//    // lowest_balance
//    EEPROM.put(
//      USERS_NUM *
//      ((sizeof(double) * 2) + (sizeof(uint16_t) * 2)) +
//      (this->mem_loc * sizeof(double)),
//      this->lowest_balance
//    );
  }
  
  inline void PurchaseToken()
  {
    DISPENSER.DispenseToken();
    this->tokens_purchased++;
    return true;
  }

  inline void TradeInToken()
  {
    this->BalanceAdd(TOKEN.VALUE);
    this->tokens_traded++; // TODO: when you make the trade-in system, keep track of how many tokens the user trades while his card is in the machine. then, once he pulls the card out,
                           //compare it to user.most_tokens_traded_at_once, and if that amount is greater than user.most_tokens_traded_at_once, replace user.most_tokens_traded_at_once with that amount
  }
};

User USERS[USERS_NUM];
User* CURRENT_USER;

void InitializeUsers()
{
  // note: starting balance is 150.0
  for (int i = 0; i < USERS_NUM; i++)
  {
    const double bal = 150.00f, highest_balance = 150.00f, lowest_balance = 150.00f;
    const uint16_t tokens_purchased = 0, tokens_traded = 0;
    const uint8_t best_leaderboard_position = 10, worst_leaderboard_position = 1,
    most_tokens_bought_at_once = 0, most_tokens_traded_at_once = 0;
    
    /* get values from memory */
    
//    double bal, highest_balance, lowest_balance;
//    uint16_t tokens_purchased, tokens_traded;

//     // balance
//    EEPROM.put(i * sizeof(double), bal);
//
//    // tokens_purchased
//    EEPROM.put(
//      USERS_NUM *
//      sizeof(double) +
//      (i * sizeof(uint16_t)), 
//      tokens_purchased
//    );
//
//    // tokens_traded
//    EEPROM.put(
//      USERS_NUM * 
//      (sizeof(double) + sizeof(uint16_t)) + 
//      (i * sizeof(uint16_t)),
//      tokens_traded
//    );
//
//    // highest_balanace
//    EEPROM.put(
//      USERS_NUM *
//      (sizeof(double) + (sizeof(uint16_t) * 2)) +
//      (i * sizeof(double)),
//      highest_balance
//    );
//
//    // lowest_balance
//    EEPROM.put(
//      USERS_NUM *
//      ((sizeof(double) * 2) + (sizeof(uint16_t) * 2)) +
//      (i * sizeof(double)),
//      lowest_balance
//    );
//
    /* initialize the user */

    User user;
    
    user.id = RFIDS[i];
    user.name = USERNAMES[i];
    user.balance = bal;
    user.mem_loc = i;

    user.tokens_purchased = tokens_purchased;
    user.tokens_traded = tokens_traded;
    user.highest_balance = highest_balance;
    user.lowest_balance = lowest_balance;

    user.best_leaderboard_position = best_leaderboard_position;
    user.worst_leaderboard_position = worst_leaderboard_position;
    
    USERS[i] = user;
  }
}

void RESET_USER_DATABASE()
{ 
//  // clear EEPROM
//  for (int i = 0; i < EEPROM.length(); i++)
//    EEPROM.put(i, 0);
//  
//  for (int i = 0; i < USERS_NUM; i++)
//  {
//    double bal = 150.00f;
//    double highest_balance = 150.00f;
//    double lowest_balance = 150.00f;
//    uint16_t tokens_purchased = 0;
//    uint16_t tokens_traded = 0;
//
//    // balance
//    EEPROM.put(i * sizeof(double), bal);
//
//    // tokens_purchased
//    EEPROM.put(
//      USERS_NUM *
//      sizeof(double) +
//      (i * sizeof(uint16_t)), 
//      tokens_purchased
//    );
//
//    // tokens_traded
//    EEPROM.put(
//      USERS_NUM * 
//      (sizeof(double) + sizeof(uint16_t)) + 
//      (i * sizeof(uint16_t)),
//      tokens_traded
//    );
//
//    // highest_balanace
//    EEPROM.put(
//      USERS_NUM *
//      (sizeof(double) + (sizeof(uint16_t) * 2)) +
//      (i * sizeof(double)),
//      highest_balance
//    );
//
//    // lowest_balance
//    EEPROM.put(
//      USERS_NUM *
//      ((sizeof(double) * 2) + (sizeof(uint16_t) * 2)) +
//      (i * sizeof(double)),
//      lowest_balance
//    );
//  }
}

User* FindUser(const uint32_t ID)
{
  User* user_ptr;
  
  for (int i = 0; i < USERS_NUM; i++)
  {
    if (USERS[i].id == ID) user_ptr = USERS + i; // ptr
  }

  return user_ptr;
}

const uint8_t sort(const User** a, const User** b)
{
  return (*b)->balance - (*a)->balance;
}

inline void GetUsersLeaderboard(User** users_array_ptr)
{
  User* user_leaderboard[USERS_NUM];
  user_leaderboard[0] = &(USERS[0]);
  
  for (int i = 1; i < USERS_NUM; i++)
    user_leaderboard[i] = &(USERS[i]);

  qsort(user_leaderboard, USERS_NUM, sizeof(User*), sort);
  
  for (int i = 0; i < USERS_NUM; i++)
    users_array_ptr[i] = user_leaderboard[i];
}

#endif
