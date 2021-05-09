#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Struktur Node */
typedef struct snode_t {
    char str[51];
    struct snode_t *next;
} SListNode;

/* Struktur ADT SinglyList */
typedef struct slist_t {
    unsigned _size;
    SListNode *_head;
} SinglyList;

/* Function definition below */

void slist_init(SinglyList *list);
bool slist_isEmpty(SinglyList *list);
void slist_pushFront(SinglyList *list, char str[]);
void slist_popFront(SinglyList *list);
void slist_pushBack(SinglyList *list, char str[]);
void slist_popBack(SinglyList *list);
void slist_insertAt(SinglyList *list, int index, char str[]);
void slist_removeAt(SinglyList *list, int index);
void slist_remove(SinglyList *list, char str[]);
char*  slist_front(SinglyList *list);
char*  slist_back(SinglyList *list);
char*  slist_getAt(SinglyList *list, int index);

void slist_init(SinglyList *list) 
{
    list->_head = NULL;
    list->_size = 0;
}

bool slist_isEmpty(SinglyList *list) {
    return (list->_head == NULL);
}

void slist_pushFront(SinglyList *list, char str[]) 
{
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        list->_size++;
        //newNode->data = value;
        strcpy(newNode->str, str);

        if (slist_isEmpty(list)) newNode->next = NULL;
        else newNode->next = list->_head;
        list->_head = newNode;
    }
}

void slist_popFront(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        SListNode *temp = list->_head;
        list->_head = list->_head->next;
        free(temp);
        list->_size--;
    }
}

void slist_pushBack(SinglyList *list, char str[])
{
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        list->_size++;
        // newNode->str = value;
        strcpy(newNode->str, str);
        newNode->next = NULL;
        
        if (slist_isEmpty(list)) 
            list->_head = newNode;
        else {
            SListNode *temp = list->_head;
            while (temp->next != NULL) 
                temp = temp->next;
            temp->next = newNode;
        }
    }
}

void slist_popBack(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        SListNode *nextNode = list->_head->next;
        SListNode *currNode = list->_head;

        if (currNode->next == NULL) {
            free(currNode);
            list->_head = NULL;
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

void slist_insertAt(SinglyList *list, int index, char str[])
{
    /* Kasus apabila posisinya melebihi batas */
    if (slist_isEmpty(list) || index >= list->_size) {
        slist_pushBack(list, str);
        return;    
    }
    else if (index == 0 || index < 0) {
        slist_pushFront(list, str);
        return;
    }
    
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        SListNode *temp = list->_head;
        int _i = 0;
        while (temp->next != NULL && _i < index-1) {
            temp = temp->next;
            _i++;
        }
        // newNode->data = value;
        strcpy(newNode->str, str);
        newNode->next = temp->next;
        temp->next = newNode;
        list->_size++;
    }
}

void slist_removeAt(SinglyList *list, int index)
{
    if (!slist_isEmpty(list)) {
        
        /* Kasus apabila posisinya melebihi batas */
        if (index >= list->_size) {
            slist_popBack(list);
            return;    
        }
        else if (index == 0 || index < 0) {
            slist_popFront(list);
            return;
        }
        
        SListNode *temp = list->_head;
        int _i = 0;
        while (temp->next != NULL && _i < index-1) {
            temp = temp->next;
            _i++;
        }
        SListNode *nextTo = temp->next->next;
        free(temp->next);
        temp->next = nextTo;
        list->_size--;
    }
}

void slist_remove(SinglyList *list, char str[])
{
    if (!slist_isEmpty(list)) {
        SListNode *temp, *prev;
        temp = list->_head;

        if (strcmp(temp->str, str) == 0 ) {
            slist_popFront(list);
            return;
        }
        while (temp != NULL && strcmp(temp->str, str) != 0) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) return;
        prev->next = temp->next;
        free(temp);
        list->_size--;
    }
}

char* slist_front(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        return list->_head->str;
    }
    return 0;
}

char* slist_back(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        SListNode *temp = list->_head;
        while (temp->next != NULL) 
            temp = temp->next;
        return temp->str;
    }
    return 0;
}

char* slist_getAt(SinglyList *list, int index)
{
    if (!slist_isEmpty(list)) {
        SListNode *temp = list->_head;
        int _i = 0;
        while (temp->next != NULL && _i < index) {
            temp = temp->next;
            _i++;
        }
        return temp->str;
    }
    return 0;
}

void move(SinglyList *list, int index){
    if (!slist_isEmpty(list)) {
        SListNode *nextNode = list->_head->next;
        SListNode *currNode = list->_head;

        for(int i = 0; i < index; ++i){
            currNode = nextNode;
            nextNode = nextNode->next;
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

int main(int argc, char const *argv[])
{
    // Buat objek SinglyList
    SinglyList myList;

    // PENTING! Jangan lupa diinisialisasi
    slist_init(&myList);
    
    char perintah[10];
    int count = 0;
    
    while(true){
        scanf("%s", perintah);

        //append = pushback
        if(strcmp(perintah, "append") == 0){
            char temp[51];
            scanf("%s", temp);
            slist_pushBack(&myList, temp);
            ++count;
        }   

        //prepend = pushfront
         if(strcmp(perintah, "prepend") == 0){
             //pushback normal
            char temp[51];
            scanf("%s", temp);
            slist_pushFront(&myList, temp);
            ++count;
        }

        if(strcmp(perintah, "cp") == 0){
            // pushfront normal
            int index, tujuan;
            char *word; // bisa menampung panjang berapapun
            scanf("%d %d", &index, &tujuan);
            // char word[100];
            word = slist_getAt(&myList, index);
            slist_insertAt(&myList, tujuan, word);
            ++count;
        }

        if(strcmp(perintah, "rm") == 0){
            int index;
            scanf("%d", &index);
            if(index < count - 1){
                slist_removeAt(&myList, index);
                --count;
            }
            
        }

        if(strcmp(perintah, "mv") == 0){
            //dapetin index yg mau di copy
            //hapus index nya
            //masukkin di tempat tujuan
            int index, tujuan;
            char *word1; // bisa menampung panjang berapapun
            scanf("%d %d", &index, &tujuan);
            word1 = slist_getAt(&myList, index);
            //remove

            if(index < tujuan){
                slist_insertAt(&myList, tujuan + 1, word1);
                slist_removeAt(&myList, index);
            }

            else if(index > tujuan){
                slist_insertAt(&myList, tujuan, word1);
                slist_removeAt(&myList, index + 1);
            }

            else if(index == tujuan){
                count = count + 0;
            }
            // ++count;
            
            //kalo index = tujuan, jangan ngapain2
            else{
                count += 0;
            }
        }

        //stop = break
        if(strcmp(perintah, "stop") == 0){
            break;
        }
    }
    
    if(count == 0){
        printf("0");
    }
    
    else{
        printf("%d\n", count);
        if(!slist_isEmpty(&myList)){
            while(!slist_isEmpty(&myList)){
            printf("%s\n", slist_front(&myList));
            slist_popFront(&myList);
        }
        }   
   }
    
    
    puts("");
    return 0;
    
}