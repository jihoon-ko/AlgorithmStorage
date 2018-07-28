#include<bits/stdc++.h>
using namespace std;

vector<int> g[100001];
int vis[100001];
int cnt = 0;
vector< pair<int,int> > ans;

int dfs(int x, int pp, bool root){
    vis[x] = ++cnt;
    int ret = vis[x];
    int mn = vis[x];
    for(int target: g[x]){
        if(target == pp) continue;
        if(vis[target]){
            ret = min(ret, vis[target]);
        }else{
            int res = dfs(target, x, false);
            mn = min(mn, res);
            ret = min(ret, res);
        }
    }
    if(!root){
        if(ret >= vis[x]){
            ans.push_back(min(make_pair(x, pp), make_pair(pp, x)));
        }
        return ret;
    }
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        int aa,bb;
        scanf("%d%d",&aa,&bb);
        g[aa].push_back(bb); g[bb].push_back(aa);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            dfs(i, i, true);
        }
    }
    sort(ans.begin(), ans.end());
    printf("%u\n", ans.size());
    for(auto &dap: ans) printf("%d %d\n", dap.first, dap.second);
    printf("\n");
}

