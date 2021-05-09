#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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
        printf("%lld ", root->data);
        preorder(root->right);
    }
}
//---------------------------------------

//fungsi untuk mendapat posisi
void getInorder(AVLNode *root, int value, int *position, int *isTrue){
    //rumus nya untuk mencari posisi adalah inorder
    //kiri - cek - kanan
    
    if(root == NULL) return; //jika node nya NULL, return

    //jika isTrue nya 0, alias value nya sudah ketemu, maka return, tidak perlu lakukan apa2 lagi
    if(*isTrue == 0) return; 

    //lakukan inorder seperti biasa
    getInorder(root->left, value, position, isTrue);
    
    //jika saat rekursi data ketemu, isTrue nya ubah jadi 0, jadi next rekursi langsung return
    if(root->data == value) *isTrue = 0;

    //jika istrue nya tidak 0, maka position++
    if(*isTrue == 1) *position += 1;
    getInorder(root->right, value, position, isTrue);

}

//fungsi untuk mendapat sum 
void getSum(AVLNode *root, int value, int *sum, int *isTrue){
    if(root == NULL) return; //jika node nya NULL atau isTrue nya 0, return
    if(*isTrue == 0) return;

    //gunakan prinsip inorder untuk mendapat sum nya
    getSum(root->left, value, sum, isTrue);

    //jika saat rekursi value ketemu, ubah isTrue jadi 0, jadi next rekursi langsung return
    if(root->data == value) *isTrue = 0;

    //jika istrue nya tidak 0, maka sum nya tambah kan dengan data yang ditemui
    if(*isTrue == 1) *sum += root->data; 

    getSum(root->right, value, sum, isTrue);
}

int main(){
    AVL avlku;
    avl_init(&avlku); //inisialisasi awal dari AVL

    int testcase; // testcase = berapa banyak testcase yang ingin ditaruh
    scanf("%d", &testcase); // scan berapa banyak testcase nya
 
    //command = bagaimana sebuah angka (input) akan dijalankan
    //input = angka yang ingin dilakukan sesuatu
    int command, input; 
    
    //sum = menghitung jumlah setiap node yang dimasukkan
    int sum = 0;

    //position = mencari posisi sebuah node
    //isTrue_position = penanda dalam mencari posisi di function nanti
    //isTrue_sum = penanda mencari jumlah di function nanti
    int position = 1;
    int isTrue_sum = 1;
    int isTrue_position = 1;

    for(int i = 0; i < testcase; ++i){
        scanf("%d %d", &command, &input); //masukkan command dan input angkanya 

        if(command == 1){
            avl_insert(&avlku, input); //jika command nya 1, masukkan input ke avl
        }

        else if(command == 2){
            if(!avl_find(&avlku, input)) //jika saat command 2, input tidak ada di avl, print ga ketemu
                printf("Ga Ketemu :(\n");
            
            else if(avl_find(&avlku, input)){
                getSum(avlku._root, input, &sum, &isTrue_sum); //dapatkan sum nya di function getSum

                //mengapa sum + input ? Karena di function getSum, saat input nya ketemu, maka akan return nilai sum nya
                //otomatis, angka yang kita periksa tidak ikut ditambahkan dalam sum
                //itulah mengapa jadi sum + input, karena sum sendiri tidak menambahkan nilai input di getSum 
                printf("Jumlahnya: %d\n", sum + input);

                //jangan lupa reset sum ke 0, dan isTrue_sum = 1
                sum = 0;
                isTrue_sum = 1;

                //dapatkan posisi nya di function getInorder
                getInorder(avlku._root, input, &position, &isTrue_position);
                printf("Di urutan: %d\n", position); //print position nya

                //jangan lupa juga reset position dan isTrue nya ke 1
                position = 1;
                isTrue_position = 1;
            }
        }

        //jika command nya bukan 1 atau 2, print sperti di bawah
        else
            printf("Ga Tau Harus Ngapain :\"(\n");
    }

    

}


        