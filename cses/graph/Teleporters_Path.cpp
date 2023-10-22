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
int X[lim], Y[lim];
int Used[lim];

// Find Eulerian Path in an directed graph
int main(){
    int n = scd(), m = scd();
    vector<int> degree(n + 1, 0);
    repI(i, 1, m) {
        X[i] = scd(), Y[i] = scd();
        G[X[i]].push_back(i);
        // G[Y[i]].push_back(i);
        degree[X[i]]++;
        degree[Y[i]]--;
    }
    rep(i, 1, n) {
        if(degree[i] != 0 && i != 1 && i != n) {
            printf("IMPOSSIBLE");
            return 0;
        }
    }
    if(degree[1] != 1 || degree[n] != -1) {
        printf("IMPOSSIBLE");
        return 0;
    }
    X[m + 1] = 1;
    Y[m + 1] = n;
    G[n].push_back(m + 1);
    degree[1]--;
    degree[n]++;
    vector<int> stk, Ans;
    stk.push_back(1);
    while(!stk.empty()) {
        int top = stk.back();
        Error(top, degree[top]);
        if(sz(G[top]) == 0) {
            stk.pop_back();
            Ans.push_back(top);
            continue;
        }
        int back = G[top].back();
        int v = X[back] + Y[back] - top;
        Error(top, v);
        G[top].pop_back();
        stk.push_back(v);
    }
    if(sz(Ans) != m + 2) {
        printf("IMPOSSIBLE");
        return 0;
    }
    for(auto a : Ans) {
        Error(a);
    }
    reverse(all(Ans));
    int ind = -1, lastOne = -1;
    for(int i = 0; i < sz(Ans) - 1; ++i) {
        if(Ans[i] == n && Ans[i + 1] == 1) {
            ind = i;
            break;
        }
        if(Ans[i] == 1) lastOne = i;
    }
    // assert(ind != -1);
    vector<int> Ans2;
    rep(i, lastOne, ind) {
        Ans2.push_back(Ans[i]);
    }
    Ans.erase(Ans.begin() + lastOne, Ans.begin() + ind + 1);
    rep(i, 1, sz(Ans2) - 1) {
        Ans.push_back(Ans2[i]);
    }
    for(auto a : Ans) {
        printf("%d ", a);
    }
    return 0;
}