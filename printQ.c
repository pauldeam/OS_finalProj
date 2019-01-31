

//functino to print contents in a queue

int printQ(node * head) {
    if(head == NULL) return 0;
    node *tmp = head;
  while (tmp->next != NULL) {
    printf("%d", tmp->job);
    printf("->");
    tmp = tmp->next;
  }
  printf("%d", tmp->job);
  printf("\n");
  return 0;

  
}
