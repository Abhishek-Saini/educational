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

lld A[lim];

// 2 - SAT
// Finding solution too
int main(){
    int n = scd(), m = scd();
    int nodes = 2 * m;
    StrongDAG dag(nodes);
    auto complement = [&](int x) {
        return x <= m ? x + m : x - m;
    };
    repI(i, 1, n) {
        auto addWish = [&]() {
            char cio;
            cin >> cio;
            int x = scd();
            return cio == '+' ? x : m + x;
        };
        int a = addWish();
        int b = addWish();
        dag.addEdge(complement(a), b);
        dag.addEdge(complement(b), a);
    }
    dag.process();
    auto order = dag.rootNodes;
    map<int,int> pos;
    repI(i, 0, sz(order) - 1) pos[order[i]] = i;
    bool poss = true;
    vector<char> ans;
    repI(i, 1, m) {
        int root_pos = pos[dag.root[i]];
        int root_neg = pos[dag.root[i + m]];
        if(root_pos == root_neg) {
            poss = false;
            break;
        }
        if(root_pos < root_neg) ans.push_back('-');
        else ans.push_back('+');
    }
    if(!poss) {
        cout << "IMPOSSIBLE\n";
    } else {
        for(auto x : ans) cout << x << " ";
        cout << "\n";
    }
    return 0;
}