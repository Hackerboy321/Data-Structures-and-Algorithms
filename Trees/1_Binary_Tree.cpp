#include <iostream>
#include <queue> 
using namespace std ;

struct node 
{
    int data ;
    node* left ;
    node* right ;

    node(int value )
    {
        data = value ;
        left = right = NULL ;
    }
};

void inorder(node* rootNode)
{
    if(rootNode == NULL) return ; 

    inorder(rootNode->left) ; 
    cout<<rootNode->data ;
    inorder(rootNode->right) ; 
}

int main()
{
    int x ; 
    cout<<"Enter the root element : " ; 
    cin>>x ; 
    int left_child , right_child ;

    queue<node*> q ;
    node* root = new node(x) ;
    q.push(root) ;  

    while(!q.empty())
    {
        node* temp = q.front() ; 
        q.pop() ; 

        
        // left child 
        cout<<"Enter value of"<<temp->data<<"Left_child : " ; 
        cin>>left_child ; 

        if(left_child != -1)
        {
            temp->left = new node(left_child) ; 
            q.push(temp->left) ; 
        }

        
        // Right child 
        cout<<"Enter value of"<<temp->data<<" Right_child : " ; 
        cin>>right_child; 

        if(right_child != -1) 
        {
            temp->right = new node(right_child) ; 
            q.push(temp->right) ; 
        }

    }
}