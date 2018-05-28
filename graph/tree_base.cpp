#include<bits/stdc++.h>
#define MAXN 100001
using namespace std;

vector<int> g[MAXN];
int root = 1;

int treesz[MAXN];
int lvl[MAXN];
int parent[MAXN];

void maketree(int me){
    treesz[me] = 1;
    for(auto &nxt: g[me]){
        if(nxt == parent[me]) continue;
        parent[nxt] = me; lvl[nxt] = lvl[me] + 1;
        maketree(nxt);
        treesz[me] += treesz[nxt];
    }
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int aa, bb;
        scanf("%d%d",&aa,&bb);
        g[aa].push_back(bb);
        g[bb].push_back(aa);
    }
    lvl[root] = 0; parent[root] = -1;
    maketree(root);
}
