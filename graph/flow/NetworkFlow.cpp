#include<cstdio>
#include<vector>
#include<queue>
#include<string.h>
#define inf 2100000000
using namespace std;

struct maxflow{
	typedef int flow_t;
	struct edge{
		int to;
		int inv;
		flow_t flow;
	};
	vector< vector<edge> > graph;
	vector<int> lvl;
	queue<int> q;
	int n;
	int source, sink;
	void init(int n_){
		n = n_;
		graph.resize(n);
		lvl.resize(n);
	}
	void addedge(int from_,int to_,flow_t flow_,flow_t flowrev_=0){
		edge ftot = {to_,graph[to_].size(),flow_};
		edge ttof = {from_,graph[from_].size(),flowrev_};
		graph[from_].push_back(ftot);
		graph[to_].push_back(ttof);
	}
	int setlvl(){
		for(int i=0;i<n;i++) lvl[i]=inf;
		q.push(source);
		lvl[source]=0;
		while(!q.empty()){
			int now = q.front(); q.pop();
			for(int i=0;i<graph[now].size();i++){
				edge nowedge = graph[now][i];
				if(nowedge.flow){
					if(lvl[nowedge.to]^inf) continue;
					lvl[nowedge.to] = lvl[now] + 1;
					q.push(nowedge.to);
				}
			}
		}
		return lvl[sink];
	}
	int blockingflow(int now,flow_t can_flow){
		flow_t res = 0;
		flow_t retval = 0;
		if(now==sink) return can_flow;
		for(int i=0;i<graph[now].size();i++){
			edge nowedge = graph[now][i];
			if(nowedge.flow && lvl[nowedge.to] == lvl[now] + 1){
				retval = blockingflow(nowedge.to,(can_flow-res<nowedge.flow)?(can_flow-res):nowedge.flow);
				if(retval){
					res += retval;
					graph[now][i].flow -= retval;
					graph[nowedge.to][nowedge.inv].flow += retval;
				}
			}
		}
		return res;
	}
	flow_t dinic(int source_,int sink_){
		source = source_;
		sink = sink_;
		flow_t res = 0;
		while(setlvl()^inf){
			res += blockingflow(source,inf); 
		}
		return res;
	}
};

int main(){
	setbuf(stdout,NULL);
	maxflow mf=maxflow();
	int n,m,aa,bb,k;
	scanf("%d %d %d",&n,&m,&k);
	mf.init(n+m+3);
	mf.addedge(0,n+m+2,k);
	for(int i=1;i<=n;i++){
		mf.addedge(0,i,1);
		mf.addedge(n+m+2,i,inf);
		scanf("%d",&aa);
		while(aa--){
			scanf("%d",&bb);
			mf.addedge(i,n+bb,1);
		}
	}
	for(int i=n+1;i<=n+m;i++){
		mf.addedge(i,n+m+1,1);
	}
	printf("%d\n",mf.dinic(0,n+m+1));
}
