#include "insertReady.h"
#include "checkCPU.h"

void insertReady(node *n) {
  
  if (readyhead == NULL) {
    readyhead = n;
    //if(n->job == 1)checkCPU(readyhead);
    
  } else {
    node *tmp = readyhead;
    while (tmp->next != NULL) {
      //printf("job %d -> ", tmp->job);
      //fflush(stdout);
      tmp = tmp->next;
    }
    //printf("job %d\n", n->job);
    //fflush(stdout);
    tmp->next = n;
    checkCPU(readyhead);
    
  }
}

void insertFin(node *n){

  if (finished == NULL) {
    finished = n;
  } 
    else {
    node *tmp = finished;
    while (tmp->next != NULL) {
      //printf("job %d \n", tmp->job);
      fflush(stdout);
      tmp = tmp->next;
    }
   
    tmp->next = n;
    n->next = NULL;

  }
}
