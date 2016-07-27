#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<deque>
#define inf 2100000000LL

using namespace std;

class edge{
public:
    int from,to,flow,weight,next;
};

const int MAXN = 100000;
int last[MAXN+4];
vector<edge> graph;

long long d[MAXN+5][2];

namespace mcmf{
    int prev[MAXN+5];
    bool checker[MAXN+5];
    deque<int> q;
    int n,qsz;
    void spfa(int source,int sink){
        int target,nxt;
        for(int i=0;i<n;i++){
            d[i][0]=inf;d[i][1]=0;prev[i]=-1;
        }
        d[source][0]=0;d[source][1]=inf;q.push_back(source);
        qsz = 1;
        while(qsz){
        	if(d[q.front()][0]>d[q.back()][0]){
                target = q.back();
                q.pop_back();
            }else{
                target = q.front();
                q.pop_front();
            }
        	qsz--;checker[target]=0;
            for(int i=last[target];i>=0;i=graph[i].next){
            	if(!graph[i].flow) continue;
                nxt = graph[i].to;
                if(d[nxt][0]>d[target][0]+graph[i].weight){
                    if(!checker[nxt]){qsz++;q.push_back(nxt);checker[nxt]=1;}
                    d[nxt][0]=d[target][0]+graph[i].weight;
                    d[nxt][1]=(d[target][1]<graph[i].flow ? d[target][1] : graph[i].flow);
                    prev[nxt]=i;
                }
            }
        }
    }
    void track(int sink,int source,int yang){
        int now = prev[sink];
        while(now>=0){
            graph[now].flow -= yang;
            graph[now^1].flow += yang;
            now = prev[graph[now].from];
        }
    }
    pair<long long,long long> getmcmf(int sz,int source,int sink,int times){
        pair<long long,long long> res;
        res.first=0;res.second=0;n=sz;
        if(!times) times=-1;
        while(times){
        	spfa(source,sink);
            if(d[sink][1] == 0) break;
            res.first += d[sink][1];
            res.second += d[sink][0] * d[sink][1];
            track(sink,source,(int)d[sink][1]);
            times--;
        }
        return res;
    }
};

void BEDGE(int ii,int from,int to,int flow,int weight){
    edge imsi;imsi.from=from;imsi.to=to;imsi.flow=flow;imsi.weight=weight;imsi.next=last[from];graph.push_back(imsi);
    imsi.from=to;imsi.to=from;imsi.flow=0;imsi.weight=-weight;imsi.next=last[to];graph.push_back(imsi);
    last[from]=ii*2;last[to]=ii*2+1;
}

int main(){
    int t,edgecnt;
    scanf("%d",&t);
    while(t--){
        edgecnt=0;
        BEDGE(edgecnt++,from,to,flow,weight);
        pair<long long,long long> retres=mcmf::getmcmf(n*2+2,0,n*2+1,0 <- times);
        printf("%lld\n",retres.second);
        graph.clear();
    }
}
