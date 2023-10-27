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


int main(){
    int n = scd(), q = scd();
    vector<vector<int>> G(n + 1);
    vector<vector<pair<int,int>>> Query(n + 1);
    repI(i, 1, n - 1) {
        int u = scd();
        G[u].push_back(i + 1);
    }
    vector<int> Ans(q + 1, -1);
    repI(i, 1, q) {
        int x = scd(), k = scd();
        Query[x].push_back({k, i});
    }
    vector<int> AtLevel(n + 1, -1);
    auto dfs = [&](auto self, int u, int par, int level) -> void{
        AtLevel[level] = u;
        for(auto v : Query[u]) {
            int k = v.first;
            int idx = v.second;
            if(level - k >= 0) {
                Ans[idx] = AtLevel[level - k];
            }
        }
        for(auto v : G[u]) {
            if(v == par) continue;
            self(self, v, u, level + 1);
        }
    };
    dfs(dfs, 1, -1, 0);
    repI(i, 1, q) {
        prdL(Ans[i]);
    }
    return 0;
}