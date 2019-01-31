/* authors: Scott Miller & Paul Jureidini  */

#include <json-c/json_object.h>

#include "global.h"
#include "getWords.h"
#include "getWords.c"
#include "getNum.h"
#include "getNum.c"
#include "insertNode.h"
#include "insertNode.c"
#include "sortedInsert.h"
#include "sortedInsert.c"
#include "insertdevnode.h"
#include "insertdevnode.c"
#include "insertReady.h"
#include "insertReady.c"
#include "readFile.h"
#include "readFile.c"
#include "checkCPU.h"
#include "checkCPU.c"
#include "readyQ.h"
#include "readyQ.c"


#include "printQ.c"




int printQ();

int main(int argc, char *argv[]) {
  
  readFile(argc, argv);

  return 0;
}









