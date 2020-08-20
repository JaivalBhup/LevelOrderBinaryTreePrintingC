//Assignment 4
//Jaival Bhuptani(991548280)
#include <stdio.h>
#include "serializeDeserializeAndPrintTree.h"

// In this project i have used Queue to print my binary tree.
// The way I used print this kind of tree is to print by levels.
// I have used queues to manage every level and at a new level I printed a new line.
int main() {
    // initialize the binary
    BinaryTree bt = initNullBinaryTree();
    FILE* fp= fopen("tree.txt", "r");
    // deserialize the tree
    deserializeTree(&bt,&(bt->Root), fp);
    int* i = (int *) 1;
    //allocate the spaces.
    allocateSpaces(&bt,&(bt->Root),&i);
    // print the tree.
    printTree(&bt);
    return 0;
}
