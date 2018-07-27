#include<bits/stdc++.h>
using namespace std;

#define inf 1000000000
#define infll 1000000000000000000LL
typedef int flow_t;
typedef long long cost_t;

struct mincostmaxflow{
    struct edge{ int from, to; flow_t flow; cost_t cost; };
    int n;
    int source, sink;
    vector<edge> edges;
    vector< vector<int> > eg;
    queue<int> q;
    vector<bool> inq;
    vector< pair<cost_t,flow_t> > table;
    vector<int> prv;
    mincostmaxflow(){}
    void init(int _n){
        n = _n;
        eg.clear(); eg.resize(_n);
        edges.clear();
        inq.clear(); inq.resize(_n);
        prv.clear(); prv.resize(_n);
        table.clear(); table.resize(_n);
    }
    void add(int from, int to, flow_t flow, cost_t cost){
        eg[from].push_back((int)edges.size());
        edges.push_back({from, to, flow, cost});
        eg[to].push_back((int)edges.size());
        edges.push_back({to, from, 0, -cost});
    }
    pair<cost_t, flow_t> spfa(){
        for(int i=0;i<n;i++){
            inq[i] = false;
            table[i] = {infll, 0};
        }
        inq[source] = true;
        table[source] = {0, -inf};
        q.push(source);
        while(!q.empty()){
            int me = q.front(); q.pop();
            inq[me] = false;
            //printf("%d (%d,%d)\n", me, table[me].first, table[me].second);
            for(const int &i: eg[me]){
                edge target = edges[i];
                if(target.flow == 0) continue;
                pair<cost_t,flow_t> candi = {target.cost + table[me].first, max(table[me].second, -target.flow)};
                if(table[target.to] > candi){
                    table[target.to] = candi;
                    prv[target.to] = i;
                    if(!inq[target.to]){
                        inq[target.to] = true;
                        q.push(target.to);
                    }
                }
            }
        }
        return table[sink];
    }
    void backtrack(pair<cost_t, flow_t> res){
        int me = sink;
        while(me^source){
            int target_edge = prv[me];
            edges[target_edge].flow -= res.second;
            edges[target_edge ^ 1].flow += res.second;
            me = edges[target_edge].from;
        }
    }
    pair<flow_t, cost_t> exe(int _source, int _sink){
        source = _source; sink = _sink;
        pair<flow_t, cost_t> ans = make_pair(0, 0);
        while(true){
            pair<cost_t, flow_t> res = spfa();
            res.second = -res.second;
            if(res.second == 0) break;
            backtrack(res);
            ans.first += res.second;
            ans.second += res.first * res.second;
        }
        return ans;
    }
};

//        mincostmaxflow mcmf = mincostmaxflow();
//        mcmf.init(n+m+2);
//        mcmf.add(0, i, 1, 0);
//        pair<flow_t, cost_t> ans = mcmf.exe(0, n+m+1);
