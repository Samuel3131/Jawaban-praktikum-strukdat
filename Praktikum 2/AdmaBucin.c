#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

//MIN dan MAX ini akan berguna untuk mencari nilai max dan min nya
const int MIN = -100;
const int MAX = 10000001;

//Pertama kita dapatkan dahulu code dari github nya
//terdapat modif di struct bstnode, __bst__createNode
//--------------------------------------------------------------
typedef struct bstnode_t {
    int key;
    //tambahkan int level untuk mengetahui level nya nanti
    int level;
    struct bstnode_t \
        *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

/**
 * !!! WARNING UTILITY FUNCTION !!!
 * Recognized by prefix "__bst__"
 * ---------------------------------------------
 * Note that you better never access these functions, 
 * unless you need to modify or you know how these functions work.
 */

//masukkan nilai level nya (default nya 0)
BSTNode* __bst__createNode(int value, int level) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->level = level;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value, int level) {
    if (root == NULL) 
        return __bst__createNode(value, level);

    if (value < root->key)
        root->left = __bst__insert(root->left, value, level);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value, level);
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, int value) {
    while (root != NULL) {
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
        else
            return root;
    }
    return root;
}

BSTNode* __bst__findMinNode(BSTNode *node) {
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    
    return currNode;
}

BSTNode* __bst__remove(BSTNode *root, int value) {
    if (root == NULL) return NULL;

    if (value > root->key) 
        root->right = __bst__remove(root->right, value);
    else if (value < root->key) 
        root->left = __bst__remove(root->left, value);
    else {
        
        if (root->left == NULL) {
            BSTNode *rightChild = root->right;
            free(root);
            return rightChild;
        }
        else if (root->right == NULL) {
            BSTNode *leftChild = root->left;
            free(root);
            return leftChild;
        }

        BSTNode *temp = __bst__findMinNode(root->right);
        root->key     = temp->key;
        root->right   = __bst__remove(root->right, temp->key);
    }
    return root;
}

void __bst__inorder(BSTNode *root) {
    if (root) {
        __bst__inorder(root->left);
        printf("%d ", root->key);
        __bst__inorder(root->right);
    }
}

void __bst__postorder(BSTNode *root) {
    if (root) {
        __bst__postorder(root->left);
        __bst__postorder(root->right);
        printf("%d ", root->key);
    }
}

void __bst__preorder(BSTNode *root) {
    if (root) {
        printf("%d ", root->key);
        __bst__preorder(root->left);
        __bst__preorder(root->right);
    }
}

/**
 * PRIMARY FUNCTION
 * ---------------------------
 * Accessible and safe to use.
 */

void bst_init(BST *bst) {
    bst->_root = NULL;
    bst->_size = 0u;
}

bool bst_isEmpty(BST *bst) {
    return bst->_root == NULL;
}

bool bst_find(BST *bst, int value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}

void bst_insert(BST *bst, int value, int level) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value, level);
        bst->_size++;
    }
}

void bst_remove(BST *bst, int value) {
    if (bst_find(bst, value)) {
        bst->_root = __bst__remove(bst->_root, value);
        bst->_size--;
    }
}

/**
 * Binary search tree traversal
 * - Inorder
 * - Postorder
 * - Preorder
 */

void bst_inorder(BST *bst) {
    __bst__inorder(bst->_root);
}

void bst_postorder(BST *bst) {
    __bst__postorder(bst->_root);
}

void bst_preorder(BST *bst) {
    __bst__preorder(bst->_root);
}
//---------------------------------------

//pertama kita cari 
int findHeight(BSTNode *node){
    if(node == NULL){
        return 0;
    }

    int left = findHeight(node->left);
    int right = findHeight(node->right);

    if(left > right){
        return (left + 1);
    }

    else {
        return (right + 1);
    }
}

int height(BST *bst){
    return findHeight(bst->_root);
    // printf("%d", height);
}
//----------------------------------------


//buat mencari dan memasukkan level dari setiap node nya
void getLevel(BSTNode *node, int level){
    //jika bertemu node = NULL, return
    if(node == NULL){
        return;
    }

    //untuk node pertama alias node paling atas, masukkan level nya
    node->level = level;

/*
    jadi urutan pengerjaan nya adalah
    masukkan level dari node pertama
    saat sudah dimasukkan, rekursi ke node left & right, dan level + 1
    artinya tiap turun ke bawah 1x, level bertambah 1
    masukkan nilai level 2 ke node-> level nya
    ulangi untuk level 3 dst
*/
    getLevel(node->left, level + 1);
    getLevel(node->right, level + 1);
}

//memanggil getLevel dengan struct BST
void bst_getLevel(BST *bst){
    getLevel(bst->_root, 1);
}



//---------------------------------------
//mencari nilai paling kecil dari 2 bilangan
int Min(int a, int b){
    if(a < b){
        return a;
    }

    else{
        return b;
    }
}

//mencari nilai paling besar dari 2 bilangan
int Max(int a, int b){
    if(a > b){
        return a;
    }

    else{
        return b;
    }
}

//Mendapatkan hasil yang diinginkan
//mulai dari paling bawah, dapatkan nilai kecil besar selang seling
int solve(BSTNode *node, int level, bool check){
    //untuk apa node = NULL ini?
    //disinilah kegunaan const int MIN dan MAX digunakan
    //seandainya dalam 1 level horizontal bst itu hanya ada 1 node, otomatis dia akan jadi nilainya
    //namun bila saat memeriksa complete binary tree (bst yang bukan full binary tree), kita harus menghandle nilai null nantinya
    //misal, di dalam 1 level ada 1 2 3 null 4. Pertama cek min(1,4) -> 1. Lalu cek min(2,null)-> bermasalah. 
    //saat cek(2,null) bermasalah. Maka saat bertemu null, buat null itu jadi nilai min atau max. Paksa agar mendapat nilai min/max yg diinginkan
    if(node == NULL){
        if(check == true){
            return MAX; //1e6
        }

        else{
            return MIN; //-100
        }
    }

    //jika sudah berada di level yang diinginkan, return key nya
    if(node->level == level){
        return node->key;
    }

    //mendapatkan nilai dari node left dan rightnya
    int left = solve(node->left, level, check);
    int right = solve(node->right, level, check);

    //jika true, cari nilai min nya
    //jika false, cari nilai max nya
    if(check == true){ 
        return Min(left, right);
    }

    else{
        return Max(left, right);
    }
}

//untuk mendapatkan nilai level per level
void bst_solve(BST *bst, int level){
    bool check = true; //penanda apakah mencari nilai max ato min

    //true = min
    //false = max
    int result;
    // int count = 1;
    for(int i = level; i >= 1; --i){
        //jika check = true, cari nilai min nya
        if(check == true){
            result = solve(bst->_root, i, check);
            printf("%d ", result);
            //saat sudah mendapat nilai min, ubah jadi false
            //jika tidak dirubah ke false, maka nanti akan terus mencari nilai min terus 
            check = false;
        }
        
        //jika saat perulangan check=false, cari nilai max nya
        else{
            result = solve(bst->_root, i, check);
            printf("%d ", result);
            check = true;
        }
    }
    printf("\n");
}


int main(){
    //pertama seperti biasa inisialisasi BST nya
    BST bst;
    bst_init(&bst);

    //query ini berguna untuk memberi tahu jumlah testcase nya
    int query;
    scanf("%d", &query);

    //perulangan di bawah ini untuk memasukkan node ke bst dari i sampai (query - 1)
    for(int i = 0; i < query; ++i){
        //deklarasi number
        int number;

        //masukkan nilai number nya
        scanf("%d", &number);

        //masukkan number ke bst dengan set level nya 0
        bst_insert(&bst, number, 0);
    }


    //bst_preorder(&bst);
    int level = height(&bst);
    //printf("%d", level);

    //dapatkan level nya dari setiap level (lebih jelasnya bisa dilihati di function)
    bst_getLevel(&bst);

    //dapatkan hasil nya (lebih jelasnya bisa dilihati di function)
    bst_solve(&bst, level);
    
}