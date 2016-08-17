#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#define inf 2100000000
using namespace std;
 
struct mincostmaxflow{
    typedef int flow_t;
    typedef int cost_t;
    struct edge{
        int to;
        int inv;
        flow_t flow;
        cost_t cost;
    };
    vector< vector<edge> > graph;
    vector<cost_t> dist;
    vector<int> inq;
    vector< pair<cost_t,flow_t> > prev;
    queue<int> q;
    int n;
    int source, sink;
    void init(int n_){
        n = n_;
        graph.resize(n);
        dist.resize(n);
        inq.resize(n);
        prev.resize(n);
    }
    void addedge(int from_,int to_,flow_t flow_,cost_t cost_,flow_t flowrev_=0){
        edge ftot = {to_,graph[to_].size(),flow_,cost_};
        edge ttof = {from_,graph[from_].size(),flowrev_,-cost_};
        graph[from_].push_back(ftot);
        graph[to_].push_back(ttof);
    }
    pair<flow_t,cost_t> spfa(){
        for(int i=0;i<n;i++){
            dist[i] = inf;
            inq[i] = 0;
            prev[i].first=-1;
            prev[i].second=0;
        }
        dist[source] = 0;
        prev[source].second = inf;
        q.push(0);
        inq[0]=1;
        while(!q.empty()){
            int now = q.front();q.pop();
            inq[now]=0;
            for(int i=0;i<graph[now].size();i++){
                edge nowedge = graph[now][i];
                if(nowedge.flow){
                    if(dist[nowedge.to] > dist[now] + nowedge.cost){
                        dist[nowedge.to] = dist[now] + nowedge.cost;
                        prev[nowedge.to].first = now;
                        if(prev[now].second > nowedge.flow) prev[nowedge.to].second = nowedge.flow;
                        else prev[nowedge.to].second = prev[now].second;
                        if(!inq[nowedge.to]){
                            inq[nowedge.to] = 1;
                            q.push(nowedge.to);
                        }
                    }
                }
            }
        }
        return prev[sink];
    }
    int backtrack(){
        int now = sink;
        while(now^source){
            for(int i=0;i<graph[now].size();i++){
                if(graph[now][i].to == prev[now].first){
                    int next = graph[now][i].to;
                    graph[now][i].flow += prev[sink].second;
                    graph[next][graph[now][i].inv].flow -= prev[sink].second;
                    now = next;
                    break;
                }
            }
        }
    }
    pair<flow_t,cost_t> solve(int source_,int sink_){
        pair<flow_t,cost_t> res;
        res.first = 0;
        res.second = 0;
        source = source_;
        sink = sink_;
        while(1){
            pair<flow_t,cost_t> retval = spfa();
            if(!retval.second) break;
            backtrack();
            res.first += retval.second;
            res.second += dist[sink] * retval.second;
        }
        return res;
    }
};
 
int main(){
    setbuf(stdout,NULL);
    mincostmaxflow mcmf=mincostmaxflow();
    int n,m,aa,bb,cc;
    scanf("%d %d",&n,&m);
    mcmf.init(n+m+2);
    for(int i=1;i<=n;i++){
        mcmf.addedge(0,i,1,0);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&aa);
        while(aa--){
            scanf("%d %d",&bb,&cc);
            mcmf.addedge(i,bb+n,1,cc);
        }
    }
    for(int i=n+1;i<=n+m;i++){
        mcmf.addedge(i,n+m+1,1,0);
    }
    pair<int,int> res = mcmf.solve(0,n+m+1);
    printf("%d\n%d\n",res.first,res.second);
}
