//============================================================================
// Name        : Assignment5.cpp
// Author      : TEJAS DAHAD
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
#define inf 99999999
using namespace std;
class Graph{
	string off[20];
	int **G;
	int n;
public:
	Graph()
{
		n=0;
}
	void create();
	void display();
	int checkoffice(string s);
	void addline(string s,string s1,int mon);
	void prims();
};
void Graph::create()
{
	cout<<"Enter number of offices\n";
	cin>>n;
	G=new int*[n];
	for(int i=0;i<n;i++)
	{
		G[i]=new int[n];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			G[i][j]=0;
	}
	string s,s1;
	int i=0;
	for(i=0;i<n;i++)
	{
		cout<<"Enter office name\n";
		cin>>s;
		off[i]=s;
	}
	int mon;
	while(1){
		cout<<"Enter phone lines between offices\n";
		cin>>s;
		if(s=="-1")
			break;
		cin>>s1;
		cout<<"Enter money required\n";
		cin>>mon;
		addline(s,s1,mon);
	}
}
void Graph::addline(string s,string s1,int mon)
{
	int i=checkoffice(s);
	int j=checkoffice(s1);
	if(i!=-1&&j!=-1)
	{
		if(G[i][j]==0)
			G[i][j]=G[j][i]=mon;
		else
		{
			cout<<"Do you want to update the price\n";
			cin>>s;
			if(s=="y")
				G[i][j]=G[j][i]=mon;
		}
	}
	else
	{
		cout<<"Office not present\n";
	}
}
int Graph::checkoffice(string s)
{
	for(int i=0;i<n;i++)
	{
		if(off[i]==s)
			return i;
	}
	return -1;
}
void Graph::display()
{
	for(int i=0;i<n;i++)
	{
		cout<<off[i]<<" -> ";
		for(int j=0;j<n;j++)
		{
			if(G[i][j]!=0)
			{
				cout<<off[j]<<" - "<<G[i][j]<<"\t";
			}
		}
		cout<<endl;
	}
}
void Graph::prims()
{
	int *visited,*from,*dist;
	visited=new int[n];
	dist=new int[n];
	from=new int[n];
	int cost[20][20];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(G[i][j]==0)
				cost[i][j]=inf;
			else
				cost[i][j]=G[i][j];
		}
	}
	string start;
	cout<<"Enter start office\n";
	cin>>start;
	int i=checkoffice(start);
	if(i==-1)
	{
		cout<<"Office not present\nEnter again";
		cin>>start;
		i=checkoffice(start);
	}
	visited[i]=1;
	for(int j=0;j<n;j++)
	{
		dist[j]=cost[i][j];
		visited[j]=0;
		from[j]=i;
	}
	visited[i]=1;
	int ne=n-1;
	int v,mincost=0;
	while(ne>0)
	{
		int mindis=inf;
		for(int j=0;j<n;j++)
		{
			if(visited[j]==0&&dist[j]<mindis)
			{
				mindis=dist[j];
				v=j;
			}
		}
		visited[v]=1;
		int u=from[v];
		mincost+=dist[v];
		cout<<off[u]<<" -> "<<off[v]<<" visited\n";
		for(int j=0;j<n;j++)
		{
			if(visited[j]==0&&dist[j]>cost[v][j])
			{
				dist[j]=cost[v][j];
				from[j]=v;
			}
		}
		ne--;
	}
	cout<<"Min cost of spanning tree is "<<mincost<<endl;
}
int main() {
	Graph g;
	string s,s1;
	int choice;
	do{
		cout<<"\nMenu\n1.Create\n2.Add Phoneline\n3.Minimum cost\n4.Display\n";
		cin>>choice;
		switch(choice){
		case 1:
			g.create();
			break;
		case 2:
			cout<<"Enter phone line\n";
			cin>>s>>s1;
			int mon;
			cout<<"ENter money\n";
			cin>>mon;
			g.addline(s,s1,mon);
			break;
		case 3:
			g.prims();
			break;
		case 4:
			g.display();
			break;
		}
	}while(choice!=0);
	return 0;
}
