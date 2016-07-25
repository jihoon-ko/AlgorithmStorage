#include<cstdio>
 
char a[4000004];
 
int f(int x,int y)
{
    return x?x/y+f(x/y,y):0;
}
 
int g(int x,int y,int z)
{
    return y?y&1?(long long)g(x,y^1,z)*x%z:g((long long)x*x%z,y>>1,z):1;
}
 
int main()
{
    int i,j,n,m,l,r=1;
    scanf("%d%d%d",&n,&m,&l);
    for(i=2;i<=n;i++)if(!a[i])
    {
        if(i<2000)for(j=i*i;j<=n;j+=i)a[j]=1;
        r=(long long)g(i,f(n,i)-f(m,i)-f(n-m,i),l)*r%l;
    }
    printf("%d",r);
}
