#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#define inf 2100000000LL
using namespace std;

class edge{
public:
    int from,to,flow,weight,next;
};

const int MAXN = 100000;
int last[MAXN+4];
vector<edge> graph;

namespace mcmf{
    long long d[MAXN+5][2];
    int prev[MAXN+5];
    bool checker[MAXN+5];
    queue<int> q;
    int n,qsz;
    long long LLLfactor;
    pair<long long,long long> spfa(int source,int sink){
        pair<long long,long long> retval;
        int target,nxt;
        for(int i=0;i<n;i++){
            d[i][0]=inf;d[i][1]=0;prev[i]=-1;
        }
        d[source][0]=0;d[source][1]=inf;q.push(source);
        LLLfactor = 0;qsz = 1;
        while(qsz){
        	if(qsz!=q.size()) printf("ERR\n");
            target = q.front();
            while(d[target][0] * qsz > LLLfactor){q.pop();q.push(target);target = q.front();}
            q.pop();LLLfactor -= d[target][0];qsz--;checker[target]=0;
            //printf("%d %lld\n",target,d[target][0]);
            for(int i=last[target];i>=0;i=graph[i].next){
            	//printf("%d\n",i);
                if(!graph[i].flow) continue;
                nxt = graph[i].to;
                if(d[nxt][0]>d[target][0]+graph[i].weight){
                    if(checker[nxt]) LLLfactor -= d[nxt][0];
                    else{qsz++;q.push(nxt);checker[nxt]=1;}
                    d[nxt][0]=d[target][0]+graph[i].weight;
                    d[nxt][1]=(d[target][1]<graph[i].flow ? d[target][1] : graph[i].flow);
                    prev[nxt]=i;
                    LLLfactor += d[nxt][0];
                    //printf("push %d %lld %lld %d %lld\n",nxt,d[nxt][0],d[nxt][1],qsz,LLLfactor);
                }
            }
        }
        retval.first = d[sink][1];
        retval.second = d[sink][0];
        return retval;
    }
    void track(int sink,int source,int yang){
        int now = prev[sink];
        while(now>=0){
            graph[now].flow -= yang;
            graph[now^1].flow += yang;
            now = prev[graph[now].from];
        }
    }
    pair<long long,long long> getmcmf(int sz,int source,int sink){
        pair<long long,long long> res;
        pair<long long,long long> midres;
        res.first=0;res.second=0;
        n=sz;
        while(1){
        	midres = spfa(source,sink);
            if(midres.first == 0) break;
            //printf("%lld %lld\n",midres.first,midres.second);
            track(sink,source,(int)midres.first);
            res.first += midres.first;
            res.second += midres.second * midres.first;
        }
        return res;
    }
};

void bedge(int ii,int from,int to,int flow,int weight){
    edge imsi;
    imsi.from=from;imsi.to=to;imsi.flow=flow;imsi.weight=weight;imsi.next=last[from];graph.push_back(imsi);
    imsi.from=to;imsi.to=from;imsi.flow=0;imsi.weight=-weight;imsi.next=last[to];graph.push_back(imsi);
    last[from]=ii*2;last[to]=ii*2+1;
}
