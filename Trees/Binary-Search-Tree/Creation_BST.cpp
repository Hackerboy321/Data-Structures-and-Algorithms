#include <iostream>
using namespace std;

struct node
{
    int data;
    node *left;
    node *right;

    node(int value)
    {
        data = value;
        left = right = NULL;
    }
};

class BST
{
public:
    // for inserting the node
   node* insertNode(node* currentNode, int x)
    {
        if (currentNode == NULL)
        {
            node* newNode = new node(x);
            return newNode;
        }

        if (x <= currentNode->data)
        {
            currentNode->left = insertNode(currentNode->left, x);
        }
        else
        {
            currentNode->right = insertNode(currentNode->right, x);
        }

        return currentNode;
    }

    // for deleting the node from the tree
    node* deleteNode(node* root , int target)
    {
        // for searching the target 
        
        if(root == NULL) return ; // base condition when the targent element don't exits in the tree

        else if( target < root->data ) 
        {
            root->left = deleteNode(root->left, target ) ; 
            return root; 
        }

        else if( target > root->data ) 
        {
            root->right = deleteNode(root->right, target) ; 
            return root ;
        }

        else 
        {
            // when we found the element now time to delete that node 

            // if the node is a leaf node 

                if(root->left == NULL && root->right) 
                {
                    delete root ; 
                    return NULL ; 
                }

            // if the node has one child node

                else if(root->right == NULL) // the node has left child  
                {
                    node* temp = root->left ; 
                    delete root ; 
                    return temp ; 
                }

                else if(root->left == NULL)
                {
                    node* temp = root->right ; 
                    delete root ; 
                    return temp ; 
                }


            // if the node has two child node

                else
                {
                    // for finding the largest node in the left
                        node* parent = root ; 
                        node* child = root->left ; 

                        while(child->right == NULL)
                        {
                            parent = child ; 
                            child = child->right ; 
                        }

                    

                    // if root != parent
                        if(root != parent)
                        {
                            parent->right = child->left;
                            child->left = root->left;
                            child->right = root->right;
                            delete root ;
                            return child ;
                        }

                    // if root == parent    
                        else
                        {
                            child->right = parent->right ; 
                            delete root;
                            return child ;
                        }

                }
        }
    }

    //for searching 
    node* search(node* root , int target)
    {
        if(root == NULL ) return NULL ;
        
        else if(root->data == target )
        {
            cout<<target<<" is found at "<<root<<" address";
            return root;
        }

        else if( target < root->data) return search(root->left , target ) ; 

        else return search(root->right, target) ; 

     }


    // for traversal 
    void InOrder(node* root )
    {

        if(root == NULL ) return ; 

        InOrder(root->left) ;
        cout<<root->data<<" ";
        InOrder(root->right) ;
    }

};

int main()
{
    BST B;
    node *root = NULL;
    root = B.insertNode(root, 10);
    root = B.insertNode(root, 20);
    root = B.insertNode(root, 13);
    root = B.insertNode(root, 11);
    root = B.insertNode(root, 12);
    root = B.insertNode(root, 5);
    root = B.insertNode(root, 1);
    root = B.insertNode(root, 4);
    root = B.insertNode(root, 7);
    //B.InOrder(root) ; 
    node* found = B.search(root , 11) ;     
}