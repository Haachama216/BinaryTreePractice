#include <iostream>
#include "BinaryTree.h"
struct Node {
    int data;
    Node *left;
    Node *right;
};
struct AVL_Node {
    int data;
    AVL_Node *left;
    AVL_Node *right;
    int height;
};
Node* GetNewNode(int data) {
    Node *node = new Node;
    node -> data = data;
    node -> left = nullptr;
    node -> right = nullptr;
    return node;
}
void InsertBST(Node *&root, int data) {
    if (!root) {
        root = GetNewNode(data);
    }
    else {
        if (data < root -> data) {
            InsertBST(root -> left,data);
        }
        else {
            InsertBST(root -> right,data);
        }
    }
}
Node* FindSuccesor(Node *root) {
    while (root -> left) {
        root = root -> left;
    }
    return root;
}
void DeleteBST(Node *&root, int data) {
    Node *parent {nullptr};
    Node *cur {root};
    while (cur -> data != data && cur) {
        parent = cur;
        if (data < cur -> data)
            cur = cur -> left;
        else 
            cur = cur -> right;
    }
    if (!cur) {
        std::cout << "khong tim thay gia tri co trong tree";
        return;
    }
    //case 1: no child aka leaf
    if (!cur -> left && !cur -> right) {
        if (cur == root)
            root = nullptr;
        if (parent -> left == cur)
            parent -> left = nullptr;
        else 
            parent -> right = nullptr;
        delete cur;
    }
    //case 3: has two child
    else if (cur -> left && cur -> right) {
        Node *succesor = FindSuccesor(cur -> right);
        cur -> data = succesor -> data;
        DeleteBST(cur -> right, succesor -> data);
    }
    //case 2: has only one child
    else {
        Node *child = ((cur -> left) ? cur -> left : cur -> right);
        if (cur == root) {
            root = child;
        }
        if (parent -> left == cur) {
            parent -> left = child;
        }
        else {
            parent -> right = child;
        }
        delete cur;
    }

}
void InsertTree(Node *&root, int data) {
    if (!root)
        root = GetNewNode(data);
    else {
        std::queue<Node*> queue;
        Node *parent {nullptr};
        queue.push(root);
        do {    
            parent = queue.front();
            queue.pop();
            if (parent -> left && parent -> right) {
                queue.push(parent -> left);
                queue.push(parent -> right);
            }
        } while (parent -> left && parent -> right);
        if (!parent -> left)
            parent -> left = GetNewNode(data);
        else
            parent -> right = GetNewNode(data);
    }
}
int GetMaxWidth(Node *root) {
    int maxWidth = 0;
    std::queue<Node*> q;
    q.push(root);
    int width = 1;
    while (!q.empty()) {
        Node *parent = q.front();
        if (parent -> left)
            q.push(parent->left);
        if (parent -> right)
            q.push(parent -> right);
        q.pop();
        --width;
        if (!width) {
            width = q.size();
            maxWidth = ((maxWidth < width) ? width : maxWidth);
        }
    }
    return maxWidth;
}
int GetHeight(Node *root) {
    if (!root)
        return -1;
    return std::max(GetHeight(root -> left),GetHeight(root -> right)) + 1;
}
Node* CreateBST() {
    int data {0};
    Node *root {nullptr};
    while (std::cin >> data) {
        InsertBST(root,data);
    }
    std::cin.clear();
    std::cin.ignore(32767,'\n');
    return root;
}
void DeleteTree(Node *&root) {
    if (!root)
        return;
    DeleteTree(root -> left);
    DeleteTree(root -> right);
    delete root;
    root = nullptr;
}
void DFS_PrintTree(Node *root) {
    if (root) {
        DFS_PrintTree(root -> left);
        std::cout << root -> data << ' ';
        DFS_PrintTree(root -> right);
    }
}
void BFS_PrintTree(Node *root) {
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        root = q.front();
        q.pop();
        std::cout << root -> data << ' ';
        if (root -> left)
            q.push(root -> left);
        if (root -> right)
            q.push(root -> right);
    }
}
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
void IterativePrint(Node *root) {
    std::stack<Node*> node;
    std::vector<bool> traversed;
    node.push(root);
    traversed.push_back(false);
    while (!node.empty()) {
        if (!traversed.back()) {
            root = node.top();
            std::cout << root -> data << ' ';
            traversed.back() = true;
            if (root -> right) {
                node.push(root -> right);
                traversed.push_back(false);
            }
            if (root -> left) {
                node.push(root -> left);
                traversed.push_back(false);
            }
        }
        else  {
            node.pop();
            traversed.pop_back();
        }
    }
}