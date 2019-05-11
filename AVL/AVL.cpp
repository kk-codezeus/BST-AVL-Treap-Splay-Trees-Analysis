#include<bits/stdc++.h>
using namespace std;

struct Node{
    int value;
    Node *left;
    Node *right;
    int height;
    Node(int v):value(v),left(NULL),right(NULL),height(0){}
    Node(int v,Node *l,Node *r,int h):value(v),left(l),right(r),height(h){}
};

class AVL{
    private:
        Node *root;
        Node *deleteTree(Node *node)
        {
             if(node == NULL)
                return NULL;
            node->left = deleteTree(node->left);
            node->right = deleteTree(node->right);

            delete node;
            return NULL;
        }
        void inorderHelper(Node *node)
        {
            if(!node)
                return;
            inorderHelper(node->left);
            cout<<node->value<<" ";
            inorderHelper(node->right);
        }
        void preorderHelper(Node *node)
        {
            if(node != NULL)
            {
                cout<<node->value<<" ";
                preorderHelper(node->left);
                preorderHelper(node->right);
            }
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
        int height(Node *node)
        {
            if(node == NULL)
                return -1;
            return node->height;
        }
        int getBalance(Node *node)
        {
            if(node == NULL)
                return 0;
            return height(node->left) - height(node->right);
        }
        Node *rightRotate(Node *node)
        {
            Node *left = node->left;
            Node *left_right = left->right;

            left->right = node;
            node->left = left_right;

            node->height = 1 + max(height(node->left),height(node->right));
            left->height = 1 + max(height(left->left),height(left->right));
            return left;
        }
        Node *leftRotate(Node *node)
        {
            Node *right = node->right;
            Node *right_left = right->left;

            right->left = node;
            node->right = right_left;

            node->height = 1 + max(height(node->left),height(node->right));
            right->height = 1 + max(height(right->left),height(right->right));
            return right;
        }
        Node *insertKeyHelper(Node *node,int key)
        {
            if(node == NULL)
                return new Node(key,NULL,NULL,0);
            else if(key < node->value)
                node->left = insertKeyHelper(node->left,key);
            else
                node->right = insertKeyHelper(node->right,key);

            node->height = max(height(node->left),height(node->right)) + 1;

            int balance = getBalance(node);
            if(balance > 1 && key < node->left->value)
                return rightRotate(node);
            if(balance < -1 && key >= node->right->value)
                return leftRotate(node);
            if(balance > 1 && key >= node->left->value)
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            if(balance < -1 && key < node->right->value)
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            return node;
        }
        Node *minValueNode(Node *node)
        {
            while(node->left)
                node = node->left;
            return node;
        }
        Node *deleteKeyHelper(Node *node,int key)
        {
            if(node == NULL)
                return node;
            if(key < node->value)
                node->left = deleteKeyHelper(node->left,key);
            else if(key > node->value)
                node->right = deleteKeyHelper(node->right,key);
            else
            {
                if(!(node->left) || !(node->right))
                {
                    Node *temp = (node->left != NULL) ? node->left : node->right;
                    if(!temp)
                    {
                        temp = node;
                        node = NULL;
                    }
                    else
                        *node = *temp;
                    delete temp;
                }
                else
                {
                    Node *inorderSuccessor = minValueNode(node->right);
                    node->value = inorderSuccessor->value;
                    node->right = deleteKeyHelper(node->right,inorderSuccessor->value);
                }
            }

            if(node == NULL)
                return node;

            node->height = 1 + max(height(node->left),height(node->right));

            int balance = getBalance(node);

            if(balance > 1 && getBalance(node->left) >= 0)          // Left-left case
                return rightRotate(node);
            if(balance < -1 && getBalance(node->right) <= 0)        //Right-right case
                return leftRotate(node);
            if(balance > 1 && getBalance(node->left) < 0)           // left-right case
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            if(balance < -1 && getBalance(node->right) > 0)         //right-left case
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
            return node;
        }
    public:
        void create()
        {
            root = NULL;
        }
        Node *searchKey(int key)
        {
            return searchHelper(root,key);
        }
        void insertKey(int key)
        {
            if(root == NULL)
                root = new Node(key,NULL,NULL,0);
            else
                root = insertKeyHelper(root,key);
        }
        void printInorder()
        {
            inorderHelper(root);
        }
        void printPreorder()
        {
            preorderHelper(root);
        }
        bool deleteKey(int key)
        {
            if(searchHelper(root,key) == NULL)
                return false;
            root = deleteKeyHelper(root,key);
            return true;
        }
        ~AVL()
        {
            root = deleteTree(root);
        }
};

