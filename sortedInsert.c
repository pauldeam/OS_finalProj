
#include "sortedInsert.h"

// for hq1 - SJF
void sortedInsert(node **head_ref, node *new_node) {
  node *current;
  // Special case for the head end
  if (*head_ref == NULL || (*head_ref)->run >= new_node->run) {
    new_node->next = *head_ref;
    *head_ref = new_node;
  } else {
    // Locate the node before the point of insertion
    current = *head_ref;
    while (current->next != NULL && current->next->run < new_node->run) {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
  }
}
