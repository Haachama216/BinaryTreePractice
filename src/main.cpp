#include <iostream>
#include "BinaryTree.h"
Node* RecurDeleteBTS(Node *root, int data) {
    if (!root) {
        std::cout << "cant find the key to delete\n";
        return root;
    }
    if (root -> data < data)
        root -> left = RecurDeleteBTS(root -> left,data);
    else if (root -> data > data)
        root -> right = RecurDeleteBTS(root -> right,data);
    else {
        if (!root -> left && !root -> right) {
            delete root;
            root = nullptr;
        }
        else if (root -> left && root -> right) {
            Node *successor = root -> right;
            while (successor -> left)
                successor = successor -> left;
            root -> data = successor -> data;
            RecurDeleteBTS(root -> right, successor -> data);
        }
        else {
            Node *child = ((root -> left) ? root -> left : root -> right);
            Node *temp = root;
            root = child;
            delete temp;
        }
    }
    return root;
}
int main() {
    // Node *root = nullptr;
    // root = CreateBST();
    // ListOfColumns *list = new ListOfColumns;
    // list -> head = nullptr;
    // list -> tail = nullptr;
    // DoubleLLNode *CurCol = nullptr;
    // DoubleLLNode *PrevCol = nullptr;
    // CreateListOfColumn(root,list,CurCol,PrevCol);
    // PrintColumnsOfTree(list);
    // std::cout << "\nPress any key to continue";
    AVL_Node *root = nullptr;
    int arr[10] {1,4,3,6,7,5,8,0,9,6};
    for (int i = 0; i < 10; ++i)
        InsertAVLNode(root,arr[i]);
    PrintAVLTree(root);
    DeleteAVLNode(root,6);
    std::cout << "\n";
    PrintAVLTree(root);
    DeleteAVLTree(root);
    std::cin.get();
    //DeleteListOfColumns(list);
}