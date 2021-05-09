#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


//Pertama kita dapatkan dahulu code dari github nya
//--------------------------------------------------------------
typedef struct bstnode_t {
    int key;
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

BSTNode* __bst__createNode(int value) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value) {
    if (root == NULL) 
        return __bst__createNode(value);

    if (value < root->key)
        root->left = __bst__insert(root->left, value);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value);
    
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

void bst_insert(BST *bst, int value) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}

void __bst__preorder(BSTNode *root) {
    if (root) {
        printf("%d ", root->key);
        __bst__preorder(root->left);
        __bst__preorder(root->right);
    }
}

void bst_preorder(BST *bst) {
    __bst__preorder(bst->_root);
}

//--------------------------------------------------------------

//ini fungsi untuk mencari buyut nya
BSTNode *search(BSTNode *head, int input, int input2){

/*
Maksud dari kedua if statement ini adalah, jika kita punya tree seperti di soal
        6
    /      \
   3        9
  / \      / \
1    5    7  11
 
case #1: jika input nya 1 dan 5, maka buyutnya adalah 3
cara kerjanya adalah kita cek node paling atas, apakah 1 < 6, betul. Apakah 5 < 6 betul. Maka ($1) akan berjalan dan memeriksa bagian kiri
apakah 1 < 3, benar. Apakah 5 < 3, salah. Maka nantinya kita return head terakhir, yaitu 3

case #2: jika inputnya 1 dan 3, buyut nya 3
cek node paling atas. Apakah 1 < 6, benar. Apakah 3 < 6, benar, maka ($1) dijalankan 
apakah 1 < 3, benar. Apakah 3 < 3, tidak. Maka return head terakhir, yaitu 3

case #3: jika input 1 dan 11, buyut nya 6
cek node paling atas, apakah 1 < 6, benar. Apakah 11 < 6, tidak. Maka langsung saja return 6
*/
    //$1
    if(input < head->key && input2 < head->key){
        return search(head->left, input, input2);
    }

    //$2
    else if(input > head->key && input2 > head->key){
        return search(head->right, input, input2);
    }

    return head;
}

//melakukan fungsi result melalui struct BST
void solve(BST *bst, int node1, int node2){
    BSTNode *solution = search(bst->_root, node1, node2);
    printf("%d\n", solution->key);
}

int main(){
    //inisialisasi BST set nya
    BST set;
    bst_init(&set);

    //masukkan query/jumlah perintah yang akan dijalankan
    int query;
    scanf("%d", &query);

    //jalankan perulangan sebanyak query
    for(int i = 0; i < query; ++i){
        //deklarasi command, dan scanf command nya dalam 1 atau 2
        int command;
        scanf("%d", &command);

        //jika command = 1, maka scan data yang akan dimasukkan ke dalam bst 
        if(command == 1){
            int data;
            scanf("%d", &data);
            bst_insert(&set, data);
        }

        //jika command = 2, maka akan memeriksa buyut dari sebuah bst
        else if(command == 2){
            int node1, node2;
            scanf("%d %d", &node1, &node2);

            //gunakan bool untuk memeriksa apakah node yang ingin diperiksa itu ada dalam bst
            bool forNode1 = bst_find(&set, node1);
            bool forNode2 = bst_find(&set, node2);

            //jika node yang ingin dicari itu ada di dalam bst nya, program pencarian buyut dapat dijalankan
            //untuk melihat penjelasan pencarian pada function (solve), bisa ke function (search)
            if(forNode1 && forNode2){
                solve(&set, node1, node2);
            }

            //jika data nya tidak ada, print data tidak valid
            else {
                printf("Data tidak valid.\n");
            }
            
        }

        //jika command nya bukan 1 atau 2, print tidak valid
        else {
           printf("Data tidak valid.\n");
        }
    }
}