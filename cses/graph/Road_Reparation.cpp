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
vector<PA> G[lim];

int main(){
    int n = scd(), m = scd();
    rep(i, 1, m) {
        int a = scd(), b = scd(), w = scd();
        G[a].push_back({b, w});
        G[b].push_back({a, w});
    }
    vector<bool> vis(n + 1, false);
    // prim's algorithm
    priority_queue<PA, vector<PA>, greater<PA>> Q;
    Q.push({0, 1});
    lld ans = 0;
    while(!Q.empty()) {
        auto [w, u] = Q.top();
        Q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        ans += w;
        for(auto [v, w] : G[u]) {
            if(!vis[v]) {
                Q.push({w, v});
            }
        }
    }
    if(count(all(vis), true) != n) {
        printf("IMPOSSIBLE\n");
    } else {
        prL(ans);
    }
    return 0;
}