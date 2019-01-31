#include "getNum.h"

// get the number/value
int getNum(char *str) {

  int total_n = 0;
  int m;
  int o;
  while (1 == sscanf(str + total_n, "%*[^0123456789]%d%n", &o, &m)) {
    total_n += m;
    // printf("%d\n", o);
  }

  return o;

} // end getNum
