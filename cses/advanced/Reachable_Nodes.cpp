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

#define lim 50001
#define lim2 200010
// std::ios::sync_with_stdio(false); // Ab :)


vector<lld> G[lim];
bitset<lim> A[lim];
vector<bool> vis(lim, false);

int main(){
    int n = scd(), m = scd();
    while(m--) {
        int a = scd(), b = scd();
        G[a].push_back(b);
    }
    function<void(int)> findAns = [&](int x) {
        if(vis[x]) return;
        vis[x] = true;
        A[x][x] = 1;
        for(auto i : G[x]) {
            findAns(i);
            A[x] |= A[i];
        }
    };
    Error(sizeof(A) * 32);
    repI(i, 1, n) {
        findAns(i);
        printf("%d ", (int)A[i].count());
    }
    return 0;
}