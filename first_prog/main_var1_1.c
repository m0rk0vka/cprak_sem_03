#include <stdio.h>
#include <stdlib.h>


typedef struct list
{
    struct list * next;
    int num;
}st;


void list_bubble_sort(st* head, int size);
void print_list(st* tmp, int size);


int main(void){
    int err, num, cnt = 0;
    st* head = NULL;
    while ((err = scanf("%d", &num)) != EOF && err != 0) {
        cnt++;
        st* tmp = (st*) malloc(sizeof(st));
        tmp->num = num;
        tmp->next = head;
        head = tmp;
    }
    list_bubble_sort(head, cnt);
    st* tmp = head;
    print_list(tmp, cnt);
    free(head);
    return 0;
}


void list_bubble_sort(st* head, int size){
    int i, j, k;
    for (i = 0; i < size - 1; i++){
        st* tmp = head;
        for(j = 0; j < size - i - 1; j++){
            if (tmp->num > tmp->next->num) {
                k = tmp->num;
                tmp->num = tmp->next->num;
                tmp->next->num = k;
            }
            tmp = tmp->next;
        }
    }
}


void print_list(st* tmp, int size)
{
    int i;
    for (i=0; i < size; i++){
        printf("%d ", tmp->num);
        tmp = tmp-> next;
    }
    printf("\n");
}
