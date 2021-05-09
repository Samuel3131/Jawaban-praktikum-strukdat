#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/* Struktur Node */

typedef struct pqueueNode_t {
    int jamIN;
    int jamOUT;
    struct pqueueNode_t *next;
} PQueueNode;

/* Struktur ADT PriorityQueue menggunakan Linked List */

// Prioritas default: nilai minimum
typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;

/* Function prototype */

void pqueue_init(PriorityQueue *pqueue);
bool pqueue_isEmpty(PriorityQueue *pqueue);
void pqueue_push(PriorityQueue *pqueue, int jam1, int jam2);
void pqueue_pop(PriorityQueue *pqueue);
int  pqueue_top(PriorityQueue *pqueue);

/* Function definition below */

void pqueue_init(PriorityQueue *pqueue)
{
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

void pqueue_push(PriorityQueue *pqueue, int jam1, int jam2)
{
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = \
        (PQueueNode*) malloc (sizeof(PQueueNode));
    newNode->jamIN = jam1;
    newNode->jamOUT = jam2;
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        return;
    }

    if (jam1 < pqueue->_top->jamIN) {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else {
        while ( temp->next != NULL && 
                temp->next->jamIN < jam1)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void pqueue_pop(PriorityQueue *pqueue)
{
    if (!pqueue_isEmpty(pqueue)) {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        free(temp);
    }
}

int pqueue_top(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->jamIN;
    else return 0;
}

int pqueue_anotherTop(PriorityQueue *pqueue){
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->jamOUT;
    else return 0;
}

int main(int argc, char const *argv[])
{
    // Buat objek PriorityQueue
    PriorityQueue myPque;

    // PENTING! Jangan lupa diinisialisasi
    pqueue_init(&myPque);

    int data;
    scanf("%d", &data);

    int jamPokemon, kapasitas;
    int jamMasuk, jamKeluar;
    
    for(int i = 0; i < data; ++i){
        scanf("%d %d", &jamPokemon, &kapasitas);
        int data2;
        scanf("%d", &data2);

        for(int i = 0; i < data2; ++i){
            scanf("%d %d", &jamMasuk, &jamKeluar);
            pqueue_push(&myPque, jamMasuk, jamKeluar);
        }

        //masuk = "Pika Pika!"
        //ga ada slot = "Pika Zzz"
        int count = 1;
       
    }

    

    printf("\n\n");
     while (!pqueue_isEmpty(&myPque)) {
        printf("%d %d\n", pqueue_top(&myPque), pqueue_anotherTop(&myPque));
        pqueue_pop(&myPque);
    }

 



    puts("");
    return 0;
}