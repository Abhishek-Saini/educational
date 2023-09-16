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

#define lim 2000010
#define lim2 200010
// std::ios::sync_with_stdio(false); // Ab :)

struct value{
    lld moves;
    lld weight;
    bool operator<(const value& o) const{
        return make_pair(moves, weight) < make_pair(o.moves, o.weight);
    }
};

value dp[lim];
lld A[25];

int main(){
    lld n = sc();
    lld tot = (1 << n) - 1;
    lld allowed = sc();
    rep(i, 0, n - 1) A[i] = sc();
    dp[0] = {.moves = 0, .weight = allowed};
    rep(mask, 1, tot) {
        dp[mask] = {n, allowed};
        rep(bit, 0, n - 1) {
            if((mask >> bit) & 1) {
                lld rem = mask ^ (1 << bit);
                if(allowed - dp[rem].weight >= A[bit]) {
                    dp[mask] = min(dp[mask], {dp[rem].moves, dp[rem].weight + A[bit]});
                }
                else dp[mask] = min(dp[mask], {dp[rem].moves + 1, A[bit]});
            }
        }
        Error(mask, dp[mask].moves, dp[mask].weight);
    }
    cout << dp[tot].moves;
    return 0;
}