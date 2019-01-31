#include "getWords.h"

// seperates the instruction line according to spaces (' ')
int getWords(char *buf, char target[10][20]) {
  int n = 0, i, j = 0;

  for (i = 0; TRUE; i++) {
    if (buf[i] != ' ') {
      target[n][j++] = buf[i];
    } else {
      target[n][j++] = '\0'; // insert NULL
      n++;
      j = 0;
    }
    if (buf[i] == '\0')
      break;
  }
  return n;

} // end getWords
