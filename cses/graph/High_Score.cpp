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

#define lim 1000010
#define lim2 200010
// std::ios::sync_with_stdio(false); // Ab :)


int A[lim];
struct edge{
    int u, v;
    lld weight;
};
edge E[lim];
vector<int> G[lim], R[lim];

// Bellman Ford
int main(){
    int n = scd(), m = scd();
    rep(i, 1, m) {
        E[i].u = scd();
        E[i].v = scd();
        E[i].weight = -sc();
        G[E[i].u].push_back(E[i].v);
        R[E[i].v].push_back(E[i].u);
    }
    auto bfs = [&](int x, vector<int> G[]) {
        vector<bool> visit(n + 1, false);
        queue<int> Q;
        Q.push(x);
        visit[x] = true;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for(auto v : G[u]) {
                if(visit[v]) continue;
                visit[v] = true;
                Q.push(v);
            }
        }
        return visit;
    };
    vector<bool> reachableFrom1 = bfs(1, G);
    vector<bool> reachableFromN = bfs(n, R);
    const lld INF = (lld) n * m * INT_MAX;
    vector<lld> Dis(n + 1, INF);
    Dis[1] = 0;
    bool negCyc = false;
    rep(times, 1, n) {
        rep(i, 1, m) {
            auto [a, b, w] = E[i];
            // INF check ensures only reachable from 1 are takens
            if(Dis[a] < INF && Dis[a] + w < Dis[b]) {
                if(times == n) {
                    if(reachableFrom1[b] && reachableFromN[b]) negCyc = true;
                }
                Dis[b] = Dis[a] + w;
            }
        }
    }
    if(negCyc) {
        printf("-1\n");
        return 0;
    }
    cout << -Dis[n];
    return 0;
}