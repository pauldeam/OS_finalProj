#include "insertdevnode.h"
#include "checkCPU.h"

// for device waiting queue
void insertdevnode(node *n) {

  if (devqhead == NULL) {
    devqhead = n;
  } else {
    node *tmp = devqhead;
    while (tmp->next != NULL) {
     
      tmp = tmp->next;
    }
    tmp->next = n;
  }
  node *checktmp = finished;
  while(checktmp != NULL){
      if(checktmp->job == n->job){
          checkDev(checktmp);
      }
      checktmp = checktmp->next;
  }
  
}

