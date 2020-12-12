#include <iostream>
#include "BinaryTree.h"

int main() {
    Node *root = nullptr;
    root = CreateBST();
    ListOfColumns *list = new ListOfColumns;
    list -> head = nullptr;
    list -> tail = nullptr;
    DoubleLLNode *CurCol = nullptr;
    DoubleLLNode *PrevCol = nullptr;
    CreateListOfColumn(root,list,CurCol,PrevCol);
    PrintColumnsOfTree(list);
    std::cout << "\nPress any key to continue";
    std::cin.get();
    DeleteListOfColumns(list);
}