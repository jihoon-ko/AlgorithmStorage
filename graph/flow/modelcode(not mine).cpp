#include <stdio.h>
#include <vector>
#include <algorithm>
#define FOR(i,n,m) for (int i=(n);i<=(m);i++)
#define si(n) fscanf(in,"%d",&n)
#define sl(n) fscanf(in,"%lld",&n)
#define sd(n) fscanf(in,"%lf",&n)
#define NM 2505
#define MOD 1000000007
#define INF 0x7fffffff
#define vi vector<int>
//FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
FILE *in = stdin, *out = stdout;
#include <climits>
#include <memory.h>
#include <limits>
 
using namespace std;
 
// usage:
// MaxFlowDinic::Init(n);
// MaxFlowDinic::AddEdge(0, 1, 100, 100); // for bidirectional edge
// MaxFlowDinic::AddEdge(1, 2, 100); // directional edge
// result = MaxFlowDinic::Solve(0, 2); // source -> sink
// graph[i][edgeIndex].res -> residual
//
// in order to find out the minimum cut, use `l'.
// if l[i] == 0, i is unrechable.
 
struct MaxFlowDinic
{
    typedef long long flow_t;
 
    struct Edge
    {
        int next;
        int inv; /* inverse edge index */
        flow_t res; /* residual */
    };
 
    int n;
    vector<vector<Edge>> graph;
 
    vector<unsigned> q, l, start;
 
    void Init(int _n) {
        n = _n;
        graph.resize(n);
        for (int i = 0; i < n; i++) graph[i].clear();
    }
    void AddNodes(int count) {
        n += count;
        graph.resize(n);
    }
    void AddEdge(int s, int e, flow_t cap, flow_t caprev = 0) {
        Edge forward = { e, graph[e].size(), cap };
        Edge reverse = { s, graph[s].size(), caprev };
        graph[s].push_back(forward);
        graph[e].push_back(reverse);
    }
 
    bool AssignLevel(int source, int sink) {
        int t = 0;
        memset(&l[0], 0, sizeof(l[0]) * l.size());
        l[source] = 1;
        q[t++] = source;
        for (int h = 0; h < t && !l[sink]; h++) {
            int cur = q[h];
            for (unsigned i = 0; i < graph[cur].size(); i++) {
                int next = graph[cur][i].next;
                if (l[next]) continue;
                if (graph[cur][i].res > 0) {
                    l[next] = l[cur] + 1;
                    q[t++] = next;
                }
            }
        }
        return l[sink] != 0;
    }
 
    flow_t BlockFlow(int cur, int sink, flow_t currentFlow) {
        if (cur == sink) return currentFlow;
        for (unsigned &i = start[cur]; i < graph[cur].size(); i++) {
            int next = graph[cur][i].next;
            if (graph[cur][i].res == 0 || l[next] != l[cur] + 1)
                continue;
            if (flow_t res = BlockFlow(next, sink, min(graph[cur][i].res, currentFlow))) {
                int inv = graph[cur][i].inv;
                graph[cur][i].res -= res;
                graph[next][inv].res += res;
                return res;
            }
        }
        return 0;
    }
 
    flow_t Solve(int source, int sink)
    {
        q.resize(n);
        l.resize(n);
        start.resize(n);
        flow_t ans = 0;
        while (AssignLevel(source, sink)) {
            memset(&start[0], 0, sizeof(start[0])*n);
            while (flow_t flow = BlockFlow(source, sink, numeric_limits<flow_t>::max())) {
                ans += flow;
            }
        }
        return ans;
    }
};
int a[NM][2];
int main()
{
    int n, m;
    si(n), si(m);
    FOR(i, 1, m) {
        si(a[i][0]), si(a[i][1]);
    }
    int left = 0, right = n, mid, ans = INF;
    while (left <= right) {
        MaxFlowDinic mf = MaxFlowDinic();
        mf.Init(n + m + 2);
        mid = (left + right) >> 1;
        FOR(i, 1, m) mf.AddEdge(0, i, 1);
        FOR(i, 1, n) mf.AddEdge(i + m, n + m + 1, mid);
        FOR(i, 1, m) {
            mf.AddEdge(i, m + a[i][0], 1);
            mf.AddEdge(i, m + a[i][1], 1);
        }
        int res = mf.Solve(0, n + m + 1);
        if (res == m) {
            ans = ans < mid ? ans : mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    fprintf(out, "%d", ans);
 
    return 0;
}
