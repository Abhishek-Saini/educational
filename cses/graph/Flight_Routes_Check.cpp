#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 
 
using namespace std;
long long mod = 1e9 + 7;
double EPS = 1e-12;
typedef long long int lld;
typedef pair<lld,lld> PA;
long double tick(){static clock_t oldt; clock_t newt=clock();
    long double diff=1.0L*(newt-oldt)/CLOCKS_PER_SEC; oldt = newt; return diff; }
#define rep(i,a,n) for(long long int i = (a); i <= (n); ++i)
#define repI(i,a,n) for(int i = (a); i <= (n); ++i)
#define repD(i,a,n) for(long long int i = (a); i >= (n); --i)
#define repDI(i,a,n) for(int i = (a); i >= (n); --i)
inline lld sc() { lld a; scanf("%lld", &a); return a; }
inline int scd() { int a; scanf("%d", &a); return a; }
#define prL(a) printf("%lld\n",a)
#define prS(a) printf("%lld ",a)
#define prdL(a) printf("%d\n",a)
#define prdS(a) printf("%d ",a)
#define all(c) (c).begin(), (c).end()
#define sz(a) ((int)a.size())
#ifdef LOCAL_RUN
#define Error(x...) { cout << "(" << #x << ")" << " = ( "; printIt(x); }
#else
#define Error(x...) 42
#endif
template <typename T1> void printIt(T1 t1) { cout << t1 << " )" << endl; }
template <typename T1, typename... T2>
void printIt(T1 t1, T2... t2) { cout << t1 << " , "; printIt(t2...); }
#define popcount __builtin_popcountll

#define lim 300010
#define lim2 200010
// std::ios::sync_with_stdio(false); // Ab :)


lld A[lim];

struct StrongDAG{
    StrongDAG(int n) : n(n) {
        G.resize(n + 1);
        revG.resize(n + 1);
        dagG.resize(n + 1);
    }
    void addEdge(int u, int v) {
        G[u].push_back(v);
        revG[v].push_back(u);
    }

    void process() {
        vector<int> visit(n + 1, 0);
        vector<int> order;
        function<void(int)> dfs = [&](int u) {
            if(visit[u] != 0) return;
            visit[u] = 1;
            for(auto v : G[u]) {
                dfs(v);
            }
            order.push_back(u);
        };

        for(int i = 1; i <= n; ++i) {
            if(visit[i] == 0) dfs(i);
        }
        reverse(order.begin(), order.end());

        // Order is here, visit in reverse to find SCC
        visit.assign(n + 1, 0);
        function<void(int, int)> revDfs = [&](int u, int root) {
            if(visit[u] != 0) return;
            visit[u] = root;
            for(auto v : revG[u]) revDfs(v, root);
        };
        dag_n = 0;
        for(auto x : order) {
            if(visit[x] == 0) revDfs(x, x), ++dag_n, rootNodes.push_back(x);
        }

        // create condensed DAG
        // Add edges for root
        root = visit;
        for(int u = 1; u <= n; ++u) {
            for(auto v : G[u]) {
                if(root[u] != root[v]) dagG[root[u]].push_back(root[v]);
            }
        }
    }

    int n, dag_n;
    vector<int> root, rootNodes;
    vector<vector<int>> G, revG, dagG;
};


int main(){
    int n = scd(), m = scd();
    StrongDAG graph(n);
    while(m--) {
        int a = scd(), b = scd();
        graph.addEdge(a, b);
    }
    graph.process();
    if(graph.dag_n == 1) printf("YES\n");
    else printf("NO\n%d %d", graph.rootNodes.back(), graph.rootNodes[graph.dag_n - 2]);
    return 0;
}