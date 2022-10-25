#include <iostream>
#include "parser.h"

using namespace std;

int main (int argc, char *argv[])
{
  double result;
  do {
    cout << "> ";
    result = expression();
    cout << result << endl;
  } while (cin);

  return 0;
}
