#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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

int max(int a, int b){
    if(a > b){
        return a;
    }

    else{
        return b;
    }
}

int min(int a, int b){
    if(a < b){
        return a;
    }

    else{
        return b;
    }
}


int main(int argc, char const *argv[])
{
    // Buat objek Stack
    Stack PiringKotor;
    Stack Depe;
    Stack temanDepe;

    // PENTING! Jangan lupa diinisialisasi
    stack_init(&PiringKotor);
    stack_init(&Depe);
    stack_init(&temanDepe);

    int banyakPiring, jumlahTugas;
    scanf("%d", &banyakPiring);
    //masukkan piring dari 1 - N
    for(int i = banyakPiring; i >= 1; --i){
        stack_push(&PiringKotor, i);
    }

    scanf("%d", &jumlahTugas);
    int orang, piring;

    //masukkan tugas
    for(int i = 0; i < jumlahTugas; ++i){
        scanf("%d %d", &orang, &piring);
        
        //ambil piring sebanyak m kali dari piringkotor, lalu taro di tempat depe
        if(orang == 1){
            for(int i = 0; i < piring; ++i){
                int temp = stack_top(&PiringKotor);
                if(!stack_isEmpty(&PiringKotor)){
                    stack_push(&Depe, temp);
                    stack_pop(&PiringKotor);
                }
            }
        }

        //ambil piring dari depe, taro di tempat nya temenDepe
        if(orang == 2){
            for(int i = 0; i < piring; ++i){
                if(!stack_isEmpty(&Depe)){
                    int temp = stack_top(&Depe);
                    stack_push(&temanDepe, temp);
                    stack_pop(&Depe);
                }
            }
        }
    }

    int size,size2,size3;
    size = stack_size(&PiringKotor);
    size2 = stack_size(&Depe);
    size3 = stack_size(&temanDepe);
   
    int sizeArray[3] = {size, size2, size3};
    int length = sizeof(sizeArray) / sizeof(sizeArray[0]);
    // printf("%d", length);

    int maxFirst = max(size, size2);
    int FinalMax = max(maxFirst, size3);

    for(int i = 0; i < FinalMax; ++i){
        //printf("%d\n", i);
        for(int arr = 0; arr < length; ++arr){
            // printf("%d\n", arr)
            if((arr != 2)){
                //printf("%d\n", arr);
                if(sizeArray[arr] != 0){
                    if(arr == 0){
                        printf("%d\t", stack_top(&PiringKotor));
                        stack_pop(&PiringKotor);
                    }

                    if(arr == 1){
                        printf("%d\t", stack_top(&Depe));
                        stack_pop(&Depe);
                    }
                }

                if(sizeArray[arr] == 0 && i == 0){
                    printf("-\t");
                }

                if(sizeArray[arr] == 0 && (i != 0)){
                    printf("\t");
                }

                if(sizeArray[arr] != 0){
                    sizeArray[arr]--;
                }

            }

            else{
                if(sizeArray[arr] != 0){
                    printf("%d\n", stack_top(&temanDepe));
                    stack_pop(&temanDepe);
                }

                if(sizeArray[arr] == 0 && (i == 0)){
                    printf("-\n");
                }

                //penyebab ga bener bener
                if(sizeArray[arr] == 0 && (i != 0)){
                    printf("\n");
                }

                if(sizeArray[arr] != 0){
                    sizeArray[arr]--;
                }
            }

        }
    }
    
}