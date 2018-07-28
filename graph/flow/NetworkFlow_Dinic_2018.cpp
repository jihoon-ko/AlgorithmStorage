#include<bits/stdc++.h>
using namespace std;

#define inf 1000000000
#define infll 1000000000000000000LL
typedef int flow_t;

struct maxflow{
    maxflow(){}
    struct edge{ int from; int to; flow_t flow; };
    int n;
    int source, sink;
    vector<int> lvl;
    vector<edge> edges;
    vector< vector<int> > eg;
    queue<int> q;
    vector<int> prv;
    vector<int> sv;
    void init(int _n){
        n = _n;
        edges.clear();
        lvl.clear(); lvl.resize(n);
        eg.clear(); eg.resize(n);
        prv.clear(); prv.resize(n);
        sv.clear(); sv.resize(n);
    }
    void add(int from, int to, flow_t flow){
        int idx = (int)edges.size();
        edges.push_back({from, to, flow});
        edges.push_back({to, from, 0   });
        eg[from].push_back(idx);
        eg[to].push_back(idx+1);
    }
    int bfs(){
        for(int i=0;i<n;i++) lvl[i] = inf;
        lvl[source] = 0;
        q.push(source);
        while(!q.empty()){
            int me = q.front(); q.pop();
            for(const int &i: eg[me]){
                const edge &target = edges[i];
                if(target.flow == 0) continue;
                if(lvl[target.to]^inf) continue;
                lvl[target.to] = lvl[me] + 1;
                q.push(target.to);
            }
        }
        return lvl[sink];
    }
    int backtrack(int x, int lim){
        if(x == sink) return lim;
        int used = 0;
        for(sv[x];sv[x]<eg[x].size();sv[x]++){
            const int &i = eg[x][sv[x]];
            const edge &target = edges[i];
            if(target.flow == 0) continue;
            if(lvl[target.to] == lvl[x] + 1){
                int able = min(lim - used, target.flow);
                int res = backtrack(target.to, able);
                if(res){
                    edges[i].flow -= res;
                    edges[i^1].flow += res;
                    used += res;
                    if(lim == used) return used;
                }
            }
        }
        return used;
    }

    flow_t exe(int _source, int _sink){
        source = _source; sink = _sink;
        int ans = 0;
        while(bfs()^inf){
            for(int i=0;i<n;i++) sv[i] = 0;
            int res = backtrack(source, inf);
            ans += res;
        }
        return ans;
    }
};

int main(){
	maxflow mf=maxflow();
	int n,m,aa,bb;
	scanf("%d %d",&n,&m);
	mf.init(n+m+2);
	for(int i=1;i<=n;i++){
		mf.add(0,i,2);
		scanf("%d",&aa);
		while(aa--){
			scanf("%d",&bb);
			mf.add(i,n+bb,1);
		}
	}
	for(int i=n+1;i<=n+m;i++){
		mf.add(i,n+m+1,1);
	}
	printf("%d\n",mf.exe(0,n+m+1));
}
