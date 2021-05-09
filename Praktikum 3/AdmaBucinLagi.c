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

void getStack(AVLNode *root, int value, int *position, int *isTrue){
    if(root == NULL) //jika ternyata root nya NULL, return
        return;

    /*
        jika isTrue nya 0, yang artinya angka yang kita cari sudah ketemu,
        maka return saja, jangan mencari apapun lagi
    */
    if(*isTrue == 0) 
        return;

    /*
        Urutan pencarian nya adalah inorder, namun lakukan inorder dari kanan ke kiri
        Jadi rumus nya => kanan - (posisi + 1) - kiri
    */
    getStack(root->right, value, position, isTrue);

    /*
        jika saat traversing angka ketemu, ubah isTrue jadi 0 
        agar menghitung position nya berhenti
    */
    if(root->data == value) 
        *isTrue = 0;

    /*
        Jika seandainya tidak ketemu, maka tambah position sebanyak 1
    */
    if(*isTrue == 1) 
        *position += 1; 

    getStack(root->left, value, position, isTrue);

}

int main(){
    AVL avlku; 
    avl_init(&avlku); //inisialisasi awal dari AVL

    int testcase; // testcase = berapa banyak testcase yang ingin ditaruh
    scanf("%d", &testcase); // scan berapa banyak testcase nya

    char command[11]; //perintah yang akan dimasukkan (Taro / Cari)
    int input; // angka yang dimasukkan di samping perintah

    int position = 0; // set up awal pencarian posisi dari 0
    int isTrue = 1; // penanda untuk apakah angka yang kita cari ada

     
    for(int i = 0; i < testcase; ++i){
        scanf("%s %d", command, &input); //masukkan perintah dan angka nya
        
        //jika perintah nya Taro atau Cari, maka lakukan hal berikut
        if((strcmp(command, "Taro") == 0) || (strcmp(command, "Cari") == 0)){
            
            //jika perintah nya Taro, masukkan angka input ke dalam AVL
            if(strcmp(command, "Taro") == 0){
                avl_insert(&avlku, input);
            }

            //Jika perintah nya Cari, pertama cek apakah angka yang dicari ada
            else{
                if(!avl_find(&avlku, input)) // jika tidak ada, output kan tidak ada
                    printf("Kasetnya gak ada!\n");
                
                //jika ada, masuk ke getStack
                else{
                    getStack(avlku._root, input, &position, &isTrue);
                    printf("Kasetnya ada di tumpukan ke - %d\n", position + 1); //position + 1, karena mulai nya dari 0
                    
                    //jangan lupa set up kembali position dan isTrue ke kondisi awal
                    position = 0;
                    isTrue = 1;
                }
            }
        }

        //Jika command nya bukan taro atau cari, print seperti di bawah ini
        else{
            printf("AKU TUH BINGUNG HARUS NGAPAIN BEB!\n");
        }
    }

}

