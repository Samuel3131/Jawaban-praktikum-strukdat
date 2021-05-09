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



BSTNode* _bst_createNode(int value){
    BSTNode* newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* _bst_insert(BSTNode *root, int value) {
    if (root == NULL) 
        return _bst_createNode(value);

    if (value < root->key)
        root->left = _bst_insert(root->left, value);
    else if (value > root->key)
        root->right = _bst_insert(root->right, value);
    
    return root;
}

BSTNode* _bst_search(BSTNode *root, int value) {
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

BSTNode* _bst_findMinNode(BSTNode *node) {
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    
    return currNode;
}

BSTNode* _bst_remove(BSTNode *root, int value) {
    if (root == NULL) return NULL;

    if (value > root->key) 
        root->right = _bst_remove(root->right, value);
    else if (value < root->key) 
        root->left = _bst_remove(root->left, value);
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

        BSTNode *temp = _bst_findMinNode(root->right);
        root->key     = temp->key;
        root->right   = _bst_remove(root->right, temp->key);
    }
    return root;
}

void __bst__inorder(BSTNode *root) {
    if (root) {
        _bst_inorder(root->left);
        printf("%d ", root->key);
        _bst_inorder(root->right);
    }
}

void __bst__postorder(BSTNode *root) {
    if (root) {
        _bst_postorder(root->left);
        _bst_postorder(root->right);
        printf("%d ", root->key);
    }
}

void __bst__preorder(BSTNode *root) {
    if (root) {
        printf("%d ", root->key);
        _bst_preorder(root->left);
        _bst_preorder(root->right);
    }
}
//--------------------------------------------------------------

//fungsi untuk mendapat level masing masing node
//namun tidak jadi dipakai
int height(BSTNode *root){
    if(root==NULL){
        return -1;
    }else{
        int leftheight=height(root->left);
        int rightheight=height(root->right);

        if(leftheight > rightheight){
            return (leftheight+1);
        }else{
            return (rightheight+1);
        }
    }
}

//idenya adalah kita hampir melakukan hal yang serupa seperti qsort
//beda sedikit nantinya di rumus nya ((awal + akhir + 1) / 2)
//stater nya => (awal = 0); (akhir = data - 1)
BSTNode* result(int arr[], int awal, int akhir){
    //tetapkan base case nya
    if (awal > akhir){
      return NULL;
    }
    
    //pivot ini lah yang akan menjadi tumpuan untuk menyelesaikan soal
    //jika ada data 3 6 7 9 11
    //maka pivot awal nya = (0 + 4 + 1) / 2 = 2;
    //jadi nanti nya 7 akan menjadi input pertama

    //setelah rekursi root left dan right, nilai awal jadi 1 dan nilai akhir jadi 1
    //lalu pivot nya jadi 1, otomatis arr[1] akan dimasukkan ke root
    //lakukan ini terus menerus nantinya  
    int pivot = (awal + akhir + 1) / 2;

    //masukkan posisi pivot di array ke node
    BSTNode *root = _bst_createNode(arr[pivot]);

    //setelah itu kita lakukan rekursi
    //untuk root kiri, tentu nya kita mengubah akhir nya jadi pivot - 1
    //untuk root kanan, kita ubah awal jadi pivot + 1
    //lakukan ini terus menerus sampai semua array terbaca dan ter assign
    root->left =  result(arr, awal, pivot - 1);
    root->right = result(arr, pivot + 1, akhir);
  
    return root;
}

//bantuan function untuk library qsort stdlib
int check(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}

int main(){
    //pertama kita deklarasi data, yang gunanya utk mengetahui brapa banyak input
    int data;
    scanf("%d", &data);

    //deklarasi array yang isinya sebanyak data
    int arr[data];

    //masukkan nilai - nilai nya ke dalam arr[0] sampai arr[data-1]
    for(int i = 0 ; i < data ; i++){
        scanf("%d", &arr[i]);
    }
    
    //lalu kita urutkan data yang tadi dimasukkan itu dengan bantuan quick sort library dari stdlib
    qsort(arr, data, sizeof(int), check);

    //disini kita tidak memakai struct BST, karena kita tidak membutuhkan spesifikasi yang ada di struct BST
    //jadi lebih baik langsung saja ke BSTNode
    //penjelasan result ada di function nya
    BSTNode *head = result(arr, 0, data-1);
    
    //lalu kita tinggal print sesuai keinginan soal
    //preorder, inorder, postorder
    __bst__preorder(head);
    printf("\n");
    __bst__inorder(head);
    printf("\n");
    __bst__postorder(head);
    printf("\n");
  
    return 0;
}