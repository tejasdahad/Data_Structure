#include<bits/stdc++.h>
using namespace std;
class vertex;
class Graph;
class edge{
	string city;
	int w;
	edge* next;
	public:
		edge(string p,int we)
		{
			city=p;
			w=we;
			next=NULL;
		}
		friend class vertex;
		friend class Graph;
};
class vertex{
	string city1;
	vertex* down;
	edge* ne;
	public:
		vertex(string city2)
		{
			city1=city2;
			down=NULL;
			ne=NULL;
		}
		friend class Graph;
};
class Graph{
	vertex *G;

	public:
		Graph()
		{
			G=NULL;
		}
		void create();
		void display();
		void addpath(string s,string s1,int t);
		void deletepath(string s,string s1);
		int checkcity(string s);
		int checkpath(vertex* p,string s);
		void addcity(string s);
		void deletecity(string s);
		void indegree();
		void outdegree();
		void DFS(string s,int v[],string arr[]);
		void traversal();
};
void Graph::create()
{
	string s,s1;
	cout<<"Keep entering cities\n";
	while(1)
	{
		cin>>s;
		if(s=="-1")
			break;
		transform(s.begin(), s.end(), s.begin(), ::toupper);
		if(G==NULL)
		{
			G=new vertex(s);
		}
		else
		{
			vertex* p=G;
			while(p->down!=NULL)
			{
				p=p->down;
			}
			p->down=new vertex(s);

		}
	}
	int t;
	while(1)
	{
		cout<<"Enter flight path\n";
		cin>>s>>s1;
		if(s=="-1")
			break;
		cout<<"Enter time taken";
		cin>>t;
		addpath(s,s1,t);
	}
}
int Graph::checkpath(vertex* p,string s)
{
	edge* q=p->ne;
	while(q!=NULL)
	{
		if(q->city==s)
			return 1;
		q=q->next;
	}
	return 0;

}
int Graph::checkcity(string s)
{
	vertex* p;
	p=G;
	while(p!=NULL)
	{
		if(p->city1==s)
		{
			return 1;
		}
		p=p->down;
	}
	return 0;


}
void Graph::addpath(string s,string s1,int t)
{
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
	if(checkcity(s)&&checkcity(s1)){
		vertex* p=G;
		while(p!=NULL)
		{
			if(p->city1==s)
			{
				break;
			}
			p=p->down;
		}
		if(p->ne==NULL)
		{
			p->ne=new edge(s1,t);
		}
		else
		{
			if(checkpath(p,s1))
			{
				cout<<"Path already present\n";
				edge* r=p->ne;
				while(r!=NULL)
				{
					if(r->city==s1)
					{
						char c;
						cout<<"Do you want to update the path(y or n)\n";
						cin>>c;
						if(c=='y')
							r->w=t;
						return;
					}
					r=r->next;
				}
			}
			edge* q;
			q=p->ne;
			while(q->next!=NULL)
			{
				q=q->next;
			}
			q->next=new edge(s1,t);
		}
	}
	else
	{
		cout<<"city not present\n";
	}
}
void Graph::deletepath(string s,string s1)
{
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
	if(checkcity(s)&&checkcity(s1)){
		vertex* p=G;
		while(p!=NULL)
		{
			if(p->city1==s)
			{
				break;
			}
			p=p->down;
		}
		if(checkpath(p,s1)==0)
		{
			cout<<"Path not present\n";
			return;
		}
	if(p->ne->city==s1)
	{
		edge* r=p->ne;
		p->ne=r->next;
		delete r;
	}
	else
	{
		edge* r=p->ne;
		while(r!=NULL)
		{
			if(r->next->city==s1)
			{
				edge* l=r->next;
				r->next=l->next;
				delete l;
				break;
			}
			r=r->next;
		}
	}}
	else
	{
		cout<<"City not present\n";
	}
}
void Graph::deletecity(string s)
{
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	vertex* p=G;
	if(checkcity(s)){
	while(p!=NULL){
		if(checkpath(p,s))
		{
			deletepath(p->city1,s);
		}
		p=p->down;
	}
	p=G;
	if(p->city1==s)
	{
		edge* r=p->ne;
		while(r!=NULL)
		{
			deletepath(p->city1,r->city);
			r=r->next;
		}
		G=p->down;
		delete p;
		return;
	}
	while(p!=NULL)
	{
		if(p->down->city1==s)
		{
			vertex* q=p->down;
			edge* r=q->ne;
			while(r!=NULL)
			{
				deletepath(q->city1,r->city);
				r=r->next;
			}
			p->down=q->down;
			delete q;
			break;
		}
		p=p->down;
	}
	}

}
void Graph::display()
{
	vertex* p;
	p=G;
	while(p!=NULL)
	{
		cout<<p->city1<<" = ";
		{
			edge* q=p->ne;
			while(q!=NULL)
			{
				cout<<q->city<<"-"<<q->w<<"\t";
				q=q->next;
			}
		}
		cout<<endl;
		p=p->down;
	}
}
void Graph::addcity(string s)
{
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	vertex* p=G;
	while(p->down!=NULL)
	{
		if(p->city1==s)
		{
			cout<<"City already present\n";
			return;
		}
		p=p->down;
	}
	if(p->city1==s)
	{
		cout<<"City present\n";
		return;
	}
	p->down=new vertex(s);

}
void Graph::indegree()
{
	vertex* t=G;
	while(t!=NULL)
	{
		int cnt=0;
		vertex* t1=G;
		while(t1!=NULL)
		{
			if(checkpath(t1,t->city1)&&t1->city1!=t->city1)
			{
				cnt++;
			}
			t1=t1->down;
		}
		cout<<"In-degree of "<<t->city1<<" is "<<cnt<<endl;
		t=t->down;
	}
}
void Graph::outdegree()
{
	vertex* t=G;
	while(t!=NULL)
	{
		edge* r=t->ne;
		int cnt=0;
		while(r!=NULL)
		{
			cnt++;
			r=r->next;
		}
		cout<<"Out-degree of "<<t->city1<<" is "<<cnt<<endl;
		t=t->down;
	}
}
void Graph::traversal()
{
	int v[10]={0};
	string arr[20];
	int i=0;
	vertex* t=G;
	while(t!=NULL)
	{
		arr[i]=t->city1;
		i++;
		t=t->down;
	}
	string start_city;
	cout<<"Enter start city:";
	cin>>start_city;
	transform(start_city.begin(), start_city.end(), start_city.begin(), ::toupper);
	DFS(start_city,v,arr);
}
void Graph::DFS(string st,int v[],string arr[])
{
	int c=0;
	while(arr[c]!=st)
	{
		c++;
	}
	cout<<st<<" visited\n";
	v[c]=1;
	vertex* t=G;
	t=G;
	while(t!=NULL)
	{
		if(t->city1==st)
			break;
		t=t->down;
	}
	edge* t1=t->ne;
	while(t1)
	{
		//c=index(t1->city);
		c=0;
		while(arr[c]!=t1->city)
			c++;
		if(v[c]==0)
		{
			DFS(t1->city,v,arr);
		}
		t1=t1->next;
	}
}
int main()
{
	Graph g;
	int choice;
	string s,s1;
	int t;
	do{
		cout<<"Menu\n1.Create\n2.Add Path\n3.Add city\n4.Delete path\n5.Delete city\n6.Display\n7.Indegree\n8.Outdegree\n9.Traversal\n";
		cin>>choice;
		switch(choice){
			case 1:
				g.create();
				break;
			case 2:
				cout<<"Enter path to add\n";
				cin>>s>>s1;
				cout<<"Enter time taken\n";
				cin>>t;
				g.addpath(s,s1,t);
				break;
			case 3:
				cout<<"Enter city to add\n";
				cin>>s;
				g.addcity(s);
				break;
			case 4:
				cout<<"Delete path:";
				cin>>s>>s1;
				g.deletepath(s,s1);
				break;
			case 5:
				cout<<"Delete city:";
				cin>>s;
				g.deletecity(s);
				break;
			case 6:
				g.display();
				break;
			case 7:
				g.indegree();
				break;
			case 8:
				g.outdegree();
				break;
			case 9:
				g.traversal();
				break;
		}
	}while(choice!=0);
	return 0;
}
