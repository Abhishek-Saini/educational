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
vector<int> G[lim];

// Cycle nodes Finder in directed graph
// Find Cycle in directed graph
int main(){
    int n = scd(), m = scd();
    vector<int> visit(n + 1, 0);
    while(m--) {
        int a = scd(), b = scd();
        G[a].push_back(b);
        // G[b].push_back(a);
    }
    bool cycle = false;
    vector<int> Curr, Ans;
    vector<bool> Inside(n + 1, false);
    function<void(int,int)> dfs = [&](int x, int par) {
        if(visit[x] != 0) {
            if(cycle || !Inside[x]) return;
            cycle = true;
            int push = false;
            for(auto node : Curr) {
                if(node == x) push = true;
                if(push) Ans.push_back(node);
            }
            Ans.push_back(x);
            return;
        }
        Curr.push_back(x);
        Inside[x] = true;
        visit[x] = 1;
        for(auto c : G[x]) {
            // if(c != par)
            dfs(c, x);
        }
        Curr.pop_back();
        Inside[x] = false;
    };
    visit[0] = 2;
    rep(i, 1, n) {
        if(visit[i] != 0) continue;
        dfs(i, 0);
    }
    if(!cycle) printf("IMPOSSIBLE\n");
    else {
        cout << sz(Ans) << endl;
        for(auto x : Ans) cout << x << " ";
    }
    return 0;
}