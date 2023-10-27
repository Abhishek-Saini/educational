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

// Finding LCA - Lowest Common Ancestor
int main(){
    int n = scd(), q = scd();
    vector<vector<int>> G(n + 1);
    repI(i, 1, n - 1) {
        int u = scd();
        G[u].push_back(i + 1);
    }
    int logN = 20;
    vector<vector<int>> Par(n + 1, vector<int>(logN + 1, 0));
    vector<int> Level(n + 1, 0);
    auto dfs = [&](auto self, int u, int par, int level) -> void{
        Par[u][0] = par;
        repI(i, 1, logN) {
            Par[u][i] = Par[Par[u][i - 1]][i - 1];
        }
        Level[u] = level;
        for(auto v : G[u]) {
            self(self, v, u, level + 1);
        }
    };
    dfs(dfs, 1, 0, 0);
    while(q--) {
        int a = scd(), b = scd();
        if(Level[a] > Level[b]) swap(a, b);
        int diff = Level[b] - Level[a];
        while(diff > 0) {
            int jump = diff & (-diff);
            int bit = __builtin_ctz(jump);
            b = Par[b][bit];
            diff -= jump;
        }
        int bit = logN;
        while(bit >= 0) {
            if(Par[a][bit] != Par[b][bit]) {
                a = Par[a][bit];
                b = Par[b][bit];
            }
            bit--;
        }
        if(a != b) {
            a = Par[a][0];
            b = Par[b][0];
        }
        prdL(a);
    }
    return 0;
}