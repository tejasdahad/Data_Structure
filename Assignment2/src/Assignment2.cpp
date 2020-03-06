//============================================================================
// Name        : Assignment2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<string.h>
using namespace std;
class BST;
class node{
	char *key,*meaning;
	node* left,*right;
public:
	node(char *p,char * q){
		key=new char[50];
		meaning=new char[50];
		strcpy(meaning,q);
		strcpy(key,p);
		left=right=NULL;
	}
	~node()
	{
		delete key;
		delete meaning;
	}
	friend class BST;
};
class BST{
	node* root;
public:
	BST()
{
		root=NULL;
}
	void create();
	node* insert(node* T,char *p,char *q);
	void inorder();
	void inorderrec(node* T);
	void operator=(BST& t);
	node* equalrec(node* p);
	void update(char* p,char *q);
	node* updaterec(node* T,char *p,char* q);
	void deletekey(char *p);
	node* deleterec(node* T,char* p);
	node* findmin(node* p);
	void addkey(char *p,char* q);
	int comparison(char* p);
	int comparerec(node* T,char* p);
	void descend();
	void descending(node* T);
};
node* BST::findmin(node* p)
{
	while(p->left!=NULL)
	{
		p=p->left;
	}
	return p;
}
void BST::create()
{
	char key1[50],mean[50];
	while(1)
	{
		cout<<"Enter keyword:\n";
		cin.getline(key1,48);
		if(strcmp(key1,"-1")==0)
			break;
		cout<<"Enter meaning:\n";
		cin.getline(mean,48);
		//cin.ignore(1);
		root=insert(root,key1,mean);
	}
}
node* BST::insert(node* T,char *p,char* q)
{
	if(T==NULL)
	{
		T=new node(p,q);
		return T;
	}
	if(strcmp(p,T->key)<0)
	{
		T->left=insert(T->left,p,q);
		return T;
	}
	if(strcmp(p,T->key)>0)
	{
		T->right=insert(T->right,p,q);
		return T;
	}
	return T;
}
void BST::inorder()
{
	inorderrec(root);
}
void BST::inorderrec(node* T)
{
	if(T)
	{
		inorderrec(T->left);
		cout<<T->key<<" : "<<T->meaning<<endl;
		inorderrec(T->right);
	}
}
void BST::descend()
{
	descending(root);
}
void BST::descending(node* T)
{
	if(T)
	{
		descending(T->right);
		cout<<T->key<<" : "<<T->meaning<<endl;
		descending(T->left);
	}
}
void BST::operator =(BST& T)
{
	root=equalrec(T.root);
}
node* BST::equalrec(node* p)
{
	if(p!=NULL)
	{
		node* q=new node(p->key,p->meaning);
		q->left=equalrec(p->left);
		q->right=equalrec(p->right);
		return q;
	}
	else
	{
		return NULL;
	}
}
void BST::deletekey(char *p)
{
	root=deleterec(root,p);
}
node* BST::deleterec(node* T,char* p)
{
	if(T==NULL)
	{
		return T;
	}
	if(strcmp(p,T->key)<0)
	{
		T->left=deleterec(T->left,p);
		return T;
	}
	else if(strcmp(p,T->key)>0)
	{
		T->right=deleterec(T->right,p);
		return T;
	}
	if(T->left==NULL&&T->right==NULL)
	{
		delete T;
		return NULL;
	}
	if(T->left==NULL)
	{
		node* q=T->right;
		delete T;
		return q;
	}
	if(T->right==NULL)
	{
		node* q=T->left;
		delete T;
		return q;
	}
	node* q=findmin(T->right);
	strcpy(T->key,q->key);
	T->right=deleterec(T->right,T->key);
	return T;
}
void BST::update(char *p,char* q)
{
	root=updaterec(root,p,q);
}
node* BST::updaterec(node* T,char* p,char* q)
{
	if(T==NULL)
	{
		cout<<"Key not found\n";
		return NULL;
	}
	if(strcmp(p,T->key)<0)
	{
		T->left=updaterec(T->left,p,q);
		return T;
	}
	else if(strcmp(p,T->key)>0)
	{
		T->right=updaterec(T->right,p,q);
		return T;
	}
	strcpy(T->meaning,q);
	return T;
}
void BST::addkey(char* p,char* q)
{
	root=insert(root,p,q);
}
int BST::comparison(char* p)
{
	return comparerec(root,p);
}
int BST::comparerec(node* T,char* p)
{
	if(T==NULL)
	{
		return 0;
	}
	if(strcmp(p,T->key)<0)
	{
		return 1+comparerec(T->left,p);
	}
	else if(strcmp(p,T->key)>0)
	{
		return 1+comparerec(T->right,p);
	}
	return 1;
}
int main() {
	BST b,b1;
	int choice;
	char name[50],name1[50];
	do{
		cout<<"Menu:\n1.Create Dictionary\n2.Delete\n3.Add a keyword\n4.Comparison to Search a keyword\n5.Update\n6.Display\n7.Print in descending order\n8.Assign\n";
		cin>>choice;
		cin.ignore(1);
		switch(choice){
		case 1:
			b.create();
			break;
		case 2:
			cout<<"Enter key to DELETE\n";
			cin.getline(name,48);
			b.deletekey(name);
			break;
		case 3:
			cout<<"Enter key to add\n";
			cin>>name;
			cout<<"Enter meaning\n";
			cin.ignore(1);
			cin.getline(name1,48);
			b.addkey(name,name1);
			break;
		case 4:
			cout<<"Enter a key to search\n";
			cin>>name;
			cout<<"Number of comparisons are:"<<b.comparison(name)<<endl;
			break;
		case 5:
			cout<<"Enter key to update:\n";
			cin.getline(name,48);
			cout<<"Enter updated value\n";
			cin.getline(name1,48);
			b.update(name,name1);
			break;
		case 6:
			b.inorder();
			break;
		case 7:
			b.descend();
			break;
		case 8:
			b1=b;
			cout<<"Another tree is:\n";
			b1.inorder();
			break;
		}
	}while(choice!=0);
	return 0;
}
