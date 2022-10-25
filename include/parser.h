class Token {
  public:
    Token(char kind, double value);
    char kind;
    double value;
};

class TokenStream {
  public: 
    TokenStream();
    Token get();
    void putback(Token token);
  private:
    Token buffer {Token('.', 0)};
    bool is_full {false};
};

extern TokenStream stream;

Token get_token();
double expression();
double term();
double primary();
