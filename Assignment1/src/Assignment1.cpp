//============================================================================
// Name        : Assignment1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
//#include<queue>
using namespace std;
class BinaryTree;
class node{
	int data;
	node* left;
	node* right;
public:
	node(int x){
		data=x;
		left=NULL;
		right=NULL;
	}
	friend class BinaryTree;
};

template<class T>
class Stack{
	T data[100];
	int top;
public:
	Stack()
{
		top=-1;
}
	void push(T x)
	{
		top++;
		data[top]=x;
	}
	void pop(){
		top--;
	}
	T tops()
	{
		return data[top];
	}
	int empty()
	{
		if(top==-1)
			return 1;
		return 0;
	}
};
class BinaryTree{
	node* root;
public:
	BinaryTree()
{
		root=NULL;
}
	void create();
	void addnode(int x);
	void inorderrec(node* p);
	void preorderrec(node* p);
	void postorderrec(node* p);
	void inorder();
	void preorder();
	void postorder();
	bool compare(BinaryTree T1);
	void leafandinternalnodes();
	void leafrec(node* p);
	void internalrec(node* p);
	void mirror();
	void mirrorrec(node* p);
	void deletenodes();
	node* deletenodesrec(node* p);
	bool comparerec(node* p,node* q);
	void operator=(BinaryTree& T);
	node* equalrec(node* p);
	void displayrec();
	//void leveltraversal();
};
void BinaryTree::create()
{
	int n,x;
	cout<<"Enter number of nodes\n";
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"Enter data\n";
		cin>>x;
		addnode(x);
	}
}
/*void BinaryTree::leveltraversal()
{
	queue<node*>T;
	if(root==NULL)
	{
		cout<<"Empty\n";
		return;
	}
	else
	{
		node* q=root;
		cout<<root->data<<endl;
		do{
			if(q->left!=NULL)
			{
				T.push(q->left);
			}
			if(q->right!=NULL)
			{
				T.push(q->right);
			}
			q=T.front();
			T.pop();
			cout<<q->data<<"\t";
		}while(!T.empty());
	}
}*/
void BinaryTree::addnode(int x)
{
	node* p=new node(x);
	if(root==NULL)
	{
		root=p;
		cout<<"It becomes root\n";
		return;
	}
	node* q=root;
	int flag=0;
	char c;
	do{
		cout<<"Enter which branch you want it to attach\n";
		cin>>c;
		if(c!='l'&&c!='r')
		{
			cout<<"Invalid branch\nRe-enter:";
			cin>>c;
		}
		flag=0;
		if(c=='l')
		{
			if(q->left==NULL)
			{
				q->left=p;
				flag=1;
			}
			else
				q=q->left;
		}
		else
		{
			if(q->right==NULL)
			{
				q->right=p;
				flag=1;
			}
			else
				q=q->right;
		}
	}while(flag==0);

}
void BinaryTree::deletenodes()
{
	root=deletenodesrec(root);
}
node* BinaryTree::deletenodesrec(node* p)
{
	if(p)
	{
		p->left=deletenodesrec(p->left);
		p->right=deletenodesrec(p->right);
		delete p;
		return NULL;
	}
	else
	{
		return NULL;
	}
}
void BinaryTree::displayrec()
{

	if(root==NULL)
	{
		cout<<"Tree is empty\n";
		return;
	}
	cout<<"Inorder:\n";
	inorderrec(root);
	cout<<"Preorder:\n";
	preorderrec(root);
	cout<<"Postorder:\n";
	postorderrec(root);
}
void BinaryTree::inorderrec(node* p)
{
	if(p!=NULL)
	{
		inorderrec(p->left);
		cout<<p->data<<endl;
		inorderrec(p->right);
	}
}
void BinaryTree::preorderrec(node* p)
{
	if(p!=NULL)
	{
		cout<<p->data<<endl;
		preorderrec(p->left);
		preorderrec(p->right);
	}
}

void BinaryTree::postorderrec(node* p)
{
	if(p!=NULL)
	{
		postorderrec(p->left);
		postorderrec(p->right);
		cout<<p->data<<endl;
	}
}
void BinaryTree::inorder()
{
	if(root==NULL)
	{
		cout<<"Tree is empty\n";
		return;
	}
	int flag=0;
	node* p=root;
	Stack<node*>s;
	while(flag==0)
	{
		if(p!=NULL)
		{
			s.push(p);
			p=p->left;
		}
		else
		{
			if(!s.empty())
			{
				p=s.tops();
				s.pop();
				cout<<p->data<<endl;
				p=p->right;
			}
			else
			{
				flag=1;
			}
		}
	}
}
void BinaryTree::preorder()
{
	if(root==NULL)
	{
		cout<<"Tree is empty\n";
		return;
	}
	int flag=0;
	node* p=root;
	Stack<node*>s;
	while(flag==0)
	{
		if(p!=NULL)
		{
			cout<<p->data<<endl;
			s.push(p);
			p=p->left;
		}
		else
		{
			if(!s.empty())
			{
				p=s.tops();
				s.pop();
				p=p->right;
			}
			else
			{
				flag=1;
			}
		}
	}
}
void BinaryTree::postorder()
{
	node* p=root;
	if(p==NULL){
		cout<<"Tree does not exist\n";
		return;
		}
	Stack<node*>s;
	do{
		while(p){
			if(p->right)
			{
				s.push(p->right);
			}
			s.push(p);
			p=p->left;
		}
		p=s.tops();
		s.pop();
		if(p->right && s.tops()==p->right)
		{
			s.pop();
			s.push(p);
			p=p->right;
		}
		else
		{
			cout<<p->data<<endl;
			p=NULL;
		}
	}while(!s.empty());
}
bool BinaryTree::compare(BinaryTree T1)
{
	return comparerec(root,T1.root);
}
bool BinaryTree::comparerec(node* p,node* q)
{
	if(p==NULL&&q==NULL)
		return true;
	else if((p!=NULL&&q==NULL)||(p==NULL&&q!=NULL))
		return false;
	else
	{
		if(p->data==q->data&&comparerec(p->left,q->left)&&comparerec(p->right,q->right))
			return true;
		else
			return false;
	}

}
void BinaryTree::operator =(BinaryTree& T)
{
	root=equalrec(T.root);
}
node* BinaryTree::equalrec(node* p)
{
	if(p!=NULL)
	{
		node* q=new node(p->data);
		q->left=equalrec(p->left);
		q->right=equalrec(p->right);
		return q;
	}
	else
	{
		return NULL;
	}
}
void BinaryTree::leafandinternalnodes()
{
	cout<<"Leaf nodes are:\n";
	leafrec(root);
	cout<<"Internal nodes are:\n";
	internalrec(root);
}
void BinaryTree::leafrec(node* p)
{
	if(p)
	{
		if(p->left==NULL&&p->right==NULL)
		{
			cout<<p->data<<endl;
		}
		leafrec(p->left);
		leafrec(p->right);
	}
}
void BinaryTree::internalrec(node* p)
{
	if(p)
	{
		if(((p->left!=NULL)||(p->right!=NULL))&&(p!=root))
		{
			cout<<p->data<<endl;
		}
		internalrec(p->left);
		internalrec(p->right);
	}
}
void BinaryTree::mirror()
{
	mirrorrec(root);
}
void BinaryTree::mirrorrec(node* p)
{
	if(p)
	{
		mirrorrec(p->left);
		mirrorrec(p->right);
		node* temp=p->left;
		p->left=p->right;
		p->right=temp;
	}
}
int main() {
	BinaryTree bin,t1;
	int choice;
	do{
		cout<<"Enter choice\n1.Create\n2.Display Recursive\n3.Inorder\n4.Preorder\n5.Postorder\n6.Mirror image\n7.Assign\n8.Compare two trees\n9.Print internal and leaf nodes\n10.Delete all nodes\n";
		cin>>choice;
		switch(choice){
		case 1:
			bin.create();
			break;
		case 2:
			bin.displayrec();
			break;
		case 3:
			cout<<"Inorder traversal:\n";
			bin.inorder();
			break;
		case 4:
			cout<<"Preorder traversal:\n";
			bin.preorder();
			break;
		case 5:
			cout<<"Postorder traversal:\n";
			bin.postorder();
			break;
		case 6:
			bin.mirror();
			cout<<"Tree after mirroring:\n";
			bin.inorder();
			break;
		case 7:
			t1=bin;
			t1.displayrec();
			t1.deletenodes();
			break;
		case 8:
			t1.create();
			if(bin.compare(t1))
			{
				cout<<"Trees are equal\n";
			}
			else
			{
				cout<<"Trees are not equal\n";
			}
			break;
		case 9:
			bin.leafandinternalnodes();
			break;
		case 10:
			bin.deletenodes();
			cout<<"All nodes deleted\n";
			bin.inorder();
			break;
		}
	}while(choice!=0);
	return 0;
}
