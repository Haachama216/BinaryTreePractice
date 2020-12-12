#include "BinaryTree.h"

TreeDataNode* NewTreeDataNode(int data) {
    TreeDataNode *newnode = new TreeDataNode;
    newnode -> data = data;
    newnode -> next = nullptr;
    return newnode;
}
TreeColumn* CreateColumn(int data) {
    TreeColumn *newColumn = new TreeColumn;
    newColumn -> head = NewTreeDataNode(data);
    newColumn -> tail = newColumn -> head;
    return newColumn;
}
DoubleLLNode* NewColumn(int data) {
    DoubleLLNode *newnode = new DoubleLLNode;
    newnode -> list = CreateColumn(data);
    newnode -> prev = nullptr;
    newnode -> next = nullptr;
    return newnode;
}
void AddTailColumn(TreeColumn *Column, int data) {
    (Column -> tail) -> next = NewTreeDataNode(data);
    Column -> tail = (Column -> tail) -> next;
}
void AddHeadList(ListOfColumns *list, int data) {
    DoubleLLNode *newnode = NewColumn(data);
    newnode -> next = list -> head;
    (list -> head) -> prev = newnode;
    list -> head = newnode;
}
void AddTailList(ListOfColumns *list, int data) {
    DoubleLLNode *newnode = NewColumn(data);
    newnode -> prev = list -> tail;
    (list -> tail) -> next = newnode;
    list -> tail = newnode;
}
void CreateListOfColumn(Node *root, ListOfColumns *list, DoubleLLNode *CurCol, DoubleLLNode *PrevCol) {
    if (root) {
        if (!list -> head) {
            list -> head = NewColumn(root -> data);
            list -> tail = list -> head;
            CurCol = list -> head;
        }
        else if (!CurCol) {
            if (PrevCol == list -> head) {
                AddHeadList(list,root -> data);
                CurCol = list -> head;
            }
            else {
                AddTailList(list,root -> data);
                CurCol = list -> tail;
            }
        }
        else {
            AddTailColumn(CurCol -> list,root -> data);
        }
        CreateListOfColumn(root -> left,list,CurCol -> prev, CurCol);
        CreateListOfColumn(root -> right,list,CurCol -> next,CurCol);
    }
}
void DeleteColumn(TreeColumn *&Column) {
    TreeDataNode *it = Column -> head;
    while (it) {
        TreeDataNode *temp = it;
        it = it -> next;
        delete temp;
    }
    delete Column;
    Column = nullptr;
}
void DeleteListOfColumns(ListOfColumns *&list) {
    DoubleLLNode *it = list -> head;
    while (it) {
        DeleteColumn(it -> list);
        DoubleLLNode *temp = it;
        it = it -> next;
        delete temp;
    }
    delete list;
    list = nullptr;
}
void PrintColumn(TreeColumn *Column) {
    TreeDataNode *it = Column -> head;
    while (it) {
        std::cout << it -> data << ' ';
        it = it -> next;
    }
    std::cout << '\n';
}
void PrintColumnsOfTree(ListOfColumns *list) {
    DoubleLLNode *it = list -> head;
    while (it) {
        PrintColumn(it -> list);
        it = it -> next;
    }
}
