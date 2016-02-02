#include<stdio.h>
#define MAX_N 100000
#define MAX_SU ~(1 << 31)
int su[MAX_N];
int left[MAX_N];
int right[MAX_N];

void sort(int s,int e){
    if(s>=e) return;
    int mid=(s+e)/2,l=0,r=0;
    sort(s,mid);
    sort(mid+1,e);
    for(int i=s;i<=mid;i++){
        left[i-s]=su[i];
    }
    for(int i=mid+1;i<=e;i++){
        right[i-mid-1]=su[i];
    }
    left[mid+1-s]=MAX_SU;
    right[e-mid]=MAX_SU;
    for(int i=0;i<(e-s+1);i++){
        if(left[l]<right[r]){
            su[i+s]=left[l];
            l++;
        }else{
            su[i+s]=right[r];
            r++;
        }
    }
}

int main(){
    int n,sum;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&su[i]);
    }    
    sort(0,n-1);
}
