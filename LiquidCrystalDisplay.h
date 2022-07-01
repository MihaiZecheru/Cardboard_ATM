// HEADER => LiquidCrystalDisplay Class

#include <LiquidCrystal_I2C.h>

#ifndef LIQUID_CRYSTAL_DISPLAY_H
#define LIQUID_CRYSTAL_DISPLAY_H

LiquidCrystal_I2C _lcdf(0x27, 20, 4);

class LiquidCrystalDisplay20x4
{
  private:
    uint8_t SCREEN;
    uint8_t CURRENT_ROW = 0;
    const uint8_t COLS = 20;
    const uint8_t ROWS = 4;

    static const uint8_t SIZEOF_LEADERBOARD = USERS_NUM + 6; // 5 extra lines
    uint8_t CURRENT_LEADERBOARD_LINES;
    String TOTAL_LEADERBOARD_LINES[LiquidCrystalDisplay20x4::SIZEOF_LEADERBOARD];    

    static const uint8_t SIZEOF_STATS_DISPLAY = 6 + 6; // 6 (extra lines) + 6 (amount of stats in a user)
    uint8_t CURRENT_STATS_DISPLAY_LINES;
    String TOTAL_STATS_DISPLAY_LINES[LiquidCrystalDisplay20x4::SIZEOF_STATS_DISPLAY];

    void println(const String text)
    {
      this->print(text);
      this->CURRENT_ROW = this->CURRENT_ROW == 3 ? 0 : this->CURRENT_ROW + 1;
      _lcdf.setCursor(0, this->CURRENT_ROW);
    }

    void println()
    {
      this->CURRENT_ROW = this->CURRENT_ROW == 3 ? 0 : this->CURRENT_ROW + 1;
      _lcdf.setCursor(0, this->CURRENT_ROW);
    }

    void home()
    {
      this->CURRENT_ROW = 0;
    }

    void nextLine()
    {
      this->println();
    }
    
  public:
    void print(const String text)
    {
      _lcdf.print(text);
    }

    void print(const char text)
    {
      _lcdf.print(text);
    }

    void setCursor(const uint8_t col, const uint8_t row)
    {
      this->CURRENT_ROW = row;
      _lcdf.setCursor(col, row);
    }
    
    void init()
    {
      _lcdf.begin();
      _lcdf.backlight();
      this->println("Setting Up...");
      _lcdf.noCursor();
      _lcdf.noBlink();
      _lcdf.noAutoscroll();
    }

    void finish_setup()
    {
//      delay(2000); todo: uncomment this
      this->print("Done!");
//      delay(1000); todo: uncomment this
      
      _lcdf.clear();
      this->screen1();
    }

    void LeaderboardOrStatsScroll(const bool isForLeaderboard, const int8_t action)
    {
      if (isForLeaderboard)
      {
        if (action && this->CURRENT_LEADERBOARD_LINES <= (SIZEOF_LEADERBOARD - ROWS - 2)) // scroll down
          this->CURRENT_LEADERBOARD_LINES += 2;
        else if (!action && this->CURRENT_LEADERBOARD_LINES >= 2) // scroll up
          this->CURRENT_LEADERBOARD_LINES -= 2;
        else return;
  
        this->PrintCurrentLeaderboardLines();
        return;
      }

      if (action && this->CURRENT_STATS_DISPLAY_LINES <= (SIZEOF_STATS_DISPLAY - ROWS - 2)) // scroll down
        this->CURRENT_STATS_DISPLAY_LINES += 2;
      else if (!action && this->CURRENT_STATS_DISPLAY_LINES >= 2) // scroll up
        this->CURRENT_STATS_DISPLAY_LINES -= 2;
      else return;

      this->PrintCurrentStatsLines();
    }

    void PrintCurrentStatsLines()
    {
      _lcdf.clear();
      this->home();

      this->println(this->TOTAL_STATS_DISPLAY_LINES[this->CURRENT_STATS_DISPLAY_LINES]);
      this->println(this->TOTAL_STATS_DISPLAY_LINES[this->CURRENT_STATS_DISPLAY_LINES + 1]);
      this->println(this->TOTAL_STATS_DISPLAY_LINES[this->CURRENT_STATS_DISPLAY_LINES + 2]);
      this->println(this->TOTAL_STATS_DISPLAY_LINES[this->CURRENT_STATS_DISPLAY_LINES + 3]);
    }

    void PrintCurrentLeaderboardLines()
    {
      _lcdf.clear();
      this->home();

      this->println(this->TOTAL_LEADERBOARD_LINES[this->CURRENT_LEADERBOARD_LINES]);
      this->println(this->TOTAL_LEADERBOARD_LINES[this->CURRENT_LEADERBOARD_LINES + 1]);
      this->println(this->TOTAL_LEADERBOARD_LINES[this->CURRENT_LEADERBOARD_LINES + 2]);
      this->println(this->TOTAL_LEADERBOARD_LINES[this->CURRENT_LEADERBOARD_LINES + 3]);
    }

    /**
     * Get the private SCREEN variable
     * 
     * SCREEN is a variable that keeps track of the current
     * screen the user is on. Ranges from 1-7.
     * 
     * @returns this.SCREEN
     */
    inline const uint8_t GetScreen()
    {
      return this->SCREEN;
    }

    /**
     * Insert-Card Screen
     * 
     * The first screen you see that prompts the user
     * to insert their credit card into the machine.
     */
    void screen1()
    {
      this->SCREEN = 1;
      _lcdf.clear();
      this->setCursor(0, 1);
      this->println("   INSERT    CARD  ");
      this->nextLine();
    }

    /**
     * Greeting Screen
     * 
     * The first screen the user is prompted with upon
     * inserting their card into the machine.
     */
    void screen2()
    {
      this->SCREEN = 2;
      _lcdf.clear();
      this->home();
      this->println("Hello, " + CURRENT_USER->name);
      this->println("Balance: $" + String(CURRENT_USER->balance));
      this->nextLine();
      this->print("Press # to continue");
    }

    /**
     * Options Menu Screen
     * 
     * Main ATM screen. From here, the user can choose
     * to buy tokens, sell tokens, view their stats, 
     * or view their balance temporarily.
     */
    void screen3()
    {
      this->SCREEN = 3;
      _lcdf.clear();
      this->home();
      
      this->println("      Options:      ");
      this->println("--------------------");
      this->println("A: BUY    |  B: SELL");
      this->println("C: STATS  |  D: LB  ");
    }

    /**
     * Purchase-Tokens Screen
     * 
     * Path A of screen3's options menu.
     */
    void screen4()
    {
      this->SCREEN = 4;  
      _lcdf.clear();
      this->home();

      this->println("   Purchase Tokens  ");
      this->println("--------------------");
      this->println("Balance: $" + String(CURRENT_USER->balance)) ;
        this->print("Enter Amount: ");
    }

    /**
     * Trade-Tokens Screen
     * 
     * Path B of screen3's options menu.
     */
    void screen5()
    {
      this->SCREEN = 5;
      _lcdf.clear();
      this->home();

      this->println("    Trade Tokens    ");
      this->println("--------------------");
      this->println("Balance: $" + String(CURRENT_USER->balance));
      this->println("<-- Deposit Tokens  ");
    }

    /**
     * User-Stats Screen
     * 
     * Path C of screen3's options menu.
     */
    void screen6()
    {
      this->SCREEN = 6;
      _lcdf.clear();
      this->home();

      User* leaderboard_users_p[USERS_NUM];
      GetUsersLeaderboard(leaderboard_users_p);
      
      for (int i = 0; i < USERS_NUM; i++)
      {
        if ((i + 1) < leaderboard_users_p[i]->best_leaderboard_position)
          leaderboard_users_p[i]->best_leaderboard_position = i + 1;
        if ((i + 1) > leaderboard_users_p[i]->worst_leaderboard_position)
          leaderboard_users_p[i]->worst_leaderboard_position  = i + 1;
      }

      this->TOTAL_STATS_DISPLAY_LINES[0] = "     Your Stats     ";
      this->TOTAL_STATS_DISPLAY_LINES[1] = "--------------------";
      this->TOTAL_STATS_DISPLAY_LINES[2] = "  Use A/B to scroll ";
      this->TOTAL_STATS_DISPLAY_LINES[3] = "--------------------";
      this->TOTAL_STATS_DISPLAY_LINES[4] = "Tokens Bought: " + String(CURRENT_USER->tokens_purchased);
      this->TOTAL_STATS_DISPLAY_LINES[5] = "Tokens Traded: " + String(CURRENT_USER->tokens_traded);
      this->TOTAL_STATS_DISPLAY_LINES[6] = "Richest: $"      + String(CURRENT_USER->highest_balance);
      this->TOTAL_STATS_DISPLAY_LINES[7] = "Poorest: $"      + String(CURRENT_USER->lowest_balance);
      this->TOTAL_STATS_DISPLAY_LINES[8] = "Best LB Spot: "   + String(CURRENT_USER->best_leaderboard_position);
      this->TOTAL_STATS_DISPLAY_LINES[9] = "Worst LB Spot: "  + String(CURRENT_USER->worst_leaderboard_position);
      this->TOTAL_STATS_DISPLAY_LINES[10] = "--------------------";
      this->TOTAL_STATS_DISPLAY_LINES[11] = "                    ";

      this->CURRENT_STATS_DISPLAY_LINES = 0;
      PrintCurrentStatsLines();
    }

    /**
     * Leaderboard Screen
     * 
     * Path D of screen3's options menu.
     */
    void screen7()
    {
      this->SCREEN = 7;
      
      User* leaderboard_users_p[USERS_NUM];
      GetUsersLeaderboard(leaderboard_users_p);
      
      this->TOTAL_LEADERBOARD_LINES[0] = "    Leaderboard     ";
      this->TOTAL_LEADERBOARD_LINES[1] = "--------------------";
      this->TOTAL_LEADERBOARD_LINES[2] = "  Use A/B to scroll ";
      this->TOTAL_LEADERBOARD_LINES[3] = "--------------------";

      this->CURRENT_LEADERBOARD_LINES = 0;

      for (int i = 0; i < USERS_NUM; i++)
        TOTAL_LEADERBOARD_LINES[i + 4] =
        String(i + 1) + ". " +
        leaderboard_users_p[i]->name +
        " - $" + String(leaderboard_users_p[i]->balance);

      this->TOTAL_LEADERBOARD_LINES[USERS_NUM + 4] = "--------------------";

      if ((USERS_NUM + 4) % 2 != 0)
        this->TOTAL_LEADERBOARD_LINES[USERS_NUM + 5] = "                 ";

      PrintCurrentLeaderboardLines();
    }

    /**
     * Dispensing-Tokens-Message Screen
     * 
     * This screen cannot be interacted with, and is not part of the 7 main screens
     * It will display the amount of tokens left to dispense.
     * 
     * @param amount The amount of tokens left to dispense
     */
    void screen8(const uint8_t amount)
    { 
      this->SCREEN = 8;     
      const String amount_s = amount < 10 ? "0" + String(amount) : String(amount);
      
      _lcdf.clear();
      this->setCursor(0, 1);

      if (amount == 0)
      {
        this->println("TRANSACTION COMPLETE");
        this->println("    REMOVE CARD    ");

        RedLED.Show();
        GreenLED.Hide();
        PREVENT_GLED_SHOW = true;
      }
      else
      {
        this->println(" DISPENSING TOKENS ");
        this->println("      " + amount_s + " Left      ");
      }
    }

    void screen9(const double amount)
    {
      _lcdf.clear();
      this->home();
      
      this->println("INSUFFICIENT FUNDS");
      this->println("Balance: $" + String(CURRENT_USER->balance));
      this->println("Price: $" + String(amount * TOKEN.VALUE));
      this->print("Press * to return");
    }

    void screen10()
    {
      this->SCREEN = 10;
      _lcdf.clear();
      this->setCursor(0, 1);

      this->println("    INVALID USER    ");
      this->println("    REMOVE CARD     ");
    }
};

#endif
