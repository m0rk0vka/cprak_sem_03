#include <stdio.h>
#include <stdlib.h>
 

typedef struct list
{
   struct list *ptr;
   int field;
}List;


List * addelem(List *lst, int number)
{
   List *tmp, *p;
   tmp = (List*)malloc(sizeof(List));
   p = lst->ptr; // сохранение указателя на следующий узел
   lst->ptr = tmp; // предыдущий узел указывает на создаваемый
   tmp->field = number; // сохранение поля данных добавляемого узла
   tmp->ptr = p; // созданный узел указывает на следующий элемент
   return(tmp);
}


void listprint(List *lst)
{
   List *p;
   p = lst;
   do {
      printf("%d ", p->field); // вывод значения элемента p
      p = p->ptr; // переход к следующему узлу
   } while (p != NULL);
}


void list_bubble_sort(List *lst, int size) {
   int i, j;
   for (i = size-1; i >= 0; i--) {
      List *tmp = lst;
      for (j = 0; j < i; j++) {
         if (tmp->field > tmp->ptr->field) {
            int k = tmp->field;
            tmp->field = tmp->ptr->field;
            tmp->ptr->field = k;
         }
         tmp = tmp->ptr;
      }
   }
}


int main(void) {
   int N = 0, i = 0, input;
   List *lst = NULL;
   List *root = lst;
   while ((i = scanf("%d", &input)) != EOF) {
      N++;
      lst = addelem(lst, i);
   }
   printf("hello");
   list_bubble_sort(root, N);
   printf("world\n");
   listprint(root);
   printf("\n");
   return 0;
}
