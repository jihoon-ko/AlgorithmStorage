#include<bits/stdc++.h>
using namespace std;

int sfx[500005];
int two[500005];
char str[500005];
int n;
int ord[500005];
int nord[500005];
int cnt[500005];
int rnk[500005];
int lcp[500005];
int main(){
    scanf("%s",str);
    n = (int)strlen(str);
    int N = 1;
    int nn = max(n, 26);
    while(N <= n){
        N *= 2;
    }
    for(int i=0;i<n;i++){
        ord[i] = str[i] - 'a' + 1;
        sfx[i] = i;
    }
    for(int ii=1;ii<=N;ii <<= 1){
        memset(cnt, 0, (nn+1) * 4);
        for(int i=0;i<n;i++){
            cnt[ord[min(n, i + ii)]]++;
        }
        for(int i=1;i<=nn;i++){
            cnt[i] += cnt[i-1];
        }
        for(int i=n-1;i>=0;i--){
            two[--cnt[ord[min(n, i + ii)]]] = i;
        }
        memset(cnt, 0, (nn+1) * 4);
        for(int i=0;i<n;i++){
            cnt[ord[i]]++;
        }
        for(int i=1;i<=nn;i++){
            cnt[i] += cnt[i-1];
        }
        for(int i=n-1;i>=0;i--){
            sfx[--cnt[ord[two[i]]]] = two[i];
        }
        nord[sfx[0]] = 1;
        for(int i=1;i<n;i++){
            if(ord[sfx[i]] == ord[sfx[i-1]] && ord[min(n, sfx[i] + ii)] == ord[min(n, sfx[i-1] + ii)]){
                nord[sfx[i]] = nord[sfx[i-1]];
            }else{
                nord[sfx[i]] = nord[sfx[i-1]]+1;
            }
        }
        for(int i=0;i<n;i++){
            ord[i] = nord[i];
        }
        ord[n] = 0;
    }
    for(int i=0;i<n;i++){
        rnk[ord[i]-1] = i;
    }
    int ans = 0;
    for(int i=0;i<n;i++){
        if(ord[i]>1){
            if(ans) ans--;
            int j = rnk[ord[i]-2];
            while(str[i+ans] == str[j+ans] && str[i+ans] && str[j+ans]) ans++;
            lcp[ord[i]-1] = ans;
        }
    }
    for(int i=0;i<n;i++) printf("%d ", rnk[i]+1);
    printf("\nx ");
    for(int i=1;i<n;i++) printf("%d ", lcp[i]);
    printf("\n");
}
