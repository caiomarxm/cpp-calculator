#include <cstdio>
#include <iostream>
#include <ostream>
#include "parser.h"

using namespace std;

TokenStream stream;

int main (int argc, char *argv[])
{
  stream = TokenStream();
  Token token = Token(EOF, 0);
  double result;

  do {
    setvbuf(stdout, NULL, _IONBF, 0);
    cout << "> ";
    token = stream.get();
    if (token.kind == 'q') {
      break;
    }
    stream.putback(token);
    result = expression();
    cout << "= " << result << endl;
  } while (cin);

  return 0;
}
