#include <iostream>
#include <fstream>
using namespace std;

class NODE
{
public:
	int father,step;
	short num[3][3];
};

const int way[4][2]={{0,1},{1,0},{-1,0},{0,-1}};

ifstream fin ("8num.in");
ofstream fout ("8num.out");

NODE q[370000],begin,final;

int main()
{
	bool compare(NODE,NODE);
	void print(NODE);	
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			fin>>begin.num[i][j];
	begin.father=0;
	begin.step=1;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			fin>>final.num[i][j];
	if (compare(begin,final))
		{
			fout<<1<<endl;
			print(begin);
			return 0;
		}		
	int rear=-1,front=-1;
	q[++rear]=begin;
	for(;;)
	{
		if (rear==front) 
		{
			fout<<"No solution!"<<endl;
			return 0;
		}
		NODE temp;
		temp=q[++front];
		int dep=front;
		int p1,p2;
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
				if (temp.num[j][k]==0) 
					{p1=j;p2=k;break;}		
		for(int i=0;i<4;i++)
		{
			if ((p1+way[i][0]>2)||(p1+way[i][0]<0)||
				(p2+way[i][1]>2)||(p2+way[i][1]<0))
					continue;
			NODE newno=temp;
			newno.father=dep;
			newno.step=temp.step+1;
			newno.num[p1][p2]=temp.num[p1+way[i][0]][p2+way[i][1]];
			newno.num[p1+way[i][0]][p2+way[i][1]]=0;
			if (compare(newno,final))
			{
				fout<<newno.step-1<<endl;
				print(newno);
				return 0;
			}
			bool flag=true;
			for(int i=0;i<=rear;i++)
				if (compare(newno,q[i])) 
					{
						flag=false;
						break;
					}
			if (flag)
				q[++rear]=newno;
		}
	}
	return 0;
}

bool compare(NODE a,NODE b)
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if (a.num[i][j]!=b.num[i][j])
				return false;
	return true;
}

void print(NODE a)
{
	if (compare(a,begin))
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				fout<<a.num[i][j]<<' ';
		fout<<endl;
	}
	else
	{
 		print(q[a.father]);
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				fout<<a.num[i][j]<<' ';
		fout<<endl;		
	}
}
