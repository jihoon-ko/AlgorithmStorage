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

int hldcnt = 0;
int label[MAXN];
int invlabel[MAXN];
pair<int, int> hldparent[MAXN];

void hld(int me){
    int prv = hldcnt;
    if((me == root) + ((int)g[me].size()) == 1) return;
    int leader = -1;
    for(auto &nxt: g[me]){
        if(nxt == parent[me]) continue;
        if(leader < 0 || treesz[leader] < treesz[nxt]){
            leader = nxt;
        }
    }
    hldcnt++;
    hldparent[hldcnt] = hldparent[prv];
    label[leader] = hldcnt;
    invlabel[hldcnt] = leader;
    hld(leader);
    for(auto &nxt: g[me]){
        if(nxt == parent[me] || nxt == leader) continue;
        hldcnt++;
        hldparent[hldcnt] = {prv, hldcnt};
        label[nxt] = hldcnt;
        invlabel[hldcnt] = nxt;
        hld(nxt);
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
    label[root] = 0;
    invlabel[0] = root;
    hldparent[0] = {0, 1};
    hld(root);
}
