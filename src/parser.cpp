#include <cstdio>
#include <iostream>
#include <string>
#include <stdexcept>
#include "parser.h"

using namespace std;


/* Token Class Methods */
Token::Token(char kind, double value) {
  this->kind = kind;
  this->value = value;
}


/* TokenStream Class Methods*/
TokenStream::TokenStream() {
  this->buffer = Token('.', 0);
}

Token TokenStream::get(){
  if (this->is_full) {
    this->is_full = false;
    return this->buffer;
  }

  char current_char;
  double value;
  cin >> noskipws;
  cin >> current_char;
  switch (current_char) {
    case '\n':
    case '+': case '-': case '*': case '/':
    case '(': case ')':
      {
        Token token = Token(current_char, 0);
        return token;
      }

    case '.':
    case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9': case '0':
      {
        cin.putback(current_char);
        cin >> value;
        Token token = Token('8', value);
        return token;
      }

    case 'q':
      return Token('q', 0);

    default:
      string error = "Bad token: ";
      error.push_back(current_char);
      throw runtime_error(error);
  }
}

void TokenStream::putback(Token token) {
  if (this->is_full) throw runtime_error("Buffer is full!");
  this->buffer = token;
  this->is_full = true;
}


/* Calculator functions */

double expression();

double primary(){
  Token token = stream.get();

  switch (token.kind) {
    case '(':
      {
        double expr = expression();
        token = stream.get();
        if (token.kind != ')') throw runtime_error("')' expected");
        return expr;
      }

    case '8':
      return token.value;

    default:
      throw runtime_error("Primary expected");
  }
  return 0;
}

double term(){
  double left = primary();
  Token token = stream.get();

  while (true) {
    switch (token.kind) {
      case '*':
        left *= primary();
        token = stream.get();
        break;

      case '/':
        {
          double d = primary();
          if (d==0) throw runtime_error("Division by 0!");
          left /= d;
          token = stream.get();
          break;
        }

      default:
        stream.putback(token);
        return left;
    }
  }
}

double expression() {
  double left = term();
  Token token = stream.get();

  while (true) {
    switch (token.kind) {
      case '+':
        left += term();
        token = stream.get();
        break;

      case '-':
        left -= term();
        token = stream.get();
        break;

      case '\n':
        return left;

      default:
        stream.putback(token);
        return left;
    }
  }
}

