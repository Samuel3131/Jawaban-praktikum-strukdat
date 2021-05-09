#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//pertama kita copy code dari github nya
//---------------------------------------
typedef struct AVLNode_t
{
    int data;
    struct AVLNode_t *left,*right;
    int height;
}AVLNode;

typedef struct AVL_t
{
    AVLNode *_root;
    unsigned int _size;
}AVL;

AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _search(AVLNode *root, int value) {
    while (root != NULL) {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else
            return root;
    }
    return root;
}

int _getHeight(AVLNode* node){
    if(node==NULL)
        return 0; 
    return node->height;
}

int _max(int a,int b){
    return (a > b)? a : b;
}

AVLNode* _rightRotate(AVLNode* pivotNode) {

    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftRotate(AVLNode* pivotNode) {

    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftCaseRotate(AVLNode* node){
    return _rightRotate(node);
}

AVLNode* _rightCaseRotate(AVLNode* node){
    return _leftRotate(node);
}

AVLNode* _leftRightCaseRotate(AVLNode* node){
    node->left=_leftRotate(node->left);
    return _rightRotate(node);
}

AVLNode* _rightLeftCaseRotate(AVLNode* node){
    node->right=_rightRotate(node->right);
    return _leftRotate(node);
}

int _getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value) {
    
    if(node==NULL) // udah mencapai leaf
        return _avl_createNode(value);
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value);
    else if(value > node->data)
    	node->right = _insert_AVL(avl,node->right,value);
    
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

    int balanceFactor=_getBalanceFactor(node);
    
    if(balanceFactor > 1 && value < node->left->data) // skewed kiri (left-left case)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value > node->left->data) // 
		return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value > node->right->data)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value < node->right->data)
        return _rightLeftCaseRotate(node);
    
    return node;
}

AVLNode* _findMinNode(AVLNode *node) {
    AVLNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    return currNode;
}

AVLNode* _remove_AVL(AVLNode* node,int value){
    if(node==NULL)
        return node;
    if(value > node->data)
    	node->right=_remove_AVL(node->right,value);
    else if(value < node->data)
    	node->left=_remove_AVL(node->left,value);
    else{
        AVLNode *temp;
        if((node->left==NULL)||(node->right==NULL)){
            temp=NULL;
            if(node->left==NULL) temp=node->right;  
            else if(node->right==NULL) temp=node->left;
            
            if(temp==NULL){
                temp=node;
                node=NULL;
            }
            else
                *node=*temp;   
            
            free(temp);
        }
        else{
            temp = _findMinNode(node->right);
            node->data=temp->data;
            node->right=_remove_AVL(node->right,temp->data);
        }    
    }

	if(node==NULL) return node;
    
    node->height=_max(_getHeight(node->left),_getHeight(node->right))+1;

    int balanceFactor= _getBalanceFactor(node);
    
    if(balanceFactor>1 && _getBalanceFactor(node->left)>=0) 
        return _leftCaseRotate(node);

    if(balanceFactor>1 && _getBalanceFactor(node->left)<0) 
        return _leftRightCaseRotate(node);
  
    if(balanceFactor < -1 && _getBalanceFactor(node->right)<=0) 
        return _rightCaseRotate(node);

    if(balanceFactor < -1 && _getBalanceFactor(node->right)>0) 
        return _rightLeftCaseRotate(node);
    
    return node;
}

void avl_init(AVL *avl) {
    avl->_root = NULL;
    avl->_size = 0u;
}

bool avl_isEmpty(AVL *avl) {
    return avl->_root == NULL;
}

bool avl_find(AVL *avl, int value) {
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->data == value)
        return true;
    else
        return false;
}

void avl_insert(AVL *avl,int value){
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }

}

void avl_remove(AVL *avl,int value){
    if(avl_find(avl,value)){
        avl->_root=_remove_AVL(avl->_root,value);
        avl->_size--;
    }

}

void preorder(AVLNode *root) {
    if (root) {
        preorder(root->left);
        printf("%d ", root->data);
        preorder(root->right);
    }
}
//---------------------------------------

//buat lah simple doubly linked list
typedef struct deque{
    int data;
    struct deque *prev;
    struct deque *next;
}DoublyList;

//function insert linked list nya
DoublyList *insert(int key){
    DoublyList *new = (DoublyList*) malloc(sizeof(DoublyList));
    new->data = key;
    new->prev = NULL;   
    new->next = NULL;
    return new;
}

//initialize dari linked list nya
DoublyList *initialize(DoublyList *root){
    DoublyList *temp = (DoublyList*) malloc(sizeof(DoublyList));
    temp->data = 0;
    temp->next = temp->prev = NULL;
    return temp;
}

void vertical(AVLNode *root, DoublyList *total){
    //ini adalah modif dari preorder
    //artinya cara kerja vertikal ini adalah = kerjakan - left - right
    
    //tambahkan nilai dari root ke linkedlist data
    total->data += root->data;

    //tujuan if ini untuk mencari nilai vertical dari bagian kiri
    //jika total->prev nya null, inisialisasi dulu
    if(root->left != NULL){
        if(total->prev == NULL){
            total->prev = initialize(total);
            total->prev->next = total;
        }
        //karena ke kiri, lakukan rekursi ke kiri, dan tentunya prev nya juga harus digeser
        vertical(root->left, total->prev);
    }

    //tujuan if ini untuk mencari nilai vertical dari bagian kanan 
    //jika total->prev nya null, inisialisasi dulu
    if(root->right != NULL){    
        if(total->next == NULL){
            total->next = initialize(total);
            total->next->prev = total;
        }
        //karena ke kanan, lakukan rekursi ke kanan, dan tentunya next nya juga harus digeser
        vertical(root->right, total->next);
    }
}

//fungsi untuk print vertical nya
void printSum(AVLNode *root){
    DoublyList *sum = initialize(sum); //pertama kita init dulu DoublyList sum nya 

    //masuk ke function vertical untuk mencari nilai vertical nya masing masing
    vertical(root, sum);

    //geser sum->prev sampai nantinya bertemu NULL
    while(sum->prev != NULL)
        sum = sum->prev;
    
    //print vertical nya seperti biasa
    while(sum != NULL){
        printf("%d ", sum->data);
        sum = sum->next;
    }
}

int main(){
    AVL avlku;
    avl_init(&avlku); //inisialisasi awal dari AVL

    char command[11]; //command = memasukkan insert / tebak nantinya

    //testcase = jumlah testcase yang akan dimasukkan
    //input = angka yang berdampingan dengan command
    int testcase, input;
    scanf("%d", &testcase);
    
    for(int i = 0; i < testcase; ++i){
        scanf("%s", command); //scan command nya


        //jika insert, maka masukkan input ke dalam avl
        if(strcmp(command, "insert") == 0){
            scanf("%d", &input);
            avl_insert(&avlku, input);
        }

        //jika tebak, maka cari vertikal nya
        else if(strcmp(command, "tebak") == 0){
            printSum(avlku._root);
            printf("\n");
        }
    }

}