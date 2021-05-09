#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int jamMasuk;
    int jamKeluar;
    struct node *next;
}SListNode;

typedef struct list{
    unsigned _size;
    SListNode *head;
}Singlylist;

void slist_initialize(Singlylist *list){
    list->head = NULL;
    list->_size = 0;
}

bool slist_isEmpty(Singlylist *list){
    return(list->head == NULL);
}

//urutkan dari kecil ke besar boi
void slist_pushBack(Singlylist *list, int masuk, int keluar){
    SListNode *newnode = (SListNode*)malloc(sizeof(SListNode));
    newnode->jamMasuk = masuk;
    newnode->jamKeluar = keluar;
    newnode->next = NULL;
    list->_size++;

    if(slist_isEmpty(list)){
        list->head = newnode;
        return;
    }
    
    //kalo ternyata yg keluar lebih kecil dari list, jadikan dia di depan
    else if(keluar < list->head->jamKeluar){ //kecil -> besar
        newnode->next = list->head;
        list->head = newnode;
    }
    
    //cari terus sampe ketemu, lalu tinggal rubah dengan mirip swap
    else{
        SListNode *temp = list->head;
        while((temp->next != NULL) && keluar > temp->next->jamKeluar){ 
            temp = temp->next;
        }
        newnode->next = temp->next; 
        temp->next = newnode;
    }
}

void slist_popBack(Singlylist *list)
{
    if (!slist_isEmpty(list)) {
        SListNode *nextNode = list->head->next;
        SListNode *currNode = list->head;

        if (currNode->next == NULL) {
            free(currNode);
            list->head = NULL;
            return;
        }

        while (nextNode->next != NULL) {
            currNode = nextNode;
            nextNode = nextNode->next;
        }
        currNode->next = NULL;
        free(nextNode);
        list->_size--;
    }
}

void slist_remove(Singlylist *list, int index){
    list->_size--;
    SListNode *temp = list->head;
    SListNode *prev; 
    if(index == list->head->jamKeluar){ 
        list->head = list->head->next;
    }
    
    else{
        while(temp != NULL){
            prev = temp;
            temp = temp->next;
            if(index == temp->jamKeluar){
              break;
              }
        }
        prev->next = temp->next; 
        free(temp);
        
    }
}


int isAllow(Singlylist *list, int isiParkir, int jam){
    SListNode *temp = list->head;
    
    //kalo lebih besar dari jam, pop out
    while(temp != NULL){
        if(temp->jamKeluar <= jam){
            slist_remove(list, temp->jamKeluar); 
        }
        temp = temp->next;
    }

    //otomatis
    if(list->_size < isiParkir){
      return 1; 
    }else{ 
      return 0;
    }
}


int main(){
    int testcase;
    scanf("%d", &testcase);

    //BUAT OBJEK myList
    Singlylist mylist[testcase];
    int isTrue[testcase];
    int isiParkir, jam, banyakParkir, masuk, keluar;
    for(int i = 0 ; i < testcase; ++i){
        //PENTING! Jangan lupa diinisialisasi
        slist_initialize(&mylist[i]);
        scanf("%d %d", &jam, &isiParkir); 
        scanf("%d", &banyakParkir);

        for(int j = 0 ; j < banyakParkir; ++j){
            scanf("%d %d", &masuk, &keluar);
            slist_pushBack(&mylist[i], masuk, keluar);
        }
            isTrue[i] = isAllow(&mylist[i], isiParkir, jam);

    }

    for(int i = 0 ; i < testcase ; ++i){
        if(isTrue[i] == 0){
          printf("Pika Zzz\n");
        
        }
        
        else if(isTrue[i] == 1){
            printf("Pika Pika!\n");
        }
    }

    
    return 0;
}