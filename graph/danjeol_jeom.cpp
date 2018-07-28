#include<bits/stdc++.h>
using namespace std;

vector<int> g[10001];
int vis[10001];
int cnt = 0;
vector<int> ans;

int dfs(int x, bool root){
    vis[x] = ++cnt;
    int mx = -1;
    int ret = vis[x];
    int cntt = 0;
    for(int target: g[x]){
        if(vis[target]){
            ret = min(ret, vis[target]);
        }else{
            cntt++;
            int res = dfs(target, false);
            mx = max(mx, res);
            ret = min(ret, res);
        }
    }
    if(root){
        if(cntt >= 2){
            ans.push_back(x);
        }
        return -1;
    }else{
        if(mx >= vis[x]){
            ans.push_back(x);
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
            dfs(i, true);
        }
    }
    sort(ans.begin(), ans.end());
    printf("%u\n", ans.size());
    for(int dap: ans) printf("%d ", dap);
    printf("\n");
}

