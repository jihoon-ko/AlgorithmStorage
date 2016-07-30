#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> tree[10001];
vector<int> lnk[10001];
vector<int> points;
int visited[10001];
int visited_tree[10001];
int lvl[10001];

void maketree(int x){
    visited[x]=1;
    for(int i=0;i<lnk[x].size();i++){
        if(visited[lnk[x][i]]==0){
            tree[x].push_back(lnk[x][i]);
            lvl[lnk[x][i]]=lvl[x]+1;
            maketree(lnk[x][i]);
        }
    }
}

int tree_dfs(int x){
    visited_tree[x]=1;
    int mxlvl = 0;
    int mnlvl = lvl[x];
    for(int i=0;i<tree[x].size();i++){
        int res = tree_dfs(tree[x][i]);
        mxlvl=max(mxlvl,res);
        mnlvl=min(mnlvl,res);
    }
    //printf("%d %d\n",x,mxlvl);
    if(tree[x].size()>0){
    	if(mxlvl>lvl[x]){
    		if(lvl[x]>0) points.push_back(x);
    		else if(lvl[x]==0&&tree[x].size()>1) points.push_back(x);
    	}
    }
    for(int i=0;i<lnk[x].size();i++){
    	mnlvl=min(mnlvl,lvl[lnk[x][i]]+1);
    }
    //printf("%d %d\n",x,mxlvl);
    return mnlvl;
}

int main(){
    int n,m,a,b;
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){
        scanf("%d %d",&a,&b);
        lnk[a].push_back(b);
        lnk[b].push_back(a);
    }
    for(int i=1;i<=n;i++){
        if(visited[i]==0) maketree(i);
    }/*
    for(int i=1;i<=n;i++){
    	for(int j=0;j<tree[i].size();j++) printf("%d ",tree[i][j]);
    	printf("\n");
    }*/
    for(int i=1;i<=n;i++){
        if(visited_tree[i]==0) tree_dfs(i);
    }
    sort(points.begin(),points.end());
    printf("%d\n",points.size());
    for(int i=0;i<points.size();i++) printf("%d ",points[i]);
}
