#include<bits/stdc++.h>
using namespace std;

const int n = (1 << 20);
const int nn = 20;
char str[2][n];
long long token[2][n];

// 17 * (2 ^ 27) + 1
// 3

long long pr;
int aa = 17, bb = 27;
long long root = 3;
// (3 ^ aa) ^ (128) === 1 (mod pr)

long long jegop(long long xx, long long yy){
    long long ans = 1;
    long long gop = xx % pr;
    while(yy){
        if(yy%2 == 1){
            ans = (ans * gop) % pr;
        }
        gop = (gop * gop) % pr;
        yy /= 2;
    }
    return ans;
}

void FFT(long long *arr, bool mode){
    for(int i=0;i<n;i++){
        int idx = 0;
        for(int j=0;j<nn;j++){
            if(i & (1 << j)) idx += (1 << (nn - 1 - j));
        }
        if(i < idx){
            long long tmp = arr[i];
            arr[i] = arr[idx];
            arr[idx] = tmp;
        }
    }
    for(int i=1;i<n;i <<= 1){
        long long key = jegop(3, pr / (i << 1));
        if(!mode) key = jegop(key, pr-2);
        for(int j=0;j<n;j+=(i << 1)){
            long long gopp = 1;
            for(int k=0;k<i;k++){
                long long *target = &arr[i | j | k];
                *target = (*target * gopp) % pr;
                long long zz = *target;
                arr[i | j | k] = (arr[j | k] + pr - zz) % pr;
                arr[j | k] = (arr[j | k] + zz) % pr;
                gopp = (gopp * key) % pr;
            }
        }
    }
    if(!mode){
        long long zz = jegop(n, pr-2);
        for(int i=0;i<n;i++) arr[i] = (arr[i] * zz) % pr;
    }
}

int main(){
    pr = 17;
    for(int i=0;i<27;i++) pr *= 2;
    pr += 1;
    for(int i=0;i<2;i++){
        scanf("%s", str[i]);
        int len = (int)strlen(str[i]);
        for(int j=0;j<len;j++){
            token[i][len-1-j] = (str[i][j] - '0');
        }
    }
    FFT(&token[0][0], true);
    FFT(&token[1][0], true);
    for(int i=0;i<n;i++) token[0][i] *= token[1][i];
    FFT(&token[0][0], false);
    for(int i=0;i<1000000;i++){
        token[0][i+1] += (token[0][i] / 10);
        token[0][i] %= 10;
    }
    bool nonzero = false;
    for(int i=1000000;i>=0;i--){
        if(token[0][i] > 0){
            nonzero = true;
        }
        if(nonzero || (i == 0)) printf("%lld", token[0][i]);
    }
    printf("\n");
}
