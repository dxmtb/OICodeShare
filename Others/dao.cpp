#include <iostream>
#include <fstream>
using namespace std;

const int MAXN=10000;

class Node
{
public:
	int a,b,dep;
};

class Queue
{
private:
	int rear,front;
	Node list[MAXN];
public:
	Queue()
	{rear=-1;front=-1;}
	void enqueue(Node x)
	{ 
		for(int i=0;i<=rear;i++)
			if ((list[i].a==x.a)&&(list[i].b==x.b))
				return;
		rear=(rear+1)%MAXN;list[rear]=x;
	}
	Node dequeue()
	{ 
		front=(front+1)%MAXN;
		return list[front];
	}
	bool empty()
	{ return rear==front?true:false;}
}q;


ifstream fin ("dao.in");
ofstream fout ("dao.out");

int main()
{
	int x,y,z;
	fin>>x>>y>>z;
	if (y==z) {fout<<0<<endl;return 0;}
	int a=x,b=0;
	Node begin;
	begin.a=a;
	begin.b=b;
	begin.dep=0;
	q.enqueue(begin);
	while(! q.empty())
	{
		Node temp;
		temp=q.dequeue();
		//向a倒水
		Node now=temp;
		now.a=x;
		now.dep++;
		q.enqueue(now);
		//向b倒水
		now=temp;
		now.b=y;
		now.dep++;
		if (now.b==z) {fout<<now.dep<<endl;return 0;}		
		q.enqueue(now);	
		//a到c
		now=temp;
		now.a=0;
		now.dep++;
		q.enqueue(now);
		//b倒c
		now=temp;
		now.b=0;
		now.dep++;
		q.enqueue(now);		
		//a倒b
		now=temp;
		if (now.b+now.a<y)
		{
			now.b+=now.a;
			now.a=0;
		}
		else 
		{
			now.a=now.a-(y-now.b);
			now.b=y;
		}
		now.dep++;
		if (now.b==z) {fout<<now.dep<<endl;return 0;}		
		q.enqueue(now);	
		//b倒a
		now=temp;
		if (now.b+now.a<x)
		{
			now.a=now.b+now.a;
			now.b=0;
		}
		else 
		{
			now.b=now.b-(x-now.a);
			now.a=x;
		}
		now.dep++;
		if (now.b==z) {fout<<now.dep<<endl;return 0;}		
		q.enqueue(now);			
	}
	fout<<"No solution!";
	return 0;
}
