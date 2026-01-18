#include <iostream>
using namespace std ;

struct Node
{
    int data ; 
    int height ;
    Node *left , *right ; 

    Node(int value)
    {
        data = value ;
        height = 1 ; 
        left = right = NULL ; 
    }
    
} ; 

class AVL
{
    public:


    int getheight( Node* root)
    {
        if(!root) return 0 ; 
        
        return root->height ; 
    }
    
    int getBalanceFactor( Node* root)
    {
        return getheight(root->left) - getheight(root->right) ; 
    }

    Node* LeftRotation(Node* root)
    {
        Node* child = root->left ;
        Node* childRight = child->right ;
        
        child->right = root ; 
        root->left = childRight ;

        root->height = 1+max(getheight(root->left) , getheight(root->right)) ; 
        child->height = 1+max(getheight(child->left) , getheight(child->right)) ; 


        return child ; 
        
    }

    Node* RightRotation(Node* root)
    {
        Node* child = root->right ;
        Node* childLeft = child->left ;

        child->left = root ;
        root->right = childLeft ;

        root->height = 1+max(getheight(root->left) , getheight(root->right)) ; 
        child->height = 1+max(getheight(child->left) , getheight(child->right)) ; 
        
        return child ; 
    }


    Node* insertToAVL(Node* root, int key) 
    {
        if(!root) return new Node(key) ; 
        
        else if( key < root->data) root->left = insertToAVL(root->left , key ) ; 
        
        else if( key > root->data) root->right = insertToAVL(root->right, key ) ;

        else return root ;
        
        
        root->height = 1+max(getheight(root->left) , getheight(root->right)) ; 

        if(getBalanceFactor(root) > 1 && key < root->left->data )
        {
            return RightRotation(root) ; 
        }
        
        else if( getBalanceFactor(root) < -1 && key > root->right->data) 
        {
            return LeftRotation(root) ;
        }

        else if( getBalanceFactor(root) > 1 && key > root->left->data ) 
        {
            root->left = LeftRotation(root->left) ; 
            return RightRotation(root) ;
        }

        else if( getBalanceFactor(root) < -1 && key < root->right->data)
        {
            root->right = RightRotation(root->right) ; 
            return LeftRotation(root) ; 
        }

        else return root ;
        
    }

    Node* deleteNode( Node* root , int target)
    {
        if(!root) return NULL ; 

        else if(target < root->data) root->left = deleteNode(root->left , target );

        else if(target > root->data ) root->right = deleteNode(root->right , target) ; 

        else
        {
            if(!root->left && !root->right) // if the node dose not have any child 
            {
                delete root ; 
                return NULL ; 
            }

            else if(root->left && !root->right ) // if the node has only left child 
            {
                Node* temp = root->left ;
                delete root ; 
                return temp ; 
            }

            else if( !root->left && root->right) // if the node has only right child 
            {
                Node* temp = root->right ; 
                delete root ; 
                return temp ; 
            }

            else // if the node has two child 
            {
                Node* temp = root->left ; 
                
                while(temp->right) 
                {
                    temp = temp->right; 
                }

                root->data = temp->data ; 
                root->left = deleteNode(root->left , root->data) ; 
            }
        }

        root->height = 1+ max(getheight(root->left) , getheight(root->right)) ; 

        // check the unbalance 

        if(getBalanceFactor(root) > 1 && getBalanceFactor(root->left) >= 0 ) // LL unbalance 
        {
            return RightRotation(root) ; 
        } 

        else if( getBalanceFactor(root) < -1 && getBalanceFactor(root->right) <= 0 ) // RR unbalance 
        {
            return LeftRotation(root) ; 
        }

        else if( getBalanceFactor(root) > 1 && getBalanceFactor(root->left) < 0 ) // LR unbalance 
        {
            root->left = LeftRotation(root->left) ; 
            return RightRotation(root) ; 
        }

        else if( getBalanceFactor(root) < -1 && getBalanceFactor(root->right) > 1 ) // RL unbalance 
        {
            root->right = RightRotation(root->right) ; 
            return LeftRotation(root) ; 
        }

        else // no unbalance 
        {
            return root ; 
        }
    }
};