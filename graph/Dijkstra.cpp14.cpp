#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#define inf 100000000

using namespace std;

vector< pair<int,int> > graph[20001];
priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > pq;
int ans[20001];

int main(){
	int n,m,s;
	scanf("%d%d",&n,&m);
	scanf("%d",&s);
	for(int i=0;i<m;i++){
		int from,to,weight;
		scanf("%d%d%d",&from,&to,&weight);
		graph[from].push_back(make_pair(weight,to));
	}
	for(int i=1;i<=n;i++) ans[i] = inf;
	ans[s] = 0;
	pq.push(make_pair(0,s));
	while(!pq.empty()){
		int now_weight = pq.top().first;
		int now_v = pq.top().second;
		pq.pop();
		if(ans[now_v] != now_weight) continue;
		for(int i=0;i<graph[now_v].size();i++){
			int target = graph[now_v][i].second;
			if(ans[target] > ans[now_v] + graph[now_v][i].first){
				ans[target] = ans[now_v] + graph[now_v][i].first;
				pq.push(make_pair(ans[target],target));
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(ans[i] == inf) printf("INF\n");
		else printf("%d\n",ans[i]);
	}
}
