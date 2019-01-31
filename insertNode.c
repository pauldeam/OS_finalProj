#include "insertNode.h"
#include "sortedInsert.h"

void insertNode(node *n) {
  if (n->pri == 2) {
   
    if (hq2head == NULL) {
      hq2head = n;
      hq2head->next = NULL;
      //printf("job %d is the head of hq2\n", hq2head->job);

    } else {
      node *tmp = hq2head;
      while (tmp->next != NULL) {
        
        tmp = tmp->next;
        break;
      }
      tmp->next = n;
      //printf("Job %d is the last node in hq2\n", n->job);
    }
  }
  else if (n->pri == 1) {
    
    // insert first node
    sortedInsert(&hq1head, n);
    //printf("job %d in hq1", n->job);
  }
}

void deleteNode(node *n){
    node * tmp = readyhead;
    while(tmp->next != NULL){
	if(tmp->next->job == n->job){
	    tmp->next = tmp->next->next;
	}
	tmp = tmp->next;
    }



}
