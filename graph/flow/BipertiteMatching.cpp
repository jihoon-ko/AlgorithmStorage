#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#define MAX_N 5000
using namespace std;
 
vector<int> graph[MAX_N+1];
queue<int> q;
int n,m;
 
int mx[MAX_N+1],my[MAX_N+1];
int lvl[MAX_N+1];
int finlev;
 
bool bfs(){
    bool res=false;
    int now,sz,target;
    finlev=n+100;
    while(!q.empty()) q.pop();
    for(int i=1;i<=n;i++){
        if(mx[i]<0){
            lvl[i]=0;
            q.push(i);
        }else{
            lvl[i]=finlev;
        }
    }
    while(!q.empty()){
        now=q.front();q.pop();
        //printf("%d %d\n",now,lvl[now]);
        sz=graph[now].size();
        if(lvl[now]>finlev) break;
        for(int i=0;i<sz;i++){
            target=my[graph[now][i]];
            if(target<0){
                finlev=lvl[now];
            }else if(lvl[target]==n+100){
                lvl[target]=lvl[now]+1;
                q.push(target);
            }
        }
    }
    //printf("%d\n",finlev);
    return (finlev<(n+100));
}
 
int dfs(int now){
    int sz=graph[now].size(),target;
    for(int i=0;i<sz;i++){
        int target=my[graph[now][i]];
        if(target<0){
            my[graph[now][i]]=now;
            mx[now]=graph[now][i];
            return 1;
        }else if(lvl[target]==lvl[now]+1){
            if(dfs(target)){
                my[graph[now][i]]=now;
                mx[now]=graph[now][i];
                return 1;
            }
        }
    }
    lvl[now]=n+100;
    return 0;
}
 
int hopcroft(){
    int matching=0;
    for(int i=1;i<=MAX_N;i++){
        mx[i]=-1;my[i]=-1;
    }
    while(bfs()){
        for(int i=1;i<=n;i++){
            if(lvl[i]==0) matching+=dfs(i);
        }
        /*
        for(int i=1;i<=n;i++){
            printf("%d ",mx[i]);
        }
        printf("\n");
        */
    }
    return matching;
}
 
int main(){
    int ia,ib;
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&m);
        for(int i=1;i<=n;i++) graph[i].clear();
        for(int i=0;i<m;i++){
            scanf("%d %d",&ia,&ib);
            ia++;ib++;
            graph[ia].push_back(ib);
        }
        printf("%d\n",hopcroft());
    }
}
