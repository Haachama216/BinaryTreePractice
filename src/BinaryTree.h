#pragma once
#include <algorithm>
#include <stack>
#include <queue>
#include <iostream>
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
AVL_Node* GetNewAVLNode(int data);
int GetHeight(AVL_Node *node);
int GetBalanceFactor(AVL_Node *node);
void LeftRotate(AVL_Node *&parent);
void RightRotate(AVL_Node *&parent);
void InsertAVLNode(AVL_Node *&root, int data);
void PrintAVLTree(AVL_Node *root);
void DeleteAVLNode(AVL_Node *&root, int data);
void DeleteAVLTree(AVL_Node *&root);
void IterativePrint(Node *root);

struct TreeDataNode {       //store the key of each node of the tree
    int data;
    TreeDataNode *next;
};
struct TreeColumn {       //a Column of tree
    TreeDataNode *head;
    TreeDataNode *tail;
};
struct DoubleLLNode {
    TreeColumn *list;
    DoubleLLNode *prev;
    DoubleLLNode *next;
};
struct ListOfColumns {      //Double linked list to store list of Columns of tree
    DoubleLLNode *head;
    DoubleLLNode *tail;
};
DoubleLLNode* NewColumn(int data);
void AddHeadList(ListOfColumns *list, int data);
void AddTailList(ListOfColumns *list, int data);
TreeColumn* CreateColumn(int data);
void AddTailColumn(TreeColumn *Column, int data);
TreeDataNode* NewTreeDataNode(int data);
void CreateListOfColumn(Node *root, ListOfColumns *list, DoubleLLNode *CurCol, DoubleLLNode *PrevCol);
void DeleteColumn(TreeColumn *&Column);
void DeleteListOfColumns(ListOfColumns *&list);
void PrintColumn(TreeColumn *Column);
void PrintColumnsOfTree(ListOfColumns *list);
