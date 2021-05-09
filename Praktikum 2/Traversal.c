#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


//Pertama kita dapatkan dahulu code dari github nya
//note: terdapat modif di bst_insert
//--------------------------------------------------------------
typedef struct bstnode_t
{
    int key;
    int count;
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
    newNode->count = 0;
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

    else if(value == root->key){
        root->count++;
    }
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
        if(root->count == 0) {
            printf("%d ", root->key);
        }
        
        else{
            for(int i = 0; i < root->count; ++i){
                printf("%d ", root->key);
            }
        }

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
    /*
        Karena duplikat diperbolehkan, maka kita tidak perlu if statement di bawah ini
    */
    // if (!bst_find(bst, value)) {
    //     bst->_root = __bst__insert(bst->_root, value);
    //     bst->_size++;
    // }

    bst->_root = __bst__insert(bst->_root, value);
    bst->_size++;
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

//PRINT LEVEL
//print level artinya kita print bst nya secara level nya, atau bisa dibilang ketinggiannya
//mulai dari node root paling atas, sampe paling bawah
bool printLevel(BSTNode *node, int level)
{
    //jika node = NULL, artinya salah satu antara leftNode dan Rightnode nya paling mentok
    if (node == NULL)
    {
        //return false untuk memberi pesan kepada __bst__levelorder  
        return false;
    }

    //jika level = 1, artinya kita akan print
    //jika fungsi __bst__levelorder mengirimkan level 1, otomatis akan langsung masuk ke sini
    //jika passing nya level 2, otomatis kita harus turun dulu 1 tingkat, lalu print. Hal sama untuk level selanjutnya
    //berarti kita rekursi ke kiri dan kanan, dan kurangkan level nya sampai level = 1 untuk mengprint nya
    if (level == 1)
    {
        printf("%d ", node->key);
        //return true untuk memberi pesan pada __bst__levelorder    
        return true;
    }

    //jika level != 1, alias dibutuhkan nya level 2,3,4,dst., rekursi ke kiri dan kanan nya dan level dikurangi 1
    //dikurangi 1 karena kita akan mendapat level nya tepat bila sudah mencapai level == 1
    /*
              20
             /  \
            10  30
           /     \
          5      35
    level = 1, langsung print 20,
    level = 2, rekursi akan ke 10 dan 30, dan level = 1, karna level = 1, print
    level = 3, rekursi dari 20 ke 10 dan 30, otomatis level = 2, karena level != 1, lanjut lagi ke left & right node
    10 akan ke 5, dan 30 akan ke 35, dan level = 1, karena level = 1, print
    begitu seterusnya
    */

    //rekursi untuk mencari level dan melanjutkan node nya
    bool left = printLevel(node->left, level - 1);
    bool right = printLevel(node->right, level - 1);

    //return left||right artinya jika salah satu dari level tersebut punya setidaknya 1 node, nilai nya true
    return left || right;
}

void __bst__levelorder(BSTNode *head)
{
    //kita mulai dari level 1, alias dari paling atas
    int level = 1;

    while (printLevel(head, level))
    {
        //jika dalam level tersebut terdapat setidaknya 1 node, dikiri ataupun dikanan, level++
        //yang artinya level seterusnya kemungkinan ada
        //jika sudah return false dari printLevel, program berhenti
        ++level;
    }
}

void bst_levelorder(BST *bst)
{
    __bst__levelorder(bst->_root);
}

/*
Fungsi ini untuk menghapus semua node dalam tree
Pertama kita membuat if statement if head == NULL, yang berarti jika kita sudah di paling bawah dari tree, maka return
Lalu saat kita sudah mencapai bagian paling bawah dari tree, hapus tree tersebut dan kembali lagi ke atas nya. Hapus. Dan ke atas lagi
Lakukan trus sampai semua node nya terhapus
*/
void deleteTree(BSTNode *head)
{
    if (head == NULL)
    {
        return;
    }

    //lakukan rekursi ke dua sisi dari root pertama
    deleteTree(head->left);
    deleteTree(head->right);

    //saat sudah di node yang level paling bawah, free(struct node nya)
    //lakukan sampai habis
    free(head);
}

//memanggil fungsi deleteTree dalam bentuk struct BST
void deleteBST(BST *bst)
{
    deleteTree(bst->_root);
}

int main()
{
    //pertama kita inisialisasi BST set nya
    BST set;
    bst_init(&set);

    //lalu kita buat int testcase untuk mengetahui brapa banyak test case yang ingin dimasukkan
    int testcase;
    scanf("%d", &testcase);

    //lalu kita buat char input untuk memasukkan input user nantinya
    //mengapa char bukan int? karena nantinya saat user memasukkan STOP, maka output dikeluarkan
    //untuk convert dari string ke int, kita gunakan atoi nanti
    char input[50001];

    for (int i = 0; i < testcase; ++i)
    {
        //selama input nya bukan STOP, maka jalankan terus di while loop
        while (true)
        {
            //masukkan input nya
            scanf("%s", input);

            //jika input = STOP, break dan output hasilnya
            if (strcmp(input, "STOP") == 0)
            {
                break;
            }

            //jika bukan STOP, kita convert input ke int dengan atoi
            //lalu kita insert ke bst nya tersebut
            int data = atoi(input);
            bst_insert(&set, data);
        }


        //Jika saat user memasukkan STOP, otomatis nanti while loop berhenti dan menjalankan yang di bawah ini
        //untuk preorder, inorder, dan postorder menggunakan tipe yang sama dari modul
        printf("Pre-order: ");
        bst_preorder(&set);
        printf("\n");

        printf("In-order: ");
        bst_inorder(&set);
        printf("\n");

        printf("Post-order: ");
        bst_postorder(&set);
        printf("\n");

        //untuk level order, cara kerjanya bisa dilihat dari function printLevel dan __bst__levelorder
        printf("Level-order: ");
        bst_levelorder(&set);
        printf("\n");

        //setelah semua selesai di print, jangan lupa hapus bst nya
        //jika tidak dihapus, nantinya akan terbawa untuk input selanjutnya
        deleteBST(&set);

        //jangan lupa setelah dihapus, otomatis kita harus menginisialisasi ulang bst nya
        bst_init(&set);
    }

    return 0;
}