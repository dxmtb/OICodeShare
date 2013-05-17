/*  
ID: dxmtb  
PROG: NOIP2000 进制转换  
TIME: 2010.3.27  
STATE: Solved  
MEMO:模拟
*/  
#include <cstdio>   
using namespace std;   
  
const int MAXN=0xfff;   
  
void print(int x);   
int a,b;   
  
FILE *fin=fopen("fjz.in","r");   
FILE *fout=fopen("fjz.out","w");   
  
int main()    
{   
    while (!feof(fin))   
    {   
		b=0;
        fscanf(fin,"%d%d",&a,&b);  
		if (b==0) return 0;
        fprintf(fout,"%d=",a);   
        if (a!=0) print(a);   
        else fprintf(fout,"0");   
        fprintf(fout,"(base %d)\n",b);   
    }   
    return 0;   
}   
  
void print(int x)   
{   
    if (x==0) return;   
    int rest;   
    if (x>0)   
        if (b>0)rest=x%b,x=x/b;   
        else rest=x%(-b),x=-(x/-b);   
    else    
        if (b>0)   
    {   
        rest=b-(-x)%b;   
        if (rest==b)rest=0,x=-((-x)/b);   
        else x=-(-x)/b-1;   
    }   
        else    
    {   
        rest=-b-(-x)%(-b);   
        if(rest==-b)rest=0,x=(-x)/(-b);   
        else x=(-x)/(-b)+1; 
    }   
    print(x);   
    if (rest<10) fprintf(fout,"%d",rest);   
    else fprintf(fout,"%c",'A'+rest-10);   
}  
