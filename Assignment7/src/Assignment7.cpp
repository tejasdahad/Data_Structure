//============================================================================
// Name        : Assignment7.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;
int hash(string s);
class node{
	string iden;
	string attr;
	int chain;
public:
	node()
{
		iden="\0";
		attr="\0";
		chain=-1;
}
	friend class symbolTable;
};
class symbolTable{
	node G[30];
public:
	symbolTable()
{

}
	void create(int flag);
	int insertwith(int i,string s);
	void insert(int c);
	int insertwithout(int i,string s);
	void display();
	int find(string s);
	void getattr(string s);
	void modify();
	void deletesym(string s);
};
void symbolTable::create(int flag)
{
	string s,s1;
	cout<<"Keep entering identifiers and value\n";
	while(1)
	{
		cout<<"Enter identifier: ";
		cin>>s;
		if(s=="-1")
			break;
		transform(s.begin(),s.end(),s.begin(),::toupper);
		int i=hash(s);
		if(flag==1)
			i=insertwithout(i,s);
		if(flag==2)
			i=insertwith(i,s);
		cout<<"Enter attribute: ";
		cin>>s1;
		transform(s1.begin(),s1.end(),s1.begin(),::toupper);
		G[i].attr=s1;
	}
}
int symbolTable::insertwithout(int i,string s)
{
	if(G[i].iden=="\0")
	{
		G[i].iden=s;
		return i;
	}
	int j=hash(G[i].iden);
	if(i==j)
	{
		int k=i;
		while(G[k].chain!=-1)
			k=G[k].chain;
		int l=k;
		while(G[l].iden!="\0")
			l=(l+1)%30;
		G[l].iden=s;
		G[k].chain=l;
		return l;
	}
	int k=j;
	do{
		int m=hash(G[k].iden);
		if(i==m)
		{
			break;
		}
		k=(k+1)%30;
	}while(k!=j);
	if(k==j)
	{
		while(G[k].iden!="\0")
			k=(k+1)%30;
		G[k].iden=s;
		return k;
	}
	else
	{
		int l=k;
		while(G[l].chain!=-1)
			l=G[l].chain;
		while(G[l].iden!="\0")
			l=(l+1)%30;
		G[l].iden=s;
		G[k].chain=l;
		return l;
	}
}
int symbolTable::insertwith(int i,string s)
{
	if(G[i].iden=="\0")
	{
		G[i].iden=s;
		return i;
	}
	int j=hash(G[i].iden);
	if(i==j)
	{
		int k=j;
		while(G[k].chain!=-1)
			k=G[k].chain;
		int l=k;
		while(G[l].iden!="\0")
			l=(l+1)%30;
		G[l].iden=s;
		G[k].chain=l;
		return l;
	}
	if(G[j].chain==-1)
	{
		int k=j;
		while(G[k].iden!="\0")
			k=(k+1)%30;
		G[k].iden=G[i].iden;
		G[k].attr=G[i].attr;
		G[i].iden=s;
		return i;
	}
	G[j].chain=G[i].chain;
	while(G[j].chain!=-1)
		j=G[j].chain;
	int k=j;
	while(G[k].iden!="\0")
		k=(k+1)%30;
	G[k].iden=G[i].iden;
	G[k].attr=G[i].attr;
	G[j].chain=k;
	G[i].iden=s;
	G[i].chain=-1;
	return i;
}
void symbolTable::display()
{
	cout<<"Index\tIden\tAttr\tChain\n";
	for(int i=0;i<30;i++)
	{
		if(G[i].iden!="\0")
		{
			cout<<i<<"\t"<<G[i].iden<<"\t"<<G[i].attr<<"\t"<<G[i].chain<<endl;
		}
	}
}
int symbolTable::find(string s)
{
	int i=hash(s);
	int k=i;
	if(i!=hash(G[i].iden))
	{
	do{
		int j=hash(G[k].iden);
		if(i==j)
			break;
		k=(k+1)%30;
	}while(k!=i);
	}
	else
	{
		k=i;
	}
	do
	{
		if(G[k].iden==s)
		{
			cout<<"Identifier found\n";
			return k;
		}
		k=G[k].chain;
	}while(k!=-1);
	cout<<"Not found\n";
	return -1;
}
void symbolTable::insert(int c)
{
	string s1,s2;
	cout<<"Enter Identifier to insert:";
	cin>>s1;
	transform(s1.begin(),s1.end(),s1.begin(),::toupper);
	int i;
	i=hash(s1);
	if(c==1)
		i=insertwithout(i,s1);
	else
		i=insertwith(i,s1);
	cout<<"Enter attribute:";
	cin>>s2;
	transform(s2.begin(),s2.end(),s2.begin(),::toupper);
	G[i].attr=s2;
}
void symbolTable::getattr(string s)
{
	int i=find(s);
	if(i!=-1)
		cout<<"Attribute is "<<G[i].attr<<endl;
	else
	{
		cout<<"Identifier invalid\n";
		return;
	}
}
void symbolTable::modify()
{
	string s1;
	cout<<"Enter symbol to modify:";
	cin>>s1;
	transform(s1.begin(),s1.end(),s1.begin(),::toupper);
	int i=find(s1);
	if(i==-1)
	{
		cout<<"Symbol not present\n";
		return;
	}
	cout<<"Current attribute is "<<G[i].attr<<endl;
	cout<<"Enter new attribute:";
	cin>>s1;
	transform(s1.begin(),s1.end(),s1.begin(),::toupper);
	G[i].attr=s1;
	cout<<"Updated attribute\n";
}
void symbolTable::deletesym(string s1)
{
	int i=find(s1);
	if(i==-1)
	{
		cout<<"Cannot delete symbol\n";
		return;
	}
	int k=0;
	do{
		int j=hash(G[k].iden);
		if(j==hash(s1))
		{
			break;
		}
		k=(k+1)%30;
	}while(k!=0);
	if(i==k)
	{
		G[i].iden=G[i].attr="\0";
		G[i].chain=-1;
		return;
	}
	while(G[k].chain!=i)
		k=G[k].chain;
	G[k].chain=G[i].chain;
	G[i].attr=G[i].iden="\0";
	G[i].chain=-1;
	return;
}

int hash(string s)
{
	return (((int)s[0]-65)%30);
}
int main() {
	symbolTable s;
	string s1,s2;
	int choice,c;
	do{
		cout<<"Menu\n1.Create\n2.Display\n3.Insert\n4.Find\n5.Get Attribute\n6.Modify attribute\n7.Delete symbol\n";
		cin>>choice;
		switch(choice){
		case 1:
			cout<<"1.Without Replacement\n2.With replacement\n";
			cin>>c;
			s.create(c);
			break;
		case 2:
			s.display();
			break;
		case 3:
			s.insert(c);
			break;
		case 4:
			cout<<"Enter symbol to find:";
			cin>>s1;
			transform(s1.begin(),s1.end(),s1.begin(),::toupper);
			cout<<"Index: "<<s.find(s1)<<endl;
			break;
		case 5:
			cout<<"Enter symbol to get attribute:";
			cin>>s1;
			transform(s1.begin(),s1.end(),s1.begin(),::toupper);
			s.getattr(s1);
			break;
		case 6:
			s.modify();
			break;
		case 7:
			cout<<"Enter symbol to delete:";
			cin>>s1;
			transform(s1.begin(),s1.end(),s1.begin(),::toupper);
			s.deletesym(s1);
			break;
		}
	}while(choice!=0);

	return 0;
}
