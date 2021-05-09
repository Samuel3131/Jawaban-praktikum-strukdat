#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//------------------------------------------STACK--------------------------------------------------------------

/* Struktur Node */

typedef struct stackNode_t {
    int ID;
    int pesananToko1;
    struct stackNode_t *next;
} StackNode;

/* Struktur ADT Stack */

typedef struct stack_t {
    StackNode *_top;
    unsigned _size;
} Stack;

/* Function prototype */

void stack_init(Stack *stack);
bool stack_isEmpty(Stack *stack);
void stack_push(Stack *stack, int ID, int pesanToko1);
void stack_pop(Stack *stack);
int stack_top(Stack *stack);
unsigned stack_size(Stack *stack);

/* Function definition below */

void stack_init(Stack *stack) 
{
    stack->_size = 0;
    stack->_top = NULL;
}

bool stack_isEmpty(Stack *stack) {
    return (stack->_top == NULL);
}

void stack_push(Stack *stack, int ID, int pesanToko1) 
{
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack->_size++;
        newNode->ID = ID;
        newNode->pesananToko1 = pesanToko1;
        
        if (stack_isEmpty(stack)) newNode->next = NULL;
        else newNode->next = stack->_top;

        stack->_top = newNode;
    }
}

void stack_pop(Stack *stack) 
{
    if (!stack_isEmpty(stack)) {
        StackNode *temp = stack->_top;
        stack->_top = stack->_top->next;
        free(temp);
        stack->_size--;
    }
}

int stack_top(Stack *stack) 
{
    if (!stack_isEmpty(stack)) {
        return stack->_top->ID;
    }
    return 0;
}

int stack_pesanan(Stack *stack) 
{
    if (!stack_isEmpty(stack)) {
        return stack->_top->pesananToko1;
    }
    return 0;
}

unsigned stack_size(Stack *stack) {
    return stack->_size;
}

int untung1(Stack *stack){
    int count = 0;
    if(!stack_isEmpty(stack)){
        StackNode *temp = stack->_top;
        for(int i = 0; i < stack->_size; ++i){
            count = count + temp->pesananToko1;
            temp = temp->next;
        }
    }
    return count;
}


//------------------------------------------QUEUE--------------------------------------------------------------

/* Struktur Node */

typedef struct queueNode_t {
    int ID;
    int pesananToko2;
    struct queueNode_t *next;
} QueueNode;

/* Struktur ADT Queue */

typedef struct queue_t {
    QueueNode   *_front, 
                *_rear;
    unsigned _size;
} Queue;

/* Function prototype */

void queue_init(Queue *queue);
bool queue_isEmpty(Queue *queue);
void queue_push(Queue *queue, int ID, int pesananToko2);
void queue_pop(Queue *queue);
int  queue_front(Queue *queue);
int  queue_size(Queue *queue);

/* Function definition below */

void queue_init(Queue *queue)
{
    queue->_size = 0;
    queue->_front = NULL;
    queue->_rear = NULL;
}

bool queue_isEmpty(Queue *queue) {
    return (queue->_front == NULL && queue->_rear == NULL);
}

void queue_push(Queue *queue, int ID, int pesanToko2)
{
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (newNode) {
        queue->_size++;
        newNode->ID = ID;
        newNode->pesananToko2 = pesanToko2;
        newNode->next = NULL;
        
        if (queue_isEmpty(queue))                 
            queue->_front = queue->_rear = newNode;
        else {
            queue->_rear->next = newNode;
            queue->_rear = newNode;
        }
    }
}

void queue_pop(Queue *queue)
{
    if (!queue_isEmpty(queue)) {
        QueueNode *temp = queue->_front;
        queue->_front = queue->_front->next;
        free(temp);
        
        if (queue->_front == NULL)
            queue->_rear = NULL;
        queue->_size--;
    }
}

int queue_front(Queue *queue)
{
    if (!queue_isEmpty(queue)) {
        return (queue->_front->ID);
    }
    return (int)0;
}

int queue_pesanan(Queue *queue)
{
    if (!queue_isEmpty(queue)) {
        return (queue->_front->pesananToko2);
    }
    return (int)0;
}

int queue_size(Queue *queue) {
    return queue->_size;
}

int untung2(Queue *queue){
    int count = 0;
    if(!queue_isEmpty(queue)){
        QueueNode *temp = queue->_front;
        for(int i = 0; i < queue->_size; ++i){
            count = count + temp->pesananToko2;
            temp = temp->next;
        }
    }
    return count;
}

int main(){
    Stack toko1;
    stack_init(&toko1);

    Queue toko2;
    queue_init(&toko2);

    char command[10];
    int now = 2;

    while(true){
        scanf("%s", command);

        if(strcmp(command, "PESAN") == 0){
            int id, pesanan;
            scanf("%d %d", &id, &pesanan);
            if(now == 2){
                queue_push(&toko2, id, pesanan);
            }

            if(now == 1){
                stack_push(&toko1, id, pesanan);
            }
        }

        if(strcmp(command, "TUKAR") == 0){
            if(now == 1){
                now = 2;
            }

            else{
                now = 1;
            }
        }

        if(strcmp(command, "CURI") == 0){
            if(now == 2){
                if(queue_isEmpty(&toko2)){
                    printf("TOKO 2 KOSONG\n");
                }

                else{
                    queue_pop(&toko2);
                }
            }

            if(now == 1){
                if(stack_isEmpty(&toko1)){
                    printf("TOKO 1 KOSONG\n");
                }

                else{
                    stack_pop(&toko1);
                }
            }
        }

        if(strcmp(command, "TUTUP") == 0){
            break;
        }
    }

    int untungToko1 = untung1(&toko1);
    int untungToko2 = untung2(&toko2);

    if(stack_isEmpty(&toko1)){
        printf("TOKO 1 :\n");
        printf("TOKO 1 SEPI :(\n");
        printf("TOKO 1 UNTUNG : %d\n", untungToko1);
    }

    else{
        printf("TOKO 1 :\n");
        while(!stack_isEmpty(&toko1)){
            printf("%d %d\n", stack_top(&toko1), stack_pesanan(&toko1));
            stack_pop(&toko1);
        }
        printf("TOKO 1 UNTUNG : %d\n", untungToko1);
    }

    if(queue_isEmpty(&toko2)){
        printf("TOKO 2 :\n");
        printf("TOKO 2 SEPI :(\n");
        printf("TOKO 2 UNTUNG : %d\n", untungToko2);
    }

    else{
        printf("TOKO 2 :\n");
        while(!queue_isEmpty(&toko2)){
            printf("%d %d\n", queue_front(&toko2), queue_pesanan(&toko2));
            queue_pop(&toko2);
        }
        printf("TOKO 2 UNTUNG : %d", untungToko2);
    }
    

}