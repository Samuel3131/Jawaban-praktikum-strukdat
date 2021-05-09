#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//pertama kita copy code dari github nya
//terdapat modif penambahan money pada beberapa function di avl nya
//---------------------------------------

typedef struct AVLNode_t
{
    int data;
    int money; //modif
    struct AVLNode_t *left,*right;
    int height;
}AVLNode;

typedef struct AVL_t
{
    AVLNode *_root;
    unsigned int _size;
}AVL;

AVLNode* _avl_createNode(int value, int money) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->money = money; //modif
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

AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value, int money) {
    
    if(node==NULL) // udah mencapai leaf
        return _avl_createNode(value, money); //modif
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value,money); //modif
    else if(value > node->data)
        node->right = _insert_AVL(avl,node->right,value,money); //modif
    
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

void avl_insert(AVL *avl,int value, int money){
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,value,money); //modif
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

//gunakan pass reference agar nilai sum nya (total) bisa kita ubah secara live dan mudah
void total(AVLNode *root, int *total, int cost){
    *total += root->money * cost;
}

int main(){
    AVL avlku;
    avl_init(&avlku); //inisialisasi awal dari AVL
    
    int check = 1; //variabel untuk mengecek apakah nilai dari ID nya berurut atau tidak
    int ID, money; //ID = memasukkan nilai ID, money = memasukkan nilai dari produk nya

    int loopCheck = 1; // sejenis flag untuk menandai apakah ID nya berurut atau tidak
    //int arr[10000];

    while(1){
        scanf("%d %d", &ID, &money); //scan nilai dari ID dan harga nya

        //jika ID dan money 0, artinya kita harus menyelesaikan loop 
        if(ID == 0 && money == 0) break;
        
        //setiap kali ID nya berurutan, masukkan nilai dari ID dan money ke avl
        else if(ID == check){
            avl_insert(&avlku, ID, money);
        }

        //jika ID nya tidak berurut, atau artinya ID nya tidak sama dengan check, break
        else if(ID != check) {
            printf("ID harus urut");
            loopCheck = 0; //set loopcheck jadi 0, yang artinya hanya akan print ID harus urut, dan tidak print apa2 lagi
            break;
        }
        check++; //jika ID nya sama dengan check, maka check++ untuk mengecek apakah ID nya urut atau tidak
    }

    int sum = 0; //sum = menghitung total keuntungan

    //buyID = ID yang ingin dibeli
    //cost = berapa banyak ID tersebut ingin dibeli
    int buyID, cost;

    //jika loopcheck 1, artinya ID nya terurut
    while(loopCheck == 1){
        scanf("%d %d", &cost, &buyID); //scan cost dan ID yang ingin dibeli

        //jika keduanya bernilai 0, maka selesaikan loop 
        if(buyID == 0 && cost == 0) break;

        //jika saat di check, ID nya ada di avl, maka tambahkan keuntungan (sum) di function total
        else if(avl_find(&avlku, buyID)){
            AVLNode *temp = _search(avlku._root, buyID);
            total(temp, &sum, cost); //masuk ke function total di atas
        }

        //jika ID yang ingin dibeli tidak tersedia, print maaf tidak tersedia
        else if(!avl_find(&avlku, buyID)){
            printf("Maaf barang tidak tersedia\n");
        }
    }

    //jika loopcheck 1, alias ID berurutan, print keuntungan nya
    if(loopCheck == 1)
        printf("%d", sum);


}