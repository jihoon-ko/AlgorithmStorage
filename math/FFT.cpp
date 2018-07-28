#include<bits/stdc++.h>
using namespace std;

const int n = (1 << 18);
const int nn = 18;
#define caltype complex<long double>

caltype tk1[n];
caltype tk2[n];

long long sum[n];
caltype anss[n];

long double pi = acosl(-1);

void FFT(caltype *arr, bool mode){
    for(int i=0;i<n;i++){
        int idx = 0;
        for(int j=0;j<nn;j++){
            if(i & (1 << j)) idx += (1 << (nn - 1 - j));
        }
        if(i < idx){
            auto tmp = arr[i];
            arr[i] = arr[idx];
            arr[idx] = tmp;
        }
    }
    for(int i=1;i<n;i <<= 1){
        caltype key;
        if(mode) key = caltype(cos(pi/i), sin(pi/i));
        if(!mode) key = caltype(cos(-pi/i), sin(-pi/i));
        for(int j=0;j<n;j+=(i << 1)){
            caltype gopp = caltype(1, 0);
            for(int k=0;k<i;k++){
                caltype *target = &arr[i | j | k];
                *target = *target * gopp;
                caltype zz = *target;
                arr[i | j | k] = arr[j | k] - zz;
                arr[j | k] += zz;
                gopp *= key;
            }
        }
    }
    if(!mode){
        for(int i=0;i<n;i++) arr[i] /= n;
    }
}

int main(){
    int N,M,L;
    scanf("%d%d%d",&N,&M,&L);
    for(int i=0;i<N;i++){
    	long long aa;
    	scanf("%lld",&aa);
    	long long cal = i; cal *= M; cal %= L;
    	sum[(int)cal] += aa;
    }
    for(int i=0;i<L;i++){
    	tk1[i] = caltype((long double)sum[i], 0);
    	sum[i] = 0;
    }
    for(int i=0;i<M;i++){
    	long long aa;
    	scanf("%lld",&aa);
    	sum[i%L] += aa;
    }
    for(int i=0;i<L;i++){
    	tk2[i] = caltype((long double)sum[i], 0);
    }
    FFT(&tk1[0], true);
    FFT(&tk2[0], true);
    for(int i=0;i<n;i++) tk1[i] *= tk2[i];
    FFT(&tk1[0], false);
    for(int i=0;i<n;i++){
    	anss[i%L] += tk1[i];   
    }
    for(int i=0;i<L;i++){
    	printf("%.0Lf\n", anss[i].real());
    }
}
