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
vector<int> G[lim], Rev[lim];
vector<lld> W[lim], RevW[lim];

int main(){
    int n = scd(), m = scd();
    vector<int> In(n + 1, 0), visit(n + 1, 0);
    while(m--) {
        int a = scd(), b = scd();
        G[a].push_back(b);
        W[a].push_back(sc());
        Rev[b].push_back(a);
        RevW[b].push_back(W[a].back());
    }
    auto findDisArray = [&](int src, vector<int> G[] = ::G, vector<lld> W[] = ::W) {
        vector<lld> dis(n + 1, 1e18);
        dis[src] = 0;
        priority_queue<PA, vector<PA>, greater<PA>> Q;
        Q.push({0, src});
        while(!Q.empty()) {
            auto u = Q.top(); Q.pop();
            if(dis[u.second] < u.first) continue;
            for(int i = 0; i < sz(G[u.second]); ++i) {
                int v = G[u.second][i];
                lld w = W[u.second][i];
                if(dis[v] > dis[u.second] + w) {
                    dis[v] = dis[u.second] + w;
                    Q.push({dis[v], v});
                }
            }
        }
        return dis;
    };
    auto distFrom1 = findDisArray(1);
    auto distFromN = findDisArray(n, Rev, RevW);
    lld ans = distFrom1[n];
    rep(i, 1, n) rep(j, 0, sz(G[i]) - 1) {
        auto [v, w] = make_pair(G[i][j], W[i][j]);
        Error(i, v, w);
        Error(distFrom1[i], distFromN[v]);
        ans = min(ans, distFrom1[i] + w / 2 + distFromN[v]);
    }
    prL(ans);
    return 0;
}