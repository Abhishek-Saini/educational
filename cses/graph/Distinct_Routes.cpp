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

const lld inf = LLONG_MAX/10;

// All augmenting flows but can have reverse edges too
vector<vector<int>> Ans;
vector<int> path;

struct edge {
    int x, y;
    lld cap, flow;
};

struct DinicFlow {
    vector <edge> e;
    vector <int> cur, d;
    vector < vector <int> > adj;
    int n, source, sink;

    DinicFlow() {}

    DinicFlow(int v) {
        n = v;
        cur = vector <int> (n + 1);
        d = vector <int> (n + 1);
        adj = vector < vector <int> > (n + 1);
    }

    void addEdge(int from, int to, lld cap) {
        edge e1 = {from, to, cap, 0};
        edge e2 = {to, from, 0, 0};
        adj[from].push_back(e.size()); e.push_back(e1);
        adj[to].push_back(e.size()); e.push_back(e2);
    }

    void addBiEdge(int from, int to, lld cap) {
        edge e1 = {from, to, cap, 0};
        edge e2 = {to, from, cap, 0};
        adj[from].push_back(e.size()); e.push_back(e1);
        adj[to].push_back(e.size()); e.push_back(e2);
    }

    int bfs() {
        queue <int> q;
        for(int i = 0; i <= n; ++i) d[i] = -1;
        q.push(source); d[source] = 0;
        while(!q.empty() and d[sink] < 0) {
            int x = q.front(); q.pop();
            for(int i = 0; i < (int)adj[x].size(); ++i) {
                int id = adj[x][i], y = e[id].y;
                if(d[y] < 0 and e[id].flow < e[id].cap) {
                    q.push(y); d[y] = d[x] + 1;
                }
            }
        }
        return d[sink] >= 0;
    }

    int dfs(int x, lld flow) {
        if(!flow) return 0;
        if(x == sink) {
            path.push_back(x);
            return flow;
        }
        for(;cur[x] < (int)adj[x].size(); ++cur[x]) {
            int id = adj[x][cur[x]], y = e[id].y;
            if(d[y] != d[x] + 1) continue;
            int pushed = dfs(y, min(flow, e[id].cap - e[id].flow));
            if(pushed) {
                e[id].flow += pushed;
                e[id ^ 1].flow -= pushed;
                path.push_back(x);
                return pushed;
            }
        }
        return 0;
    }

    lld maxFlow(int src, int snk) {
        this->source = src; this->sink = snk;
        lld flow = 0;
        while(bfs()) {
            for(int i = 0; i <= n; ++i) cur[i] = 0;
            path.clear();
            while(int pushed = dfs(source, inf)) {
                flow += pushed;
                Ans.push_back(path);
                path.clear();
            }
        }
        return flow;
    }
};

lld A[lim];

// Finding all distinct routes
int main(){
    int n = scd(), m = scd();
    int source = 1, sink = n;
    DinicFlow df(n);
    while(m--) {
        int a = scd(), b = scd();
        df.addEdge(a, b, 1);
    }
    lld flow = df.maxFlow(source, sink);
    vector<vector<int>> allPaths(flow);
    for(auto &path : allPaths) path.push_back(source);
    while(true) {
        bool edgeTaken = false;
        for(auto &path : allPaths) {
            int u = path.back();
            int cnt = 0, takeId = -1;
            for(auto &id : df.adj[u]) {
                auto &e = df.e[id];
                if(e.flow == 1) {
                    cnt++;
                    takeId = id;
                }
            }
            if(cnt == 1) {
                edgeTaken = true;
                auto &e = df.e[takeId];
                e.flow = 0;
                path.push_back(e.y);
                break;
            }
        }
        if(edgeTaken) {
            continue;
        }
        for(auto &path : allPaths) {
            int u = path.back();
            for(auto &id : df.adj[u]) {
                auto &e = df.e[id];
                if(e.flow == 1) {
                    edgeTaken = true;
                    e.flow = 0;
                    path.push_back(e.y);
                    break;
                }
            }
        }
        if(!edgeTaken) break;
    }
    printf("%lld\n", flow);
    for(auto &path : allPaths) {
        printf("%d\n", sz(path));
        for(auto &x : path) printf("%d ", x);
        printf("\n");
    }
    return 0;
}