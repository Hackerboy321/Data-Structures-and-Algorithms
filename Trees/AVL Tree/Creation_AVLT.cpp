#include <iostream>
using namespace std ; 

struct node
{
    int data ;
    int height; 
    node* left ; 
    node* right ; 
    
    node(int value )
    {
        data = value ;
        height = 1 ;
        left = right = NULL ;
    }
};

// to calculate the height of root 
    int getHeight( node* root )
    {
        if(!root) return 0 ; 

        return root->height ;
    }

// to calculate the balance Factor node 
int getBalanceFactor( node* root )
    {
        return getHeight(root->left) - getHeight(root->right) ; 
    }

// Rotations 

// Right Rotation 
    node* rightRotation(node* root )
    {
        node* child = root->left ;
        node* childRight = child->right ;

        child->right = root ;
        root->left = childRight ; 

    // Update the height of root and child after rotation 
        root->height = 1 + max(getHeight(root->left) , getHeight(root->right)); 
        child->height = 1+ max(getHeight(child->left) , getHeight(child->right)) ; 

        return child ; 
    }

// Left Rotation
    node* leftRotation(node* root)
    {
        node* child = root->right ; 
        node* childLeft = child->left ;
        
        child->left = root ; 
        root->right = childLeft ; 

    // Update the height of root and child after rotation 
        root->height = 1 + max(getHeight(root->left) , getHeight(root->right)); 
        child->height = 1+ max(getHeight(child->left) , getHeight(child->right)) ; 
        return child ;
    }

node* insertNode( node* root, int key)
{
    // if root dose not exist 
        if(!root)
        {
            return new node(key) ; 
        }

    // if root exist 
        else if(key < root->data) // go to left sub tree
        {
            root->left = insertNode( root->left , key ) ; 
            
        }

        else if( key > root->data)  // go to right sub tree
        {
            root->right = insertNode(root->right, key ) ; 
        }

        // update the height of root 
            root->height = 1 + max(getHeight(root->left) , getHeight(root->right)) ; 

        //check the balance factor 
            int balanceFactor = getBalanceFactor(root) ; 

        // check which type of rotation 

            if(balanceFactor > 1 && key < root->left->data) // LL rotation 
            {
               return  rightRotation(root) ; 
            }

            else if(balanceFactor < -1 && key > root->right->data) //  RR rotation 
            {
                return leftRotation(root) ; 
            }

            else if(balanceFactor > 1 && key > root->left->data) //  LR rotation
            {
                root->left =  leftRotation(root->left) ;
                return rightRotation(root)  ; 
        
            }

            else if(balanceFactor < -1 && key < root->right->data ) // LR rotation
            {
                root->right = rightRotation(root->right) ; 
                return leftRotation(root) ;  
            }

            else 
            {
                return root ; // tree is balanced
            }
}


node* deleteNode( node* root , int target )
{
    // if the target node 
        if(!root) return NULL ; // target node dose not exist 

        else if( target < root->data)
        {
            root->left = deleteNode(root->left, target) ; 
            
        }

        else if( target > root->data)
        {
            root->right = deleteNode(root->right , target) ; 
           
        }

        else // the target node is found  so now check what kind of node it is 
        {
            // leaf node
                if(root->left == NULL &&  root->right == NULL) 
                {
                    delete root ;
                    return root ; 
                }
            // node having one child 
                if(root->right == NULL) // means node has left child 
                {
                    node* temp = root->left ;
                    delete root ; 
                    return temp ; 
                }

                if(root->left == NULL ) // means node has right child 
                {
                    node* temp = root->right ;
                    delete root ; 
                    return temp ; 
                }

            // node having two child
                else  // if nothing from above so it means it node having two child 
                {
                    node* parent = root ; 
                    node* child = root->left ; 

                    while(root->right == NULL) // find largest number in in left sub tree 
                    {
                        parent = child ;
                        child = root->right ; 
                    }


                    if(root != parent )
                    {
                        parent->right = child->left ;
                        child->left = root->left ; 
                        child->right = root->right ;

                        delete root ;
                        return child ; 
                    }

                    else 
                    {
                        child->right = root->right ;
                        delete root ; 
                        return child ; 

                    }
                }

            root->height = 1 + max(getHeight(root->left) , getHeight(root->right)) ; 
            
   

            // check the type of unbalance 

            // LL Unbalance
                if(getBalanceFactor(root) > 1 && getBalanceFactor(root->left) > 0 ) 
                {
                    return rightRotation(root) ; 
                }
            // RR Unbalance
                else if(getBalanceFactor(root) < -1 && getBalanceFactor(root->right) < 0) // the deleted node is leftNode  ;
                {
                    return leftRotation(root) ; 
                }
            // LR Unbalance
                else if(getBalanceFactor(root) > 1 && getBalanceFactor(root->left)< 0 ) 
                {
                    root->left = leftRotation(root->left) ;  
                    return rightRotation(root) ; 
                }
            // RL Unbalance
                else if(getBalanceFactor(root) < -1 && getBalanceFactor(root->right) > 0) 
                {
                    root->right = rightRotation(root->right) ; 
                    return leftRotation(root) ; 
                }
            // if there is no unbalancing 
                else 
                {
                    return root ;
                }
            
        }
}

// traversal 

void preOrder(node* root)
{
    if(!root ) return ; 

    cout<<root->data<<" "; 
    preOrder(root->left) ; 
    preOrder(root->right) ; 
}

void inOrder(node* root)
{
    if(!root) return ; 

    inOrder(root->left) ; 
    cout<<root->data<<" "; 
    inOrder(root->right) ; 
}

void postOrder(node* root)
{
    if(!root) return ; 

    postOrder(root->left) ;
    postOrder(root->right) ; 
    cout<<root->data<<" " ;  
}

int main()
{
    node* root = NULL ;
    root = insertNode(root,50);
    root = insertNode(root,60);
    root = insertNode(root,65);
    root = insertNode(root,70);
    root = insertNode(root,75);
    root = insertNode(root,80);
    root = insertNode(root,85);
    root = insertNode(root,90);
    root = insertNode(root,95);

    cout<<"Pre Order : "; 
    preOrder(root) ; 
    cout<<endl ; 

    cout<<"In Order : " ;
    inOrder(root) ; 
    cout<<endl ;

    cout<<"Post Order : " ; 
    postOrder(root) ; 
    cout<<endl ;
}