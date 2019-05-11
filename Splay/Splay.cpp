#include<bits/stdc++.h>
using namespace std;

struct Node{
    int value;
    Node *left;
    Node *right;
    Node(int v):value(v),left(NULL),right(NULL){}
    Node(int v,Node *l,Node *r):value(v),left(l),right(r){}
};

class Splay {
    private:
        Node *root;
        void preorderHelper(Node *node)
        {
            if(node != NULL)
            {
                cout<<node->value<<" ";
                preorderHelper(node->left);
                preorderHelper(node->right);
            }
        }
        void inorderHelper(Node *node)
        {
            if(!node)
                return;
            inorderHelper(node->left);
            cout<<node->value<<" ";
            inorderHelper(node->right);
        }
        Node *rightRotate(Node *node)
        {
            Node *left = node->left;
            Node *left_right = left->right;

            left->right = node;
            node->left = left_right;

            //node->height = 1 + max(height(node->left),height(node->right));
            //left->height = 1 + max(height(left->left),height(left->right));
            return left;
        }
        Node *leftRotate(Node *node)
        {
            Node *right = node->right;
            Node *right_left = right->left;

            right->left = node;
            node->right = right_left;

            //node->height = 1 + max(height(node->left),height(node->right));
            //right->height = 1 + max(height(right->left),height(right->right));
            return right;
        }
        Node *splay(Node *node,int key)
        {
            if(node == NULL || node->value == key)
                return node;
            if(key < node->value)                       //key is in left subtree
            {
                if(node->left == NULL)
                    return node;
                if(key < node->left->value)                //left-left case(ZIG-ZIG)
                {
                    node->left->left = splay(node->left->left,key);
                    node = rightRotate(node);
                }
                else if(key > node->left->value)            //left-right case (ZIG-ZAG)
                {
                    node->left->right = splay(node->left->right,key);
                    if(node->left->right)
                        node->left = leftRotate(node->left);
                }
                return(node->left)?rightRotate(node):node;
            }
            else
            {
                if(node->right == NULL)
                    return node;
                if(key > node->right->value)                    //right-right case(ZIG-ZIG)
                {
                    node->right->right = splay(node->right->right,key);
                    node = leftRotate(node);
                }
                else if(key < node->right->value)               //right-left case(ZIG-ZAG)
                {
                    node->right->left = splay(node->right->left,key);
                    if(node->right->left)
                        node->right = rightRotate(node->right);
                }
                return (node->right)?leftRotate(node):node;
            }
        }
        Node *insertKeyHelper(Node *node,int key)
        {
            if(node == NULL)
                return new Node(key);
            node = splay(node,key);
            if(node->value == key)
                return node;
            Node *newNode = new Node(key);
            if(key < node->value)
            {
                newNode->right = node;
                newNode->left = node->left;
                node->left = NULL;
            }
            else
            {
                newNode->left = node;
                newNode->right = node->right;
                node->right = NULL;
            }
            return newNode;
        }
        Node *deleteKeyHelper(Node *node,int key)
        {
            if(node == NULL)
                return node;
            node = splay(node,key);
            if(key != node->value)
                return node;
            Node *toDelete;
            if(!node->left)
            {
                toDelete = node;
                node = node->right;
            }
            else
            {
                toDelete = node;
                node = splay(node->left,key);
                node->right = toDelete->right;
            }
            delete toDelete;
            return node;
        }
    public:
        void printPreorder()
        {
            preorderHelper(root);
        }
        void printInorder()
        {
            inorderHelper(root);
        }
        void create()
        {
            root = NULL;
        }
        Node *searchKey(int key)
        {
            return splay(root,key);
        }
        void insertKey(int key)
        {
            root = insertKeyHelper(root,key);
        }
        void deleteKey(int key)
        {
            root = deleteKeyHelper(root,key);
        }
};

