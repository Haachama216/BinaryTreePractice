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
//Add an item to the tree column
void AddTailColumn(TreeColumn *Column, int data) {
    (Column -> tail) -> next = NewTreeDataNode(data);
    Column -> tail = (Column -> tail) -> next;
}
//Add a column to the head of list
void AddHeadList(ListOfColumns *list, int data) {
    DoubleLLNode *newnode = NewColumn(data);
    newnode -> next = list -> head;
    (list -> head) -> prev = newnode;
    list -> head = newnode;
}
//Add a column to the tail of list
void AddTailList(ListOfColumns *list, int data) {
    DoubleLLNode *newnode = NewColumn(data);
    newnode -> prev = list -> tail;
    (list -> tail) -> next = newnode;
    list -> tail = newnode;
}
//Create the list of column of tree
void CreateListOfColumn(Node *root, ListOfColumns *list, DoubleLLNode *CurCol, DoubleLLNode *PrevCol) {
    if (root) {
        //if the list is empty, its head and tail will be assigned with a new column
        if (!list -> head) {
            list -> head = NewColumn(root -> data);
            list -> tail = list -> head;
            CurCol = list -> head;
        }
        //if current column is empty, add a new column to the list
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
        //Add item to the current column
        else {
            AddTailColumn(CurCol -> list,root -> data);
        }
        //Recursion for the left subtree and the right subtree
        CreateListOfColumn(root -> left,list,CurCol -> prev, CurCol);
        CreateListOfColumn(root -> right,list,CurCol -> next,CurCol);
    }
}
//Deallocate the column
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
//Deallocate the whole list of columns
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
//print the column of tree
void PrintColumn(TreeColumn *Column) {
    TreeDataNode *it = Column -> head;
    while (it) {
        std::cout << it -> data << ' ';
        it = it -> next;
    }
    std::cout << '\n';
}
//Print each column of tree line by line
void PrintColumnsOfTree(ListOfColumns *list) {
    DoubleLLNode *it = list -> head;
    while (it) {
        PrintColumn(it -> list);
        it = it -> next;
    }
}
