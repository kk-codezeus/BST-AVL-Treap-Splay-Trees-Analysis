#include<bits/stdc++.h>
using namespace std;

struct Node{
    int value;
    Node *left;
    Node *right;
    Node(int v):value(v),left(NULL),right(NULL){}
    Node(int v,Node *l,Node *r):value(v),left(l),right(r){}
};

class BST{
    private:
        Node *root;
        Node *newNode(int key)
        {
            Node *temp = new Node(key);
            return temp;
        }
        Node *deleteTree(Node *node)
        {
            if(node == NULL)
                return NULL;
            node->left = deleteTree(node->left);
            node->right = deleteTree(node->right);

            delete node;
            return NULL;
        }
        void insertKeyHelper(Node *node,int key)
        {
            if(key < node->value)
            {
                if(!node->left)
                    node->left = newNode(key);
                else
                    insertKeyHelper(node->left,key);
            }
            else
                if(!node->right)
                    node->right = newNode(key);
                else
                    insertKeyHelper(node->right,key);
        }
        void printInorderHelper(Node *node)
        {
            if(!node)
                return;
            printInorderHelper(node->left);
            cout<<node->value<<" ";
            printInorderHelper(node->right);
        }
        Node *searchHelper(Node *node,int key)
        {
            while(node)
            {
                if(node->value == key)
                    return node;
                else if(key < node->value)
                    return searchHelper(node->left,key);
                else
                    return searchHelper(node->right,key);
            }
            return NULL;
        }
        bool deleteKeyHelper(Node *parent,Node *current,int key)
        {
            if(!current)
                return false;
            if(current->value == key)
            {
                if(current->left == NULL || current->right == NULL)
                {
                    Node *temp = current->left;
                    if(current->right)
                        temp = current->right;
                    if(parent)
                    {
                        if(parent->left == current)
                            parent->left = temp;
                        else
                            parent->right = temp;
                    }
                    else
                        this->root = temp;
                }
                else
                {
                    Node *inorderSuccessor = current->right;
                    while(inorderSuccessor->left)
                        inorderSuccessor = inorderSuccessor->left;
                    int temp_val = current->value;
                    current->value = inorderSuccessor->value;
                    inorderSuccessor->value = temp_val;
                    return deleteKeyHelper(current,current->right,temp_val);
                }
                delete current;
                return true;
            }
            if(key < current->value)
                return deleteKeyHelper(current,current->left,key);
            else
                return deleteKeyHelper(current,current->right,key);
        }
    public:
        void printInorder()
        {
            printInorderHelper(root);
        }
        void create()
        {
            root = NULL;
        }
        void insertKey(int key)
        {
            if(root == NULL)
                root = newNode(key);
            else
                insertKeyHelper(root,key);
        }
        Node *searchKey(int key)
        {
            return searchHelper(root,key);
        }
        bool deleteKey(int key)
        {
            deleteKeyHelper(NULL,root,key);
        }
        ~BST()
        {
           root = deleteTree(root);
        }
};

