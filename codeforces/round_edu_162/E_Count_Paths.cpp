#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 
 
using namespace std;
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
map<lld, lld> M[lim];

int main(){
    int tt = scd();
    while(tt--) {
        int n = scd();
        repI(i, 1, n) A[i] = sc();
        vector<vector<int>> Graph(n + 1);
        repI(i, 1, n) {
            M[i].clear();
        }
        repI(i, 1, n - 1) {
            int u = scd(), v = scd();
            Graph[u].push_back(v);
            Graph[v].push_back(u);
        }
        lld ans = 0;
        vector<int> Sz(n + 1, 0);
        auto dfs = [&](auto self, int x, int par) -> void {
            int bc = 0;
            for(auto y : Graph[x]) {
                if(y == par) continue;
                self(self, y, x);
                if(sz(M[y]) > sz(M[bc])) {
                    bc = y;
                }
            }
            swap(M[x], M[bc]);
            lld currColorCnt = M[x][A[x]];
            for(auto y : Graph[x]) {
                if(y == par || y == bc) continue;
                for(auto [color, cnt] : M[y]) {
                    if(color == A[x]) {
                        currColorCnt += cnt;
                        continue;
                    }
                    ans += cnt * M[x][color];
                    M[x][color] += cnt;
                }
            }
            M[x][A[x]] = 1;
            ans += currColorCnt;
        };
        dfs(dfs, 1, 0);
        prL(ans);
    }
    return 0;
}