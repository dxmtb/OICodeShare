#include <cstdio>
using namespace std;

float a,b,c,d;
int in=0;

float f(float x)
{
	return a*x*x*x+b*x*x+c*x+d;
}

int main()
{
	freopen("3cfc.in","r",stdin);
	freopen("3cfc.out","w",stdout);
	scanf("%f%f%f%f",&a,&b,&c,&d);
	for(int i=-10000;i<=10000&&in<3;i+=1)
	{
		float x=f(i/100.00);
		if (x<=0.01&&x>=-0.01)
		{
			printf("%.2f ",i/100.0);
			in++;
		}
	}
	return 0;
}
