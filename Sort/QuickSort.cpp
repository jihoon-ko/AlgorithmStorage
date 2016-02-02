#include<stdio.h>
#define swap(aa,bb) {int cc=aa;aa=bb;bb=cc;}
int su[1001];

void sort(int s,int e){
    if(s>=e) return;
    int smallidx=s;
    for(int i=s+1;i<=e;i++){
        if(su[s]>su[i]){
            smallidx++;
            swap(su[smallidx],su[i]);
        }
    }
    swap(su[s],su[smallidx]);
    sort(s,smallidx-1);
    sort(smallidx+1,e);
}

int main(){
    int n,sum;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&su[i]);
    }    
    sort(0,n-1);
}
