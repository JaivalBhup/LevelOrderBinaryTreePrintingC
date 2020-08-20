//
// Created by Jaival Bhuptani on 2020-08-06.
//

#ifndef ASSIGN3_SERIALIZEDESERIALIZEANDPRINTTREE_H
#define ASSIGN3_SERIALIZEDESERIALIZEANDPRINTTREE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
//------------------------- All Structs -------------------------
// tree node struct -- spaces are provided to every node. these spaces define the place where the node
// is suppose to be printed.
typedef struct node
{
    int key;
    int space;
    struct node* left, *right;
}Node, *NodePtr;
// Binary tree struct
typedef struct {
    NodePtr Root;
    int totalNodes;
}*BinaryTree;

// QueueNode Struct
typedef struct def_{
    Node* treeNode;
    struct def_ *next;
} QNode, *QNodePtr;
// Queue Struct
typedef struct{
    QNodePtr head;
    QNodePtr tail;
}QueueType, *Queue;
//------------------------- Queue -------------------------
//initialize the queue
Queue initQueue(){
    Queue q = malloc(sizeof(QueueType));
    q->head = NULL;
    q->tail = NULL;
    return q;
}
// checks it the queue is empty
int isEmpty(Queue q){
    return (q->head == NULL);
}
// adds a new element to the queue
void enQueue(Queue* q, Node* treeNode){
    QNodePtr ptr = malloc(sizeof(QNode));
    ptr->treeNode = treeNode;
    ptr->next = NULL;
    if(isEmpty(*q)){
        (*q)->head=ptr;
        (*q)->tail = ptr;
    }
    else{
        (*q)->tail->next = ptr;
        (*q)->tail = ptr;
    }
}
// removes an element from the queue
NodePtr dequeue(Queue* q){
    if(isEmpty((*q))){
        NodePtr rouge = malloc(sizeof(Node));
        rouge->key = -1;
        puts("QUEUE IS EMPTY");
        return rouge;
    }
    QNodePtr ptr = (*q)->head;
    NodePtr data = (*q)->head->treeNode;
    (*q)->head = (*q)->head->next;
    free(ptr);
    return data;
}
//------------------------- Binary Tree -------------------------
// creates a new tree node
Node* newNode(int key)
{
    Node* temp = malloc(sizeof(Node));
    temp->key = key;
    temp->space = 0;
    temp->left = temp->right = NULL;
    return (temp);
}
// takes a file as input and creates a tree from the file by using '@' as a empty node.
void deserializeTree(BinaryTree* tree,Node **root, FILE* file){
    int val;
    char n[120];
    if(!fscanf(file, "%s", n) || !strcmp(n,"@")) {
        return;
    }

    val = atoi(n);
   // printf("%d", val);
    *root = newNode(val);
    (*tree)->totalNodes++;
    deserializeTree(tree,&(*root)->left,file);
    deserializeTree(tree,&(*root)->right,file);
}
// Pre order traversal
void preOrder(Node *root){
    if(root){
        printf("%d ",root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}
// uses pre order traversal to go through every node and allocate space to it.
// it allocates different spaces for 2 digit numbers and 1 digit number.
void allocateSpaces(BinaryTree *tree,Node **root,int* i)
{
    if (*root)
    {
        allocateSpaces(tree,&((*root)->left),i);
        int rootSpace = 0;
        int DigitSpace = 0;
        if((*tree)->Root->key == (*root)->key) rootSpace = 2;
        if((*root)->key<10) DigitSpace = 1;
        //if((*root)->key>=10){DigitSpace = 4;}
        (*root)->space = *i+rootSpace+DigitSpace;
        *i+=1;
        allocateSpaces(tree,&((*root)->right),i);
    }
}
// initializes a null binary tree
BinaryTree initNullBinaryTree(){
    BinaryTree tree = malloc(sizeof(*tree));
    tree->Root = NULL;
    tree->totalNodes = 0;
    return tree;
}
// in order traversal to see sorted list
void inorder(Node *root)
{
    if (root)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
// this is a recursive method. It uses queue to print the tree level-wise
// it keeps track of every slashes and after every \n it prints the slashes
// it differentiates between 2 digit numbers and 1 digit number.
// this method loops for 2 times the number of nodes in the tree.
void printTreeUsingQueue(Node *root, Queue* q,char str[200],int i, int dis,int count){
    int d;
    int d1;
    if(i<=count*2) {
        NodePtr current = root;
        if (current == NULL) {
            enQueue(q, NULL);
            printf("\n");
            printf("%s\n",str);
            strcpy(str,"");
            dis = 0;
        } else {
            if (current->key < 10) {
                d = dis+1;
                d1 = dis;
            } else {
                d = dis;
                d1 = dis;
            }
            for (int j = 0; j < current->space - d; j++) {
                strcat(str, " ");
            }
            if (current->left) {
                enQueue(q, current->left);
                strcat(str, "/");
            } else {
                strcat(str, " ");
            }
            if (current->right) {
                enQueue(q, current->right);
                strcat(str, " \\");
            }
            for (int j = 0; j < current->space - d1; j++) {
                printf(" ");
            }
            printf("%d", current->key);
            dis = current->space;
        }
        i+=1;
        printTreeUsingQueue(dequeue(q),q,str,i,dis,count);
    }
}
//  prints a binary tree
void printTree(BinaryTree *tree){
    Queue q = initQueue();
    enQueue(&q,(*tree)->Root);
    enQueue(&q,NULL);
    char slashes[200] = "";
    int p = 0;
    int dis = 0;
    int count = (*tree)->totalNodes;
    printTreeUsingQueue(dequeue(&q),&q,slashes,p,dis,count);
}

#endif //ASSIGN3_SERIALIZEDESERIALIZEANDPRINTTREE_H
