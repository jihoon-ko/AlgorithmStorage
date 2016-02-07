#include<cstdio>
#include<string.h>
#include<algorithm>
using namespace std;
int su[2000001];
int mx[2000001];
int main(){
    int n,p=-1,r=-1,q,a,b;
    long long ans=0;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&su[i*2+1]);
    }
    int en=2*n;
    for(int i=1;i<en;i++){
        if(r<i){
            mx[i]=0;
        }else{
            mx[i]=min(r-i,mx[2*p-i]);
        }
        while(i-mx[i]-1>0&&i+mx[i]+1<en&&su[i-mx[i]-1]==su[i+mx[i]+1]){
            mx[i]++;
        }
        if(i+mx[i]>r){
        	r=i+mx[i];
        	p=i;
        }
        /*
        //printf("%d ",mx[i]);
        if(i%2){
        	ans+=(mx[i]/2)+1;
        //	printf("%d\n",mx[i]/2+1);
        }else{
        	ans+=(mx[i]+1)/2;
        //	printf("%d\n",(mx[i]+1)/2);
        }
        */
    }
    //printf("%lld",ans);
    scanf("%d",&q);
    for(int i=0;i<q;i++){
        scanf("%d %d",&a,&b);
        printf("%d\n",(mx[a+b-1]>=b-a));
    }
}
