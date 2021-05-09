#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Struktur Node */

typedef struct stackNode_t {
    int data;
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
void stack_push(Stack *stack, int value);
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

void stack_push(Stack *stack, int value) 
{
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack->_size++;
        newNode->data = value;
        
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
    if (!stack_isEmpty(stack)) 
        return stack->_top->data;
    return 0;
}

unsigned stack_size(Stack *stack) {
    return stack->_size;
}

void tambah(Stack *stack, int num){
    if(!stack_isEmpty(stack)){
        StackNode *temp = stack->_top;
        for(int i = 0; i < stack->_size; ++i){
            temp->data += num;
            temp = temp->next;
        }
    }
}

void kurangkan(Stack *stack, int num){
    if(!stack_isEmpty(stack)){
        StackNode *temp = stack->_top;
        for(int i = 0; i < stack->_size; ++i){
            temp->data -= num;
            temp = temp->next;
        }
    }
}

void kalikan(Stack *stack, int num){
    if(!stack_isEmpty(stack)){
        StackNode *temp = stack->_top;
        for(int i = 0; i < stack->_size; ++i){
            temp->data *= num;
            temp = temp->next;
        }
    }
}


int main(int argc, char const *argv[])
{
    // Buat objek Stack
    Stack myStack;

    // PENTING! Jangan lupa diinisialisasi
    stack_init(&myStack);

    int data;
    scanf("%d", &data);

    char comand[10];
    int number, iteration;
    for(int i = 0; i < data; ++i){
        scanf("%s", comand);

        //tambah
        //print size
        if(strcmp(comand, "add") == 0){
            scanf("%d %d", &number, &iteration);
            for(int j = 0; j < iteration; ++j){
                stack_push(&myStack, number);
            }
            printf("%d\n", stack_size(&myStack));
        }

        //hapus sebanyak iterasi, sebelum itu ambil data paling atas
        if(strcmp(comand, "del") == 0){
            scanf("%d", &iteration);
            printf("%d\n", stack_top(&myStack));
            for(int j = 0; j < iteration; ++j){
                stack_pop(&myStack);
            }
        }
        
        //tambah
        if(strcmp(comand, "adx") == 0){
            scanf("%d", &number);
            tambah(&myStack, number);
        }

        //kurangkan
        if(strcmp(comand, "dex") == 0){
            scanf("%d", &number);
            kurangkan(&myStack, number);
        }

        //kalikan
        if(strcmp(comand, "mux") == 0){
            scanf("%d", &number);
            kalikan(&myStack, number);
        }

    }


    // while(!stack_isEmpty(&myStack)){
    //     printf("%d\n", stack_top(&myStack));
    //     stack_pop(&myStack);
    // }
    

        
    return 0;
}