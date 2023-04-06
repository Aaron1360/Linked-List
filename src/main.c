
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "llist.h"

int main(int argc, char **argv) {
  
  Node *list1_head = NULL;
  Node *list2_head = NULL;

  list1_head = insert_at_tail(list1_head, 8);
  list1_head = insert_at_tail(list1_head, 1);
  list1_head = insert_at_tail(list1_head, 6);
  list1_head = insert_at_tail(list1_head, 9);
  list1_head = insert_at_tail(list1_head, 2);

  list2_head = insert_at_tail(list2_head, 3);
  list2_head = insert_at_tail(list2_head, 7);
  list2_head = insert_at_tail(list2_head, 1);
  list2_head = insert_at_tail(list2_head, 0);
  list2_head = insert_at_tail(list2_head, 5);
  
  printf("\nLIST 1:\n");
  print_list(list1_head);
  
  printf("\nLIST 2:\n");
  print_list(list2_head);

  printf("\nNEW LIST:\n");
  list1_head = merge_list(list1_head,list2_head);
  print_list(list1_head);
}
