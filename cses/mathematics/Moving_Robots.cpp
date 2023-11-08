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


long double prob[2][8][8], ans[8][8];
int cnt[8][8];

int main(){
    int n = 8, m = 8;
    int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
    int k = scd();
    rep(i,0,n-1) rep(j,0,m-1) ans[i][j] = 1;
    auto isValid = [&](int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < m;
    };
    rep(rr, 0, n - 1) rep(cc, 0, m - 1) {
        rep(dir, 0, 3) cnt[rr][cc] += isValid(rr + dx[dir], cc + dy[dir]);
    }
    rep(rr, 0, n - 1) rep(cc, 0, m - 1) {
        rep(i,0,n-1) rep(j,0,n-1) prob[0][i][j] = prob[1][i][j] = 0;
        int ind = 1;
        prob[0][rr][cc] = 1;
        rep(step,1,k) {
            auto& curr = prob[ind];
            auto& prev = prob[ind ^ 1];
            ind ^= 1;
            
            rep(r, 0, n - 1) rep(c, 0, m - 1) {
                curr[r][c] = 0;
                rep(dir, 0, 3) {
                    if(!isValid(r + dx[dir], c + dy[dir])) continue;
                    curr[r][c] += prev[r + dx[dir]][c + dy[dir]] / cnt[r + dx[dir]][c + dy[dir]];
                }
            }
        }
        rep(r, 0, n - 1) rep(c, 0, m - 1) ans[r][c] *= (1 - prob[ind ^ 1][r][c]);
    }
    long double res = 0;
    rep(r, 0, n - 1) rep(c, 0, m - 1) res += ans[r][c];
    printf("%.6Lf\n", res);
    return 0;
}