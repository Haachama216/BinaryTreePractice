#pragma once
#include <algorithm>
#include <stack>
#include <queue>
struct Node {
    int data;
    Node *left;
    Node *right;
};
Node* GetNewNode(int data);
void InsertBST(Node *&root, int data);
Node* FindSuccesor(Node *root);
void DeleteBST(Node *&root, int data);
void InsertTree(Node *&root, int data);
int GetMaxWidth(Node *root);
int GetHeight(Node *root);
Node* CreateBST();
void DeleteTree(Node *&root);
void DFS_PrintTree(Node *root);
void BFS_PrintTree(Node *root);

struct AVL_Node {
    int data;
    AVL_Node *left;
    AVL_Node *right;
    int height;
};
AVL_Node* GetNewAVL_Node(int data);
int GetHeight(AVL_Node *node);
int GetBalanceFactor(AVL_Node *node);
void LeftRotate(AVL_Node *&parent);
void RightRotate(AVL_Node *&parent);
void InsertAVL_Node(AVL_Node *&root, int data);
void DeleteAVLNode(AVL_Node *&root, int data);
void DeleteAVL_Tree(AVL_Node *&root);
void IterativePrint(Node *root);

