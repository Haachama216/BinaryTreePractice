#include "BinaryTree.h"

AVL_Node* GetNewAVLNode(int data) {
    AVL_Node *newnode = new AVL_Node;
    newnode -> data = data;
    newnode -> left = nullptr;
    newnode -> right = nullptr;
    newnode -> height = 1;
    return newnode;
}
int GetHeight(AVL_Node *node) {
    if (!node)
        return 0;
    return node -> height;
}
int GetBalanceFactor(AVL_Node *node) {
    return GetHeight(node -> left) - GetHeight(node -> right);
}
void LeftRotate(AVL_Node *&parent) {
    AVL_Node *child {parent -> right};
    AVL_Node *GrandChild {child -> left};
    child -> left = parent;
    parent -> right = GrandChild;
    parent -> height = std::max(GetHeight(parent -> left),GetHeight(parent -> right)) + 1;
    child -> height = std::max(GetHeight(child -> left),GetHeight(child -> right)) + 1;
    parent = child;
}
void RightRotate(AVL_Node *&parent) {
    AVL_Node *child {parent -> left};
    AVL_Node *GrandChild {child -> right};
    child -> right = parent;
    parent -> left = GrandChild;
    parent -> height = std::max(GetHeight(parent -> left), GetHeight(parent -> right)) + 1;
    child -> height = std::max(GetHeight(child -> left),GetHeight(child -> right)) + 1;
    parent = child;
}
void InsertAVLNode(AVL_Node *&root, int data) {
    if (!root)
        root = GetNewAVLNode(data);
    else {
        if (data < root -> data)
            InsertAVLNode(root -> left,data);
        else
            InsertAVLNode(root -> right,data);
        root -> height = std::max(GetHeight(root -> left),GetHeight(root -> right)) + 1;
        if (GetBalanceFactor(root) > 1) {
            if (GetBalanceFactor(root -> left) < 0) {
                LeftRotate(root -> left);
                RightRotate(root);
            }
            else
                RightRotate(root);
        }
        if (GetBalanceFactor(root) < -1) {
            if (GetBalanceFactor(root -> right) > 0) {
                RightRotate(root -> right);
                LeftRotate(root);
            }
            else   
                LeftRotate(root);
        }
    }
}
void PrintAVLTree(AVL_Node *root) {
    if (root) {
        PrintAVLTree(root -> left);
        std::cout << root -> data;
        PrintAVLTree(root -> right);
    }
}
void DeleteAVLNode(AVL_Node *&root, int data) {
    if (!root) {
        std::cout << "can not find the data in tree";
        return;
    }
    if (data < root -> data)
        DeleteAVLNode(root -> left,data);
    else if (data > root -> data)
        DeleteAVLNode(root -> right,data);
    else {
        if (!root -> left || !root -> right) {
            AVL_Node *child = ((root -> left) ? root -> left : root -> right);
            if (!child) {
                delete root;
                root = nullptr;
            }
            else {
                delete root;
                root = child;
            }
        }
        else {
            AVL_Node *successor = root -> right;
            while (successor -> left) {
                successor = successor -> left;
            }
            root -> data = successor -> data;
            DeleteAVLNode(root -> right, successor -> data);
        }
    }
    //check whether the current root was delete or not
    if (root) {
        root -> height = std::max(GetHeight(root -> left),GetHeight(root -> right)) + 1;
        if (GetBalanceFactor(root) > 1) {
            if (GetBalanceFactor(root -> left) < 0) {
                LeftRotate(root -> left);
                RightRotate(root);
            }
            else
                RightRotate(root);
        }
        else if (GetBalanceFactor(root) < -1) {
            if (GetBalanceFactor(root -> right) > 0) {
                RightRotate(root -> right);
                LeftRotate(root);
            }
            else
                LeftRotate(root);
        }
    }
}
void DeleteAVLTree(AVL_Node *&root) {
    if (root) {
        DeleteAVLTree(root -> left);
        DeleteAVLTree(root -> right);
        delete root;
        root = nullptr;
    }
}