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

#define lim 200010
#define lim2 200010
// std::ios::sync_with_stdio(false); // Ab :)
vector<int> G[lim];
lld ans = 0;
int k1, k2;

lld prefixSum(deque<lld> &res, int ind) {
    if(ind < 0) return 0;
    if(ind + 1 >= sz(res)) return res[0];
    return res[0] - res[ind + 1];
}

void merge(deque<lld> &res, deque<lld> &tmp) {
    if(sz(res) < sz(tmp)) swap(res, tmp);
    repI(i, 0, sz(tmp) - 1) {
        ans += (prefixSum(tmp, i) - prefixSum(tmp, i - 1)) * (prefixSum(res, k2 - i) - prefixSum(res, k1 - 1 - i));
    }
    repI(i, 0, sz(tmp) - 1) {
        res[i] += tmp[i];
    }
}


deque<lld> dfs(int u, int par) {
    deque<lld> res{1};
    for(auto v : G[u]) {
        if(v == par) continue;
        deque<lld> tmp = dfs(v, u);
        tmp.push_front(tmp.front());
        merge(res, tmp);
    }
    return res;
}


int main(){
	int n = scd();
    k1 = scd();
    k2 = scd();
    repI(i, 1, n - 1) {
        int u = scd();
        int v = scd();
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, -1);
    prL(ans);
	return 0;
}