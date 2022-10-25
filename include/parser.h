class Token {
  public:
    char kind;
    double value;
};

Token get_token();
double expression();
double term();
double primary();
