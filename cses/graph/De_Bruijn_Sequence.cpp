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


vector<pair<int,int>> G[lim];

int main(){
    int n = scd();
    if(n == 1) {
        puts("01");
        return 0;
    }
    int nodes = (1 << (n - 1)) - 1;
    repI(i, 0, nodes) {
        int x = i >> 1;
        G[i].emplace_back(x, 0);
        G[i].emplace_back(x | (1 << (n - 2)), 1);
        Error(i, x, x | (1 << (n - 2)));
    }
    vector<int> Ans;
    vector<pair<int,int>> stk;
    stk.emplace_back(0, -1);
    while(!stk.empty()) {
        auto [u, ch] = stk.back();
        if(G[u].empty()) {
            Ans.push_back(ch);
            stk.pop_back();
        } else {
            auto [v, c] = G[u].back();
            G[u].pop_back();
            stk.emplace_back(v, c);
        }
    }
    cout << string(n - 1, '0');
    reverse(all(Ans));
    for(auto x : Ans) {
        if(x != -1) printf("%d", x);
    }
    return 0;
}