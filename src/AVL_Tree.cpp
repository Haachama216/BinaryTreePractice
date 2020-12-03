#include "BinaryTree.h"

AVL_Node* GetNewAVL_Node(int data) {
    AVL_Node *newnode = new AVL_Node;
    newnode -> data = data;
    newnode -> left = nullptr;
    newnode -> right = nullptr;
    newnode -> height = 0;
    return newnode;
}
int GetHeight(AVL_Node *node) {
    if (!node)
        return -1;
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
void InsertAVL_Node(AVL_Node *&root, int data) {
    if (!root)
        root = GetNewAVL_Node(data);
    else {
        if (data < root -> data)
            InsertAVL_Node(root -> left,data);
        else
            InsertAVL_Node(root -> right,data);
        root -> height = std::max(GetHeight(root -> left),GetHeight(root -> right)) + 1;
        if (GetBalanceFactor(root) > 1) {
            if (data < (root -> left) -> data)
                RightRotate(root);
            else {
                LeftRotate(root -> left);
                RightRotate(root);
            }
        }
        if (GetBalanceFactor(root) < -1) {
            if (data > (root -> right) -> data)
                LeftRotate(root);
            else {
                RightRotate(root -> right);
                LeftRotate(root);
            }
        }
    }
}
void DeleteAVL_Node(AVL_Node *&root, int data) {
    if (root -> data < data)
        DeleteAVL_Node(root -> left,data);
    else if (root -> data > data)
        DeleteAVL_Node(root -> right,data);
    else {
        if (!root -> left && !root -> right) {
            delete root;
            root = nullptr;
        }
        else if (root -> left && root -> right) {
            AVL_Node *successor = root -> right;
            AVL_Node *ParentSuccessor = root;
            while (successor -> left) {
                ParentSuccessor = successor;
                successor = successor -> left;
            }
            root -> data = successor -> data;
            if (successor -> right) {
                ParentSuccessor -> left = successor -> right;
                delete successor;
            }
            else {
                delete successor;
                successor = nullptr;
            }
        }
        else {
            if (root -> left) {
                root -> data = (root -> left) -> data;
                delete root -> left;
                root -> left = nullptr;
            }
            else {
                root -> data = (root -> right) -> data;
                delete root -> right;
                root -> right = nullptr;
            }
        }
    }
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
void DeleteAVL_Tree(AVL_Node *&root) {
    if (root) {
        DeleteAVL_Tree(root -> left);
        DeleteAVL_Tree(root -> right);
        delete root;
        root = nullptr;
    }
}