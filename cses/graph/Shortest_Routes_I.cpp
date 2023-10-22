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
vector<int> G[lim], W[lim];

// Dijsktra
int main(){
    int n = scd(), m = scd();
    while(m--) {
        int a = scd(), b = scd();
        G[a].push_back(b);
        W[a].push_back(scd());
    }
    priority_queue<PA, vector<PA>, greater<PA>> Q;
    vector<lld> Dis(n + 1, LLONG_MAX), visit(n + 1, 0);
    Q.emplace(0, 1);
    Dis[1] = 0;
    while(!Q.empty()) {
        auto [dis, u] = Q.top(); Q.pop();
        if(visit[u] == 1) continue;
        visit[u] = 1;
        int sz = G[u].size();
        repI(i, 0, sz - 1) {
            auto [v, weight] = make_pair(G[u][i], W[u][i]);
            if(dis + weight < Dis[v]) {
                Dis[v] = dis + weight;
                Q.emplace(Dis[v], v);
            }
        }
    }
    rep(i, 1, n) prS(Dis[i]);
    return 0;
}