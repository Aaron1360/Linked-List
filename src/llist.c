/*LINKED LIST LIBRARY
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "llist.h"

//print linked list
void print_list(Node *head)
{
  Node *current;
  current = head;
  int i=0;
  while(current != NULL){
      printf("Node %d = %d\n",i,current->value);
      i++;
      current=current->next;
    }
}

//insert new node at head
Node *insert_at_head(Node *head, int new_value)
{
  Node *newNode = calloc(1, sizeof(Node));
  newNode->value = new_value;

  if(head == NULL) return newNode;
  else{
    newNode->next = head;
    return newNode;
  }
}

//insert new node at tail
Node *insert_at_tail(Node *head, int new_value)
{
  Node *newNode = calloc(1, sizeof(Node));
  newNode->value = new_value;

  if(head == NULL) return newNode;
  else{
    Node *current = head;
    while(current->next != NULL) current = current->next;
    current->next = newNode;
    return head;
  }
}

//delete node at head
Node *delete_at_head(Node *head)
{
  if(head == NULL){
    return NULL;
  }
  else{
    Node *to_return = head->next;
    free(head);
    return to_return;
  }
}

//delete node at tail
Node *delete_at_tail(Node *head)
{
  if(head == NULL) return NULL;
  else if(head->next == NULL){
    free(head);
    return NULL;
  }
  else{
    Node *current = head;
    Node *prev = NULL;
    while(current->next != NULL){
      prev = current;
      current = current->next;
    }
    prev->next = NULL;
    free(current);
    return head;
  }
}

//length of the list
int length(Node *head)
{
  Node *current;
  current = head;
  int length = 0;
  while(current != NULL){
    length++;
    current = current->next;
  }
  return length;
  
}
//recursive length of the list
int recursive_length(Node *node)
{
  if(node == NULL) return 0;
  else return 1 + recursive_length(node->next);
}

//find value
bool is_member(Node *node, int find_value)
{
  if(node == NULL) return false;
  else if(node->value == find_value) return true;
  else return is_member(node->next, find_value);
}

//count matches 
int count_matches(Node *node, int find_value)
{
  if(node == NULL) return 0;
  else if(node->value == find_value) return 1 + count_matches(node->next, find_value);
  else return count_matches(node->next, find_value);
}

//replace matches
void replace_matches(Node *node, int find_value, int replace_value)
{
  if(node != NULL){
    if(node->value == find_value) node->value = replace_value;
    replace_matches(node->next, find_value, replace_value);
  }
}

//delete first match
Node *delete_first_match(Node *head, int delete_value, bool *was_deleted)
{
  if(head == NULL){
    *was_deleted = false;
    return NULL;
  }
  
  if(head->value == delete_value){
    Node *temp = head->next;
    free(head);
    *was_deleted = true;
    return temp;
  }

  Node *current = head->next;
  Node *prev = head;

  while(current != NULL){
    if(current->value == delete_value){
      prev->next = current->next;
      free(current);
      *was_deleted = true;
      return(head);
    }
    prev = current;
    current = current->next;
    }

  *was_deleted = false;
  return head;
}

//delete all matches
Node *delete_all_matches(Node *head, int delete_value, int *num_deleted)
{
  Node *current = head;
  bool deleted = false;
  *num_deleted = 0;
  do {
  current = delete_first_match(current, delete_value, &deleted);
    if(deleted) *num_deleted +=1;
  }while (deleted);
  return current;
}

//efficient delete
Node *efficient_delete_match(Node *head, int delete_value, int *num_deleted)
{
  if(head == NULL) return NULL;

  Node *current, *temp, *new_head;
  current = head;
  while(current->value == delete_value){
    temp = current;
    current = current->next;
    *num_deleted +=1;
  }
  new_head = current;

  while(current->next != NULL){
    if(current->next->value == delete_value){
      temp = current->next;
      current->next = current->next->next;
      free(temp);
      *num_deleted+=1;
    }
    else current = current->next;
  }
  return new_head;
}

//append
Node *append_list(Node *head1, Node *head2)
{
  if(head1 == NULL) return head2;

  Node *current = head1;

  while(current->next != NULL) current = current->next;

  current->next = head2;
  return head1;
}

//reverse list
Node *reverse_list(Node *head)
{
  if(head == NULL) return NULL;
  if(head->next == NULL) return head;

  Node *current = head;
  Node *next_node = head->next;

  current->next = NULL;

  while(next_node != NULL){
    Node *temp = next_node->next;
    next_node->next = current;
    current = next_node;
    next_node = temp;
  }
  return current;
}

//bubble sort
void sort_list(Node *head)
{
  if(head == NULL) return;
  if(head->next == NULL) return;

  bool swapped = false;
  do {
    swapped = false;
    Node *current = head;
    Node *prev = NULL;

    while (current->next != NULL) {
      prev = current;
      current = current->next;
      if(current != NULL){
        if(current->value < prev->value){
          int temp;
          temp = prev->value;
          prev->value = current->value;
          current->value = temp;
          swapped = true;
        }
      }
    }
  }while (swapped);
}

//delete duplicates
void delete_duplicates(Node *head)
{
  if(head == NULL) return;
  if(head->next == NULL) return;

  Node *current1, *current2, *duplicate;
  current1 = head;

  while(current1 != NULL && current1->next != NULL){
    current2 = current1;
    while(current2->next != NULL){
      if(current1->value == current2->next->value){
        duplicate = current2->next;
        current2->next = current2->next->next;
        free(duplicate);
      }
      else current2 = current2->next;
    }
    current1 = current1->next;
  }
}

//insert new node after a value
Node *insert_after(Node *head, int new_value, int after_value)
{
  Node *new_node = calloc(1, sizeof(Node));
  new_node->value = new_value;

  if(head == NULL) return new_node;
    
  else{
    Node *current = head;
    
    while(current->next != NULL){
      if(current->value == after_value){
        new_node->next = current->next;
        current->next = new_node;
        return head;
      }
      else current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    return head;
  }
}

//delete list
Node *delete_list(Node *head)
{
  if(head != NULL){
    delete_list(head->next);
    free(head);
  }
  return NULL;
}

//add two list 
Node *add_two_lists(Node *list1, Node *list2)
{
  Node *temp1 = list1;
  Node *temp2 = list2;

  if(list1 && list2){
    
    if(length(list1) >= length(list2)){
      while(temp1){
        if(temp2 != NULL){
          temp1->value += temp2->value;
          temp2 = temp2->next;
        }
        temp1 = temp1->next;
      }
      return list1;
    }

    else{
      while(temp2){
          if(temp1 != NULL){
            temp2->value += temp1->value;
            temp1 = temp1->next;
          }
          temp2 = temp2->next;
        }
        return list2;
    }  
  }
  else if(list1 != NULL && list2 == NULL){return list1;}
  else if(list1 == NULL && list2 != NULL){return list2;}
  else{printf("\nERROR\n");return NULL;}
}

//duplicate 
Node *duplicate_list(Node *list1)
{
  if(list1 != NULL){
    Node *newNode = calloc(1, sizeof(Node));
    newNode->value = list1->value;
    newNode->next = duplicate_list(list1->next);
    return newNode;
  }
  else return NULL;
}

// merge lists
Node *merge_list(Node *list1, Node *list2)
{
  if(list1 == NULL) return list2;
  if(list2 == NULL) return list1;

  sort_list(list1);
  sort_list(list2);
  Node *l1current, *l2current, *newhead, *newcurrent;
  l1current = list1;
  l2current = list2;

  if(l1current->value <= l2current->value){
    newhead = l1current;
    l1current = l1current->next;
  }
  else{
    newhead = l2current;
    l2current = l2current->next;
  }
  newcurrent = newhead;

  while(l1current != NULL && l2current != NULL){
    if(l1current->value <= l2current->value){
      newcurrent->next = l1current;
      newcurrent = l1current;
      l1current = l1current->next;
    }
    else{
      newcurrent->next = l2current;
      newcurrent = l2current;
      l2current = l2current->next;
    }
  }

  if(l1current == NULL){
    newcurrent->next = l2current;
  }
  else if(l2current == NULL){
    newcurrent->next = l1current;
  }
  return newhead;
}