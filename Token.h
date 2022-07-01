// HEADER => Token Class

#ifndef TOKEN_H
#define TOKEN_H

class Token
{
  private:
    
  public:
    float VALUE;
    
    Token(const float starting_value) : VALUE(starting_value) {}

    void DisplayValue();
};

#endif
