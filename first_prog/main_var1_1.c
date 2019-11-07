#include <stdio.h>
#include <stdlib.h>


typedef struct list
{
    struct list * next;
    int num;
}st;


st* list_bubble_sort(st* head);
void print_list(st* tmp);
void clear_list(st* tmp);


int main(void){
  int err, num;
  st* head = NULL;
  while ((err = scanf("%d", &num)) != EOF && err != 0) {
    st* tmp = (st*) malloc(sizeof(st));
    tmp->num = num;
    tmp->next = head;
    head = tmp;
  }
  head = list_bubble_sort(head);
  st* tmp = head;
  print_list(tmp);
  clear_list(head);
  return 0;
}


st* list_bubble_sort(st* head){
  st* tmp;
  st* tmp_k;
  st* resault = head;
  head = head->next;
  resault->next = NULL;
  while(head != NULL){
    tmp = head;
    head = head->next;
    if (tmp->num < resault->num) {
      tmp->next = resault;
      resault = tmp;
    }else{
      tmp_k = resault;
      while(tmp_k->next != NULL){
    if(tmp_k->next->num > tmp->num)
      break;
    tmp_k=tmp_k->next;
      }
      tmp->next = tmp_k->next;
      tmp_k->next = tmp;
    }
  }
  return resault;
}


void print_list(st* tmp)
{
    while(tmp !=  NULL){
        printf("%d ", tmp->num);
        tmp = tmp->next;
    }
    printf("\n");
}


void clear_list(st* tmp)
{
  while(tmp != NULL){
    st* tmp_cl = tmp->next;
    free(tmp);
    tmp = tmp_cl;
  }
}
