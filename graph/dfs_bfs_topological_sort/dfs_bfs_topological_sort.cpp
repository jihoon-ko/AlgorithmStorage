#include<cstdio>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;

int lnk[11][11];
int visited[11];
int before[11];
int n,m;
int count_edge[11];
bool cycle_found=false;
queue<int> q;

void dfs(int now){
    visited[now]=1;
    for(int i=1;i<=n;i++){
        if(lnk[now][i]&&(!visited[i])){
            printf("-> %d ",i);
            dfs(i);
        }
    }
    visited[now]=2;
}

void bfs(int start){
    int now;
    visited[start]=1;
    q.push(start);
    while(!q.empty()){
        now=q.front();
        q.pop();
        for(int i=1;i<=n;i++){
            if(lnk[now][i]&&(!visited[i])){
                visited[i]=1;
                q.push(i);
                printf("-> %d ",i);
            }
        }
    }
}

void find_cycle(int now,int prev){
    int target;
    visited[now]=1;
    for(int i=1;i<=n;i++){
        if(cycle_found) break;
        if(i==prev) continue;
        if(lnk[now][i]){
            if(visited[i]==0){
                before[i]=now;
                find_cycle(i,now);
            }else if(visited[i]==1){
                cycle_found=true;
                printf("Cycle Found! \nCycle Result : %d ",now);
                target=now;
                while(target!=i){
                    target=before[target];
                    printf("<- %d ",target);
                }
            }
        }
    }
    visited[now]=2;
}

void topological_sort(){
    int now;
    bool first=true;
    for(int i=1;i<=n;i++){
        if(!count_edge[i]) q.push(i);
    }
    while(!q.empty()){
        now=q.front();
        q.pop();
        if(first) printf("%d",now);
        else printf(" -> %d",now);
        for(int i=1;i<=n;i++){
            if(lnk[now][i]){
                count_edge[i]--;
                if(!count_edge[i]) q.push(i);
            }
        }
    }
}

void clear_visited_array(){
    for(int i=1;i<=n;i++) visited[i]=0;
}

int main(){
    int ia,ib;
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){
        scanf("%d %d",&ia,&ib);
        lnk[ia][ib]=1;//lnk[ib][ia]=1;
        count_edge[ib]++;
    }
    clear_visited_array();
    printf("DFS Result : 1 ");
    dfs(1);
    printf("\n");
    clear_visited_array();
    printf("BFS Result : 1 ");
    bfs(1);
    printf("\n");
    clear_visited_array();
    find_cycle(1,-1);
    if(!cycle_found) printf("Cycle Not Found!");
    printf("\n");
    if(!cycle_found){
        printf("Cycle is not found, so Let's do topological sort!\n");
        printf("Topological Sort Result : ");
        clear_visited_array();
        topological_sort();
        printf("\n");
    }
}
/*
Test Data
BFS&DFS
8 12
1 2
1 3
2 3
8 5
2 5
3 6
6 7
6 8
8 7
7 4
4 1
2 6
Topological Sort
9 11
1 5
5 6
4 6
4 7
6 7
8 9
7 9
3 8
2 4
4 5
3 5
*/

