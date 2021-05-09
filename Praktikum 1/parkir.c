#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int getin;
    int getout;
    struct node *next;
}SListNode;

typedef struct list{
    unsigned _size;
    SListNode *head;
}Singlylist;


void initialize(Singlylist *list){
    list->head = NULL;
    list->_size = 0;
}

bool isEmpty(Singlylist *list){
    return(list->head == NULL);
}


SListNode *createnode(int in, int out){
    SListNode *newnode = (SListNode*)malloc(sizeof(SListNode));
    newnode->getin = in;
    newnode->getout = out;
    newnode->next = NULL;
    return newnode;
}


void slist_pushBack(Singlylist *list, int in, int out){
    list->_size++;

    SListNode *newnode = createnode(in, out);
    if(isEmpty(list)){
        list->head = newnode;
        return;
    }else if(out < list->head->getout){ //Kalo dia paling kecil, jadi yang pertama
        newnode->next = list->head;
        list->head = newnode;
    }else{
        SListNode *temp = list->head;
          while(temp->next != NULL && out>temp->next->getout){ //Menempatkan urutan biar terurut
              temp = temp->next;
          }
        newnode->next = temp->next; //sesudah lebih kecil, sebelum lebih besar
        temp->next = newnode;
    }
}


void removing(Singlylist *list, int target){
    list->_size -= 1;
    SListNode *temp = list->head;
    SListNode *prev; //Buat connect linked list yang terputus
    if(target == list->head->getout){ //Kalo yang pertama keluar, move headnya ke nextnya
        list->head = list->head->next;
    }else{
        while(temp != NULL){
            prev = temp;
            temp = temp->next;
            if(target == temp->getout){
              break; //udah ketemu
              }
        }
        prev->next = temp->next; //connected
        free(temp);
    }
}


int result(Singlylist *list, int capacity, int time){
    SListNode *temp = list->head;
    while(temp != NULL){
        if(temp->getout <= time){
            removing(list, temp->getout); //Remove yang udah keluar sebelum Pika masuk dan antrian (list->size berkurang 1)
        }
        temp = temp->next;
    }

    if(list->_size<capacity){
      return 1; //Kalo masih ada, return 1 (true)
    }else{ //Kalo sudah di remove yang keluarnya tetapi masih ada antrian yang lebih dri kpasitas, artinyaa engga bisa amasuk
      return 0; //return false
    }
}


int main(){
    int times;
    scanf("%d", &times);
    Singlylist mylist[times];
    
    int capacity, time, antre, entering, exiting;
    int final[times];

    for(int i=0 ; i<times ; ++i){
        initialize(&mylist[i]);
        scanf("%d", &time); 
        scanf("%d", &capacity);
        scanf("%d", &antre);

        for(int k=0 ; k<antre; ++k){
            scanf("%d", &entering);
            scanf("%d", &exiting);
            slist_pushBack(&mylist[i], entering, exiting);
        }

            final[i] = result(&mylist[i], capacity, time);
    }

    for(int i=0 ; i<times ; ++i){
        if(final[i] == 1){
          printf("Pika Pika!\n");
        
        }else{
            printf("Pika Zzz\n");
        }
    }
    return 0;
}