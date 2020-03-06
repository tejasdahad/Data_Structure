//============================================================================
// Name        : Assignment3.cpp
// Author      : Tejas Dahad
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
class TBT;
class node{
	node *left,*right;
	int data,lbit,rbit;
public:
	node(int x)
{
		data=x;
		left=right=NULL;
		lbit=rbit=1;
}
	friend class TBT;
};
class TBT{
	node* root;
public:
	TBT()
{
		root=new node(-1);
		root->right=root->left=root;
}
	void create();
	void inorder();
	void preorder();
};
void TBT::create()
{
	int n,x,flag;
	char c;
	cout<<"Enter number of nodes\n";
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"Enter data\n";
		cin>>x;
		node* q=new node(x);
		if(root->lbit==1)
		{	
			root->left=q;
			root->lbit=0;
			q->left=root;
			q->right=root;
			cout<<"It becomes root\n";
		}
		else
		{
			node* p=root->left;
			flag=0;
			do{
				cout<<"Enter left or right of"<<p->data;
				cin>>c;
				if(c=='l')
				{
					if(p->lbit==1)
					{
						q->left=p->left;
						q->right=p;
						p->lbit=0;
						p->left=q;
						flag=1;
					}
					else
					{
						p=p->left;
					}
				}
				else
				{
					if(p->rbit==1)
					{
						q->right=p->right;
						q->left=p;
						p->rbit=0;
						p->right=q;
						flag=1;
					}
					else
					{
						p=p->right;
					}
				}
			}while(flag==0);
		}
	}
}
void TBT::inorder()
{
	node* t=root->left;
	while(t->lbit==0)
	{
		t=t->left;
	}
	while(t!=root)
	{
		cout<<t->data<<"\t";
		if(t->rbit==1)
			t=t->right;
		else{
		t=t->right;
		while(t->lbit==0)
			t=t->left;
		}
	}
}
void TBT::preorder()
{
	node* t=root->left;
	while(t!=root)
	{
		cout<<t->data<<"\t";
		if(t->lbit==0)
			t=t->left;
		else
		{
			while(t->rbit==1&&t!=root)
			{
				t=t->right;
			}
			t=t->right;
		}
	}
}
int main() {
	TBT t;
	int choice;
	do{
		cout<<"\nMenu\n1.Create TBT\n2.Inorder traversal\n3.Preorder traversal\n";
		cin>>choice;
		switch(choice){
		case 1:
			t.create();
			break;
		case 2:
			cout<<"Inorder traversal:";
			t.inorder();
			break;
		case 3:
			cout<<"Pre-order traversal:";
			t.preorder();
			break;
		}
	}while(choice!=0);
	return 0;
}
