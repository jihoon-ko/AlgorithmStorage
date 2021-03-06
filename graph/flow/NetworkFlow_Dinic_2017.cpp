#include<bits/stdc++.h>
using namespace std;

#define inf 1000000000
#define infll 1000000000000000000LL
#define target (edges[i])
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
    void init(int _n){
        n = _n;
        edges.clear();
        lvl.clear(); lvl.resize(n);
        eg.clear(); eg.resize(n);
        prv.clear(); prv.resize(n);
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
        for(const int &i: eg[x]){
            if(target.flow == 0) continue;
            if(lvl[target.to] == lvl[x] + 1){
                int able = min(lim - used, target.flow);
                int res = backtrack(target.to, able);
                edges[i].flow -= res;
                edges[i^1].flow += res;
                used += res;
            }
        }
        return used;
    }
    flow_t exe(int _source, int _sink){
        source = _source; sink = _sink;
        int ans = 0;
        while(bfs()^inf){
            int res = backtrack(source, inf);
            ans += res;
        }
        return ans;
    }
};
