#include<bits/stdc++.h>
using namespace std;

struct Node{
    int value;
    Node *left;
    Node *right;
    double priority;
    Node(int v):value(v),left(NULL),right(NULL)
    {
        priority = (double)rand()/(RAND_MAX);
    }
    Node(int v,Node *l,Node *r,double p):value(v),left(l),right(r),priority(p){}
};

class Treap{
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
            cout<<node->value<<"|"<<node->priority<<endl;
            inorderHelper(node->right);
        }
        void preorderHelper(Node *node)
        {
            if(node != NULL)
            {
                cout<<node->value<<"|"<<node->priority<<endl;
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
        Node *insertKeyHelper(Node *node,int key)
        {
            if(node == NULL)
                return new Node(key);
            else if(key < node->value)
            {
                node->left = insertKeyHelper(node->left,key);
                if(node->left->priority > node->priority)
                    node = rightRotate(node);
            }
            else
            {
                node->right = insertKeyHelper(node->right,key);
                if(node->right->priority > node->priority)
                    node = leftRotate(node);
            }
            return node;
        }
        Node *deleteKeyHelper(Node *node,int key)
        {
            if(node == NULL)
                return node;
            else if(key < node->value)
                node->left = deleteKeyHelper(node->left,key);
            else if(key > node->value)
                node->right = deleteKeyHelper(node->right,key);

            else if(node->left == NULL)
            {
                //cout<<"No left-subtree"<<endl;
                Node *temp = node->right;
                delete node;
                node = temp;
            }
            else if(node->right == NULL)
            {
                //cout<<"No right-subtree"<<endl;
                Node *temp = node->left;
                delete node;
                node = temp;
            }
            else if(node->left->priority > node->right->priority)
            {
                //cout<<"left>right"<<endl;
                node = rightRotate(node);
                node->right = deleteKeyHelper(node->right,key);
            }
            else
            {
                //cout<<"left<right"<<endl;
                node = leftRotate(node);
                node->left = deleteKeyHelper(node->left,key);
            }
            return node;
        }
    public:
        void create()
        {
            root = NULL;
        }
        void printInorder()
        {
            inorderHelper(root);
        }
        void printPreorder()
        {
            preorderHelper(root);
        }
        Node *searchKey(int key)
        {
            return searchHelper(root,key);
        }
        void insertKey(int key)
        {
            if(root == NULL)
                root = new Node(key);
            else
                root = insertKeyHelper(root,key);
        }
        bool deleteKey(int key)
        {
            if(searchHelper(root,key) == NULL)
                return false;
            root = deleteKeyHelper(root,key);
            return true;
        }
        ~Treap()
        {
            root = deleteTree(root);
        }
};
//
//int main()
//{
//    srand(time(0));
//    Treap tree;
//    tree.create();
//    tree.insertKey(50);
//    tree.insertKey(30);
//    tree.insertKey(20);
//    tree.insertKey(40);
//    tree.insertKey(70);
//    tree.insertKey(60);
//    tree.insertKey(80);
//
//    tree.printPreorder();
//    cout<<endl<<endl;
//    tree.printInorder();
//    cout<<endl<<endl;
//
//    tree.deleteKey(50);
//
//    tree.printPreorder();
//    cout<<endl<<endl;
//    tree.printInorder();
//    cout<<endl<<endl;
//}
