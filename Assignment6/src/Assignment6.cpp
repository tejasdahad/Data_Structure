//============================================================================
// Name        : Assignment6.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;
int hash(string s);
class Dictionary{
string key[26];
string mean[26];
public:
	Dictionary(){
		for(int i=0;i<26;i++)
		{
			key[i]=mean[i]="\0";
		}
	}
	void create(int flag);
	int insertwith(int i,string s);
	int insertwithout(int i,string s);
	void insert();
	void display();
	void find(string s);
	void deletekey();
};
void Dictionary::create(int flag){
	while(1)
	{
		string s,s1;
		cout<<"Enter key:";
		cin>>s;
		if(s=="-1")
			break;
		transform(s.begin(),s.end(),s.begin(),::toupper);
		int i=hash(s);
		cout<<i;
		if(flag==1)
		{
			i=insertwithout(i,s);
			cout<<i;
		}
		if(flag==2)
		{
			i=insertwith(i,s);
			cout<<i;
		}
		if(i==-1)
			return;
		cout<<"Enter value:";
		cin>>s1;
		transform(s1.begin(),s1.end(),s1.begin(),::toupper);
		mean[i]=s1;
	}
}
int Dictionary::insertwithout(int i,string s)
{
	if(key[i]=="\0")
	{
		key[i]=s;
		return i;
	}
	else
	{
		int k=i;
		do{
			if(key[k]=="\0")
			{
				key[k]=s;
				return k;
			}
			k=(k+1)%26;
		}while(k!=i);
		cout<<"Cannot be inserted as no empty space\n";
		return -1;
	}
}
int Dictionary::insertwith(int i,string s)
{
	if(key[i]=="\0")
	{
		key[i]=s;
		return i;
	}
	int j=hash(key[i]);
	if(j==i)
	{
		int k=j;
		do{
			if(key[k]=="\0")
			{
				key[k]=s;
				return k;
			}
			k=(k+1)%26;
		}while(k!=j);
		cout<<"Cannot be inserted as no empty space\n";
		return -1;
	}
	else
	{
		int k=i;
		do
		{
			if(key[k]=="\0")
			{
				key[k]=key[i];
				mean[k]=mean[i];
				key[i]=s;
				return i;
			}
			k=(k+1)%26;
		}while(k!=i);
		cout<<"Cannot be inserted as no empty space\n";
		return -1;
	}
}
void Dictionary::display()
{
	for(int i=0;i<26;i++)
	{
		if(key[i]!="\0")
		{
			cout<<key[i]<<" = "<<mean[i]<<endl;
		}
	}
}
void Dictionary::find(string s)
{
	transform(s.begin(),s.end(),s.begin(),::toupper);
	int i=hash(s);
	if(key[i]==s)
	{
		cout<<key[i]<<"="<<mean[i]<<endl;
		cout<<"Key found\n";
		return;
	}
	int k=i;
	do{
		if(key[k]==s)
		{
			cout<<key[k]<<"="<<mean[k]<<endl;
			cout<<"Key found\n";
			return;
		}
		k=(k+1)%26;
	}while(k!=i);
	cout<<"Key not found\n";
}
void Dictionary::insert()
{
	int i,c;
	string s,s1;
	cout<<"Enter choice\n1.Without replacement\n2.With replacement\n";
	cin>>c;
	cout<<"Enter key to insert\n";
	cin>>s;
	transform(s.begin(),s.end(),s.begin(),::toupper);
	i=hash(s);
	if(c==1)
	{
		i=insertwithout(i,s);
	}
	else
	{
		i=insertwith(i,s);
	}
	cout<<"Enter meaning\n";
	cin>>s1;
	transform(s1.begin(),s1.end(),s1.begin(),::toupper);
	mean[i]=s1;
}
void Dictionary::deletekey()
{
	string s;
	cout<<"Enter key to delete\n";
	cin>>s;
	transform(s.begin(),s.end(),s.begin(),::toupper);
	int i=hash(s);
	if(key[i]==s)
	{
		key[i]="\0";
		mean[i]="\0";
		cout<<"Key deleted\n";
		return;
	}
	int k=i;
	do
	{
		if(key[k]==s)
			break;
		k=(k+1)%26;
	}while(k!=i);
	if(k!=i)
	{
		key[k]="\0";
		mean[k]="\0";
		cout<<"Key deleted\n";
		return;
	}
	cout<<"Key not present\n";
}
int hash(string s)
{
	return (((int)s[0]-65)%26);
}
int main() {
	Dictionary d;
	string s;
	int choice,c;
	do{
		cout<<"Menu\n1.Create\n2.Find\n3.Insert\n4.Delete key\n5.Display";
		cin>>choice;
		switch(choice){
		case 1:
			cout<<"Enter choice\n1.Without replacement\n2.With replacement\n";
			cin>>c;
			d.create(c);
			break;
		case 2:
			cout<<"Enter key to search\n";
			cin>>s;
			d.find(s);
			break;
		case 3:
			d.insert();
			break;
		case 4:
			d.deletekey();
			break;
		case 5:
			d.display();
			break;
		}
	}while(choice!=0);
	return 0;
}
