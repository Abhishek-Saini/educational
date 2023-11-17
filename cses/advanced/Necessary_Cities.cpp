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


vector<int> G[lim];

int main(){
    int n = scd(), m = scd();
    repI(i,1,m) {
        int u = scd(), v = scd();
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<int> cutNodes;
    vector<int> minReachable(n + 1, n + 1);
    vector<int> discoverdBy(n + 1, -1), discoveryTime(n + 1, -1);
    vector<bool> visited(n + 1, false);
    int turn = 1;
    function<void(int, int)> dfs = [&](int x, int par){
        Error(x, par, turn);
        discoverdBy[x] = par;
        visited[x] = true;
        discoveryTime[x] = turn++;
        minReachable[x] = discoveryTime[x];
        bool cutEdgeFound = false;
        for(auto y : G[x]) {
            if(y == par || visited[y]) continue;
            dfs(y, x);
            // Error(x, par, minReachable[x]);
            // Error(y, minReachable[y]);
            // equality comparison is different than cut edges
            // equal is not okay as coming to same node is not enough
            if(minReachable[y] >= discoveryTime[x]) {
                // cutEdges.push_back({x, y});
                cutEdgeFound = true;
            }
        }
        if(cutEdgeFound && x != 1) cutNodes.push_back(x);
        for(auto y : G[x]) {
            if(y == par) continue;
            minReachable[x] = min(minReachable[x], minReachable[y]);
        }
        Error(x, minReachable[x]);
    };
    dfs(1, -1);
    if(count(all(discoverdBy), 1) > 1) cutNodes.push_back(1);
    cout << sz(cutNodes) << endl;
    for(auto x : cutNodes) {
        cout << x << " ";
    }
    return 0;
}