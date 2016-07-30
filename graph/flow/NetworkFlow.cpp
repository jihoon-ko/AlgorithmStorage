#include<cstdio>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#define inf 2100000000
using namespace std;

class edge{
public:
    int from,to,flow,next;
};

const int maxn = 5000;

vector<edge> graph;
int last[maxn+1];

namespace maxflow{
    queue<int> q;
    stack<int> stk;
    int n;
    int lvl[maxn+1];
    int visited[maxn+1];
    int source,sink;
    void buildlgraph(){
        int now,target;
        for(int i=0;i<n;i++) lvl[i]=inf;
        lvl[source]=0;q.push(source);
        while(!q.empty()){
            now=q.front();q.pop();
            for(int i=last[now];i>=0;i=graph[i].next){
                if(!graph[i].flow) continue;
                if(lvl[graph[i].to]^inf) continue;
                target=graph[i].to;
                lvl[target]=lvl[now]+1;
                q.push(target);
            }
        }
        /*
        for(int i=0;i<n;i++) printf("%d ",lvl[i]);
        printf("\n");
        */
    }
    int blockingflow(int now,int pedge,int lim){
        if(!lim) return 0;
        int res = 0;
        visited[now]=1;
        if(now!=sink){
            for(int i=last[now];i>=0;i=graph[i].next){
                if(!graph[i].flow) continue;
                if(visited[graph[i].to]) continue;
                if(lvl[graph[i].to]==lvl[now]+1){
                    res += blockingflow(graph[i].to,i,min(lim-res,graph[i].flow));
                    if(lim==res) break;
                }
            }
        }else res = lim;
        visited[now]=0;
        if(pedge>=0){
            graph[pedge].flow -= res;
            graph[pedge^1].flow += res;
        }
        return res;
    }
    int dinic(int sz,int src,int snk){
        int res=0;n=sz;source=src;sink=snk;
        while(1){
            buildlgraph();
            if(lvl[sink]^inf) res += blockingflow(0,-1,inf);
            else break;
        }
        return res;
    }
};

void BEDGE(int ii,int from,int to,int flow){
    edge imsi;
    imsi.from=from;imsi.to=to;imsi.flow=flow;imsi.next=last[from];graph.push_back(imsi);
    imsi.from=to;imsi.to=from;imsi.flow=0;imsi.next=last[to];graph.push_back(imsi);
    last[from]=ii*2;last[to]=ii*2+1;
}

int main(){
    int edgecnt=0;
    int t;
    scanf("%d",&t);
    while(t--){
        edgecnt=0;
        for(int i=0;i<n*m+2;i++){
            last[i]=-1;
        }
        //BEDGE  something(edgecnt++,from,to,flow)
        printf("%d\n",maxflow::dinic(n*m+2,0,n*m+1));
        graph.clear();
    }
}
