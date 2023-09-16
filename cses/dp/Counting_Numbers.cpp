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


lld A[lim];
lld dp[22][11][2][2];
bool Vis[22][11][2][2];

int main(){
    lld a = sc(), b = sc();
    string S;
    lld n;
    auto calc = [&](auto calc, lld ind, lld last, bool less, bool nonZero) -> lld {
        if(ind == n) return 1;
        lld& cnt = dp[ind][last][less][nonZero];
        if(Vis[ind][last][less][nonZero]) return cnt;
        Vis[ind][last][less][nonZero] = true;
        lld hi = S[ind] - '0';
        if(less) hi = 9;
        for(lld dig = 0; dig <= hi; ++dig) {
            if(dig == last && nonZero) continue;
            cnt += calc(calc, ind + 1, dig, less | (dig < hi), nonZero | (dig > 0));
        }
        Error(ind, last, dp[ind][last][less][nonZero]);
        return cnt;
    };
    auto findAns = [&](lld num) {
        if(num < 0) return 0LL;
        S = to_string(num);
        n = S.size();
        Error(S, n);
        rep(i, 0, n - 1) rep(j, 0, 9) rep(k,0,1) rep(l,0,1)
            Vis[i][j][k][l] = false, dp[i][j][k][l] = 0;
        lld ans = calc(calc, 0, 0, false, false);
        return ans;
    };
    lld ans = findAns(b);
    ans -= findAns(a - 1);
    cout << ans;
    return 0;
}