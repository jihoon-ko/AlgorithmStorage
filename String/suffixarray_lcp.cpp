#include<cstdio>
#include<string.h>
#include<algorithm>
using namespace std;

char want_str[1048576];

namespace suffixary{
    const int maxlogn = 20;
    int grp[maxlogn+2][(1 << maxlogn)];
    int lcp[1 << maxlogn];
    int sfxary[1 << maxlogn];
    int n;
    void getsfxary(){
        n = (int)strlen(want_str);
        for(int i=0;i<n;i++){
            sfxary[i]=i;
            grp[0][i]=want_str[i];
        }
        grp[0][n]=-1;
        for(int k=0,jisu=1;;k++,jisu <<= 1){
            sort(sfxary,sfxary+n,[&](const int &left,const int &right){
                return (grp[k][left]^grp[k][right])?(grp[k][left]<grp[k][right]):(grp[k][left+jisu]<grp[k][right+jisu]);
            });
            if((1 << k)>=n) break;
            grp[k+1][sfxary[0]]=0;
            grp[k+1][n]=-1;
            for(int i=1;i<n;i++){
                grp[k+1][sfxary[i]]=grp[k+1][sfxary[i-1]]+1;
                if(grp[k][sfxary[i-1]]==grp[k][sfxary[i]]){
                    if(grp[k][sfxary[i-1]+jisu]==grp[k][sfxary[i]+jisu]){
                        grp[k+1][sfxary[i]]=grp[k+1][sfxary[i-1]];
                    }
                }
            }
        }
    }

    void getlcp(){
        int lim=0,left,right;
        while((1 << lim)<n) lim++;
        for(int i=1;i<n;i++){
            lcp[i]=0;
            left = sfxary[i-1];right = sfxary[i];
            for(int j = lim;j >= 0;j--){
                if(grp[j][left]==grp[j][right]){
                    lcp[i] += (1 << j);
                    left += (1 << j);right += (1 << j);
                }
            }
        }
    }
    void getans(){
        getsfxary();
        getlcp();
    }
};

int main(){
    scanf("%s",want_str);
    int len = (int)strlen(want_str);
    suffixary::getans();
    for(int i=0;i<len;i++) printf("%d ",suffixary::sfxary[i]+1);
    for(int i=1;i<len;i++) printf("%d ",suffixary::lcp[i]);
}
