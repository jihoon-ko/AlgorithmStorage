#include<cstdio>
#include<algorithm>
#include<vector>
#define MAX_N 10001
using namespace std;

vector<int> graph[MAX_N];
vector<int> scc_result[MAX_N];
int cntsort[MAX_N];

namespace scc{
    int visited_topo[MAX_N+1];
    int visited_scc[MAX_N+1];
    int topo_result[MAX_N+1];
    int scc_group[MAX_N];
    int left;
    int n;
    vector<int> g_t[MAX_N];
    void dfs_topo(int x){
    	visited_topo[x]=1;
    	for(int i=0;i<graph[x].size();i++){
    		if(visited_topo[graph[x][i]]==0){
    			dfs_topo(graph[x][i]);
    		}
    	}
    	topo_result[--left]=x;
    	visited_topo[x]=2;
    }
    
    void dfs_scc(int x,int cnt){
    	//printf("%d %d\n",x,cnt);
    	visited_scc[x]=1;
    	scc_group[x]=cnt;
    	scc_result[cnt].push_back(x);
    	for(int i=0;i<g_t[x].size();i++){
    		if(visited_scc[g_t[x][i]]==0){
    			dfs_scc(g_t[x][i],cnt);
    		}
    	}
    	visited_scc[x]=2;
    }
    
    void do_topo_sort(){
        left = n;
        for(int i=0;i<n;i++){
            if(visited_topo[i]==0) dfs_topo(i);
        }
    }
    
    int do_find_scc(){
    	int scc_count = 0;
    	for(int i=0;i<n;i++){
    		if(visited_scc[topo_result[i]]==0){
    			dfs_scc(topo_result[i],scc_count);
    			scc_count++;
    		}
    	}
    	return scc_count;
    }
    
    int find_scc(int sz){
    	n=sz;
    	for(int i=0;i<n;i++){
    		for(int j=0;j<graph[i].size();j++){
    			g_t[graph[i][j]].push_back(i);
    		}
    		scc_group[i]=MAX_N+11;
    	}
        do_topo_sort();
        return do_find_scc();
    }
};

int main(){
    int n,m,aa,bb;    
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){
        scanf("%d %d",&aa,&bb);
        graph[aa-1].push_back(bb-1);
    }
    int groupcount = scc::find_scc(n);
    for(int i=0;i<groupcount;i++){
    	sort(scc_result[i].begin(),scc_result[i].end());
    	cntsort[scc_result[i][0]]=i+1;
    }
    printf("%d\n",groupcount);
    for(int i=0;i<n;i++){
    	if(cntsort[i]>0){
    		for(int j=0;j<scc_result[cntsort[i]-1].size();j++){
    			printf("%d ",scc_result[cntsort[i]-1][j]+1);
    		}
    		printf("-1\n");
    	}
    }
}
