#include <iostream>
#include <fstream>
using namespace std;

const int MAXN=2000;

struct Student
{
	int id,score;
	Student *pre,*next;
};

Student *head,*tail;

int n;

ifstream fin ("linet.in");
ofstream fout ("linet.out");

int main()
{
	fin>>n;
	int i,x,y;
	Student *p,*q;
	fin>>x>>y;
	head=new Student;
	(*head).pre=NULL;
	(*head).next=NULL;
	(*head).id=x;
	(*head).score=y;
	q=head;
	for(i=1;i<n;i++)
	{
		fin>>x>>y;
		p=new Student;
		(*p).pre=q;
		(*p).next=NULL;
		(*p).id=x;
		(*p).score=y;
		(*q).next=p;
		q=p;
	}
	tail=q;
	int m;
	fin>>m;
	void search(void);
	void insert(void);
	void del(void);
	for(i=1;i<=m;i++)
	{
		int k;
		fin>>k;
		switch(k)
		{
			case 1:search();break;
			case 2:insert();break;
			case 3:del();break;
			default:fout<<"error";
		}
	}
	return 0;
}	

void search()
{
	int k;
	fin>>k;
	if (k==0)
	{
		Student *p=head;
		fout<<n<<endl;
		for(;;) 
		{
			fout<<(*p).id<<" "<<(*p).score<<endl;
			if ((*p).next!=NULL) p=(*p).next;
			else break;
		}
	}
	else
	{
		int id;
		fin>>id;
		Student *p=head;
		for(;((*p).id!=id)&&((*p).next!=NULL);p=(*p).next){}
		if ((*p).id!=id) fout<<"no"<<endl;
		else fout<<(*p).id<<" "<<(*p).score<<endl;
	}
	
}

void insert()
{
	int k;
	fin>>k;
	for(int i=1;i<=k;i++)
	{
		int a,b,c;
		bool flag=true;
		fin>>a>>b>>c;
		Student *p=head;
		for(;;)
		{
			if ((*p).id!=b) {if (((*p).next)!=NULL) p=(*p).next;else break;}
			else {fout<<"dup"<<endl;flag=false;break;}			
		}
		if (flag) 
		{
			if (a!=0) {
			p=head;
			for(int j=1;j<a;j++)
				if ((*p).next!=NULL)
					p=(*p).next;
				else {
					fout<<"out"<<endl;
					return;
				}
			Student *temp=new Student;
			(*temp).id=b;
			(*temp).score=c;
			(*temp).pre=p;
			(*temp).next=(*p).next;
			(*p).next=temp;
			n++;}
			else {
				Student *temp=new Student;
				(*temp).id=b;
				(*temp).score=c;
				(*temp).pre=NULL;
				(*temp).next=head;	
				(*head).pre=temp;
				head=temp;
				n++;
			}
			if ((n==2000)&&(left!=0)) {fout<<"out"<<endl;break;}
		}
	}
	
}

void del()
{
	bool dele[200000];
	memset(dele,false,sizeof(dele));
	int y;
	fin>>y;
	for(int i=1;i<=y;i++)
	{
		int x;
		fin>>x;
		dele[x]=true;
	}
	int left=y;
	Student *p=head;
	for(;left>0;)
	{
		if ((*p).next==NULL) break;
		if (dele[(*p).id]) 
			if (p==head) 
			{
				Student *temp=head;
				head=(*p).next;
				(*head).pre=NULL;
				p=(*p).next;
				delete temp;
				left--;
				n--;
			}
			else 
			{
				Student *temp=p,*fo=(*p).pre;
				(*fo).next=(*p).next;
				p=(*p).next;
				delete temp;
				left--;
				n--;
			}
		else if ((*p).next!=NULL) p=(*p).next;
			 else break;
	}
	if (left>0) fout<<"error"<<endl;
}
