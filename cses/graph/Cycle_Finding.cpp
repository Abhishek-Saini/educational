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
struct edge{
    int u, v;
    lld weight;
};
edge E[lim];
vector<int> G[lim], R[lim];

// Bellman Ford
int main(){
    int n = scd(), m = scd();
    rep(i, 1, m) {
        E[i].u = scd();
        E[i].v = scd();
        E[i].weight = sc();
    }
    bool negCyc = false;
    int cyclePoint = -1;
    vector<lld> Dis(n + 1, 0), Par(n + 1, -1);
    rep(times, 1, n) {
        rep(i, 1, m) {
            auto [a, b, w] = E[i];
            if(Dis[a] + w < Dis[b]) {
                if(times == n) {
                    negCyc = true;
                    cyclePoint = b;
                }
                Par[b] = a;
                Dis[b] = Dis[a] + w;
            }
        }
    }
    if(!negCyc) {
        printf("NO\n");
        return 0;
    }
    repI(times, 1, n) cyclePoint = Par[cyclePoint];
    vector<int> Ans;
    int st = cyclePoint;
    while(true) {
        Ans.push_back(st);
        st = Par[st];
        if(st == cyclePoint) break;
    }
    Ans.push_back(st);
    reverse(all(Ans));
    printf("YES\n");
    for(auto x : Ans) printf("%d ", x);
    return 0;
}