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
    int count = 0;
    if (root) {
        __bst__postorder(root->left);
        __bst__postorder(root->right);
        
        printf("%d ", root->key);
    }
}

void __bst__preorder(BSTNode *root) {
    int count = 0;
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

void bst_insert(BST *bst, int value) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value);
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
//--------------------------------------------------------------

//fungsi mencari index dalam urutan postorder
void bst_find_postorder(BSTNode *root, int value, int *position, int *isTrue){
    //position dan isTrue nya berupa pass by reference agar rekursi nya hanya berfokus pada node nya saja
    //dan jika kita gunakan rekursi untuk position dan istrue nya, akan sulit impelementasi nya, jadi gunakan pass reference saja
    //saat fungsi ini sudah selesai, di fungsi main position dan isTrue akan direset kembali nilainya

    //jika root nya bertemu null, return
    if(root == NULL) {
        return;
    }

    //jika istrue = 0, artinya value yg diinginkan sudah didapat, dan return saja
    if(*isTrue == 0){
        return;
    }

    //lakukan rekursi ke node left dan right nya sampai value nya = root -> key nya
    bst_find_postorder(root->left, value, position, isTrue);
    bst_find_postorder(root->right, value, position, isTrue);
    
    //jika isTrue = 1, artinya node yang dicari belum bertemu
    //maka posisi nya berarti akan bertambah 1 alias position++
    if(*isTrue == 1){
        *position += 1;
    }

    //jika node yang dicari index nya ketemu, berarti ubah isTrue jadi 0
    //yang artinya kita akan melakukan return terus menerus nantinya
    if(root->key == value) {
        *isTrue = 0;
    }
    
    
}




int main()
{
    //it = untuk mencari berapa iterasi yang dibutuhkan untuk insert bst nya
    //testcase = mencari tahu brapa perintah yang akan dipakai (perintah 1 atau 2 muncul brpa kali)
    int testCase, it;
    scanf("%d %d", &it, &testCase);

    //const int arr ini tidak jadi dipakai
    const int arr = testCase;
    
    //Seperti biasa kita inisialisasi BST set nya
    BST set;
    bst_init(&set);

    //isTrue ini untuk mengecek saat perintah = 2, apakah value nya sudah ketemu di bst
    //position ini untuk mengecek sebuah value ada di index ke brapa 
    int isTrue = 1;
    int position = 0;

    //masukkan nilai yang akan diubah menjadi bst nya
    for(int i = 0 ; i < it; ++i){
        //input = memasukkan nilai yang akan di insert ke bst nya
        int input;
        scanf("%d", &input);
        bst_insert(&set, input);
    }

    //masuk ke perintah nya
    for(int i = 0; i < testCase; ++i){
        //input = untuk memasukkan perintah (1 atau 2)
        //input2 = memasukkan value yang ingin dicari index / dihapus
        int input, input2;
        scanf("%d", &input);

        //jika input = 1, artinya kita akan menghapus 1 node
        if(input == 1){
            //scan node yang ingin dihapus
            scanf("%d", &input2);

            //jika node nya ada di bst, hapus dan print 'sudah terhapus'
            if(bst_find(&set, input2)){
                //pertama remove yang ingin diremove
                bst_remove(&set, input2);

                //print hasil
                printf("%d sudah terhapus\n", input2);
            }

            //jika ternyata node nya tidak ada, print 'tidak ada'
            else{
                printf("%d tidak ada\n", input2);
            }
        }

        //jika input = 2, kita akan mencari posisi sebuah node jika dalam bentuk postorder
        else{
            //masukkan node yang ingin dicari
            scanf("%d", &input2);

            //jika node nya ada di bst, maka lakukan pencarian index
            if(bst_find(&set, input2)){
                
                //untuk penjelasan function ini bisa langsung ke function bst_find_postorder
                bst_find_postorder(set._root, input2, &position, &isTrue);
                
                //print indexnya 
                printf("%d ada di index ke-%d\n", input2, position);
                
                //setelah kita menjalankan bst_find_postorder, kita harus reset kembali nilai position dan isTrue nya
                //karena kita pass by reference, otomatis nantinya nilai position dan isTrue nya akan berubah nantinya
                position = 0;
                isTrue = 1;
            }

            //jika node nya tidak ada, berarti print 'tidak ada'
            else{
                printf("%d tidak ada\n", input2);
            }

            
        }


    }
    
}