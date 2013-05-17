/*
 * Problem: [HNOI2004]最佳包裹
 * Time: 2011.06.30
 * Author: dxmtb
 * State: Solved
 * Memo: 偏移+暴力枚举凸包平面
*/
#include <cstdio>
#include <cstdlib>
#include <cmath>

const int MAXN=105;

int N;
double x[MAXN],y[MAXN],z[MAXN];

int main()
{
	freopen("enwrap.in","r",stdin);
	freopen("enwrap.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%lf%lf%lf",x+i,y+i,z+i);
		x[i]+=rand()%100*1e-15;
		y[i]+=rand()%100*1e-15;
		z[i]+=rand()%100*1e-15;
	}
	double re=0;
	for(int i=0;i<N;i++)
		for(int j=i+1;j<N;j++)
			for(int k=j+1;k<N;k++)
			{
				double vx1=x[i]-x[j],vy1=y[i]-y[j],vz1=z[i]-z[j];
				double vx2=x[i]-x[k],vy2=y[i]-y[k],vz2=z[i]-z[k];
				double vx=vy1*vz2-vy2*vz1,vy=vx2*vz1-vx1*vz2,vz=vx1*vy2-vx2*vy1;
				int sta=-1;
				for(int p=0;p<N;p++)
					if (p!=i && p!=j && p!=k)
					{
						double vx3=x[i]-x[p],vy3=y[i]-y[p],vz3=z[i]-z[p];
						double dot=vx*vx3+vy*vy3+vz*vz3;
						if (dot==0)
							continue;
						int ns=-1;
						if (dot<0) ns=0;
						else ns=1;
						if (sta!=-1 && sta!=ns)
							goto OUT;
						sta=ns;
					}
				re+=sqrt(vx*vx+vy*vy+vz*vz)/2;
				OUT:;
			}
	printf("%.6lf\n",re);
	return 0;
}
