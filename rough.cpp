#include <iostream>
#include <queue>
using namespace std ; 

struct node
{
    int data ; 
    node* left ; 
    node* right ; 

    node( int value )
    {
        data = value ; 
        left = right = NULL ; 
    }
}; 

void inorder( node* root)
{
    if(root == NULL ) return ; 

    inorder(root->left) ; 
    cout<<root->data; 
    inorder(root->right) ; 
}

int main()
{
    int n, right_node , left_node ; 
    cout<<"Enter the root node value : " ;
    cin>>n; 
 
    queue<node*> q ; 
    node* root = new node(n) ; 
    q.push(root) ; 

    while(!q.empty())
    {
        node* temp = q.front() ; 
        q.pop() ; 

        // for left child 
        cout<<"Enter the value of left child node of "<<temp->data<<" : ";
        cin>>left_node ;

        if(left_node != -1 )
        {
            temp->left = new node(left_node) ; 
            q.push(temp->left) ; 
        }


        //for right child 
        cout<<"Enter the value of right childe node of "<<temp->data<<" : ";  
        cin>>right_node ; 

        if(right_node != -1 )
        {
            temp->right = new node(right_node) ; 
            q.push(temp->right) ; 
        }
    }

    inorder(root) ;

}