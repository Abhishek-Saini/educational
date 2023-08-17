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
#define errorpair(a) cout<<#a<<" = ( "<<((a).first)<<" , "<<((a).second)<<" )\n";
#else
#define Error(x...) 42
#define errorpair(a) 42
#endif
template <typename T1> void printIt(T1 t1) { cout << t1 << " )" << endl; }
template <typename T1, typename... T2>
void printIt(T1 t1, T2... t2) { cout << t1 << " , "; printIt(t2...); }
#define mset(a, v) memset(a, v, sizeof(a))
#define popcount __builtin_popcountll

#define lim 300010
#define lim2 200010
// unordered_map<lld,lld>::iterator it; // Ab :)
// std::ios::sync_with_stdio(false);

lld A[lim];
vector<lld> G[lim];

int main(){
    lld n = sc(), mod = sc();
    rep(i,1,n-1) {
        lld u = sc(), v = sc();
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<lld> dp(n+1, 0);
    auto dfs = [&](auto dfs, lld u, lld p) -> void{
        lld& ans = dp[u] = 1;
        for(auto v : G[u]) {
            if(v == p) continue;
            dfs(dfs, v, u);
            ans = (ans * (1 + dp[v])) % mod;
        }
        Error(u, dp[u]);
    };
    dfs(dfs, 1, -1);
    auto findAns = [&](auto findAns, lld u, lld p, lld val) -> void{
        vector<lld> pref;
        lld curr = 1;
        pref.push_back(1);
        for(auto v : G[u]) {
            if(v == p) continue;
            curr = (curr * (1 + dp[v])) % mod;
            pref.push_back(curr);
        }
        lld prefInd = sz(pref) - 2, suff = 1;
        for(int i = sz(G[u]) - 1; i >= 0; --i) {
            lld v = G[u][i];
            if(v == p) continue;
            Error(u, v, prefInd, pref[prefInd], suff, val);
            lld oldSuff = suff;
            suff = (suff * (1 + dp[v])) % mod;
            findAns(findAns, v, u, (pref[prefInd] * oldSuff) % mod * (val + 1) % mod);
            prefInd--;
        }
        dp[u] = (dp[u] * (val + 1)) % mod;
        Error(u, val, dp[u]);
    };
    findAns(findAns, 1, -1, 0);
    rep(i,1,n) prL(dp[i]);
    return 0;
}