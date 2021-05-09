#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

//Pertama kita dapatkan dahulu code dari github nya
//--------------------------------------------------------------
typedef struct bstnode_t
{
    int key;
    struct bstnode_t
        *left,
        *right;
} BSTNode;

typedef struct bst_t
{
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

BSTNode *__bst__createNode(int value)
{
    BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode *__bst__insert(BSTNode *root, int value)
{
    if (root == NULL)
        return __bst__createNode(value);

    if (value < root->key)
        root->left = __bst__insert(root->left, value);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value);

    return root;
}

BSTNode *__bst__search(BSTNode *root, int value)
{
    while (root != NULL)
    {
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
        else
            return root;
    }
    return root;
}

BSTNode *__bst__findMinNode(BSTNode *node)
{
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;

    return currNode;
}

BSTNode *__bst__remove(BSTNode *root, int value)
{
    if (root == NULL)
        return NULL;

    if (value > root->key)
        root->right = __bst__remove(root->right, value);
    else if (value < root->key)
        root->left = __bst__remove(root->left, value);
    else
    {

        if (root->left == NULL)
        {
            BSTNode *rightChild = root->right;
            free(root);
            return rightChild;
        }
        else if (root->right == NULL)
        {
            BSTNode *leftChild = root->left;
            free(root);
            return leftChild;
        }

        BSTNode *temp = __bst__findMinNode(root->right);
        root->key = temp->key;
        root->right = __bst__remove(root->right, temp->key);
    }
    return root;
}

void __bst__inorder(BSTNode *root)
{
    if (root)
    {
        __bst__inorder(root->left);
        printf("%d ", root->key);
        __bst__inorder(root->right);
    }
}

void __bst__postorder(BSTNode *root)
{
    if (root)
    {
        __bst__postorder(root->left);
        __bst__postorder(root->right);
        printf("%d ", root->key);
    }
}

void __bst__preorder(BSTNode *root)
{
    if (root)
    {
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

void bst_init(BST *bst)
{
    bst->_root = NULL;
    bst->_size = 0u;
}

bool bst_isEmpty(BST *bst)
{
    return bst->_root == NULL;
}

bool bst_find(BST *bst, int value)
{
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;

    if (temp->key == value)
        return true;
    else
        return false;
}

void bst_insert(BST *bst, int value)
{
    if (!bst_find(bst, value))
    {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}

void bst_remove(BST *bst, int value)
{
    if (bst_find(bst, value))
    {
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

void bst_inorder(BST *bst)
{
    __bst__inorder(bst->_root);
}

void bst_postorder(BST *bst)
{
    __bst__postorder(bst->_root);
}

void bst_preorder(BST *bst)
{
    __bst__preorder(bst->_root);
}
//--------------------------------------------------------------

/*FUNGSI BUAT NYARI NYA*/

//fungsi untuk mencari apakah node nya ada 
BSTNode *search(BSTNode *head, int input, int input2){
    //kalo root nya udah nol
    if (head == NULL){
        return head;
    }

    //kalo udah sama, return
    if (head->key == input || head->key == input2){
        return head;
    }

    //cari 2 node di kiri dan kanan
    //kemungkinan besar node mereka bersebrangan maka cari di kedua sisi
    BSTNode *leftNode = search(head->left, input, input2);
    BSTNode *rightNode = search(head->right, input, input2);

    //jika kedua nya ada nilainya return head
    if (leftNode != NULL && rightNode != NULL){
        return head;
    }

    //jika kedua node itu tidak ada alias null, return null
    if (leftNode == NULL && rightNode == NULL){
        return NULL;
    }

    //jika leftnode nya != null, artinya kita akan search trus ke bawah
    if (leftNode != NULL){
        return search(head->left, input, input2);
    }
    //berlaku juga untuk node kanan
    return search(head->right, input, input2);  
}

//ini untuk mendapat distance nya / level nya
//idenya adalah mencari ketinggian masing2 input, lalu menjumlahkan nya
/*
        6
    /      \
   3        9
  / \      / \
1    5    7  11

jarak dari 3 dan 9 adalah 2
maka ini bisa didapat dengan mendapat level dari 3 dan 9
node 3 berada di level 1, dan 9 berada di level 1, maka 1+1 = 2
jadi dapatkan level/height masing2 node, dan jumlahkan (tentu nantinya saat penjumlahan ada beberapa syarat)
*/
int treeLadder(BSTNode *head, int height, int input){
    //base case 1
    if (head == NULL){
        return -1;
    }

    //jika saat pencarian node nya ketemu, return height / level nya
    if (head->key == input){
        return height;
    }

    //kita rekursi ke bagian kiri node terus menerus
    //jangan lupa height++ juga, sebagai tanda kita mencari level dari suatu node
    int left = treeLadder(head->left, height + 1, input);

    //jika ternyata left nya -1, rekursi nya sekarang ke kanan
    //karena kirinya sudah tidak ada node lagi
    if (left == -1){
        return treeLadder(head->right, height + 1, input);
    }

    return left;
}

//inilah function untuk menjumlahkan 2 jarak/distance nya
int realResults(BSTNode *head, int input, int input2){
    //search untuk mencari apakah ada input dan input2 dalam bst
    BSTNode *temp = search(head, input, input2);

    //low adalah level awal suatu node
    int low = 0;

    //distance_1 sebenarnya adalah pencarian level node dari input
    //distance_2 adalah pencarian level node dari input2
    int distance_1 = treeLadder(temp, low, input);
    int distance_2 = treeLadder(temp, low, input2);

    //jika distance nya jumlahnya 0, return 0
    if(distance_1 + distance_2 == 0){
        return 0;
    }

    //jika distance nya saat dijumlah negatif, return 0 juga
    //fungsi ini dibuat karena jarak tidak pernah minus (kecuali fisika)
    else if(distance_1 + distance_2 < 0){
        return 0;
    }

    //jika saat dijumlah itu tidak memenuhi if state di atas, maka jumlahkan biasa saja
    else{
        return distance_1 + distance_2;
    }
    
}

//mendapatkan distance (hasil) melalui struct BST
int distance(BST *node, int input, int input2){
    int results = realResults(node->_root, input, input2);
    return results;
}


int main(){
    //inisialisasi BST nya 
    BST bst;
    bst_init(&bst);

    //deklarasi query dan masukkan nilai query
    //query = banyak node yang ingin dimasukkan
    int query;
    scanf("%d", &query);

    //masukkan data data nya dan insert ke bst
    for (int i = 1; i <= query; ++i){
        int data;
        scanf("%d", &data);
        bst_insert(&bst, data);
    }

    //muchData = berapa banyak node yang ingin dicari jaraknya
    int muchData;
    scanf("%d", &muchData);

    //cari jaraknya dalam perulangan ini
    for (int k = 1; k <= muchData; ++k){
        //input dan input2 adalah node yang ingin dicari jarak nya
        int input, input2;
        scanf("%d %d", &input, &input2);

        //penjelasan function nya ada di atas
        int res = distance(&bst, input, input2);

        //setelah didapat jaraknya, print hasil
        printf("%d\n", res);
    }
}