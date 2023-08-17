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
#define errorpair(a) cout<<#a<<" = ( "<<((a).first)<<" , "<<((a).second)<<" )\n";
#else
#define Error(x...) 42
#define errorpair(a) 42
#endif
template <typename T1> void printIt(T1 t1) { cout << t1 << " )" << endl; }
template <typename T1, typename... T2>
void printIt(T1 t1, T2... t2) { cout << t1 << " , "; printIt(t2...); }
#define mset(a, v) memset(a, v, sizeof(a))
#define popcount __builtin_popcountll

#define lim 300010
#define lim2 200010
// unordered_map<lld,lld>::iterator it; // Ab :)
// std::ios::sync_with_stdio(false);

lld A[lim];
lld Freq[4];
long double dp[303][303][303];

int main(){
    lld n = sc();
    rep(i,1,n) Freq[sc()]++;
    dp[0][0][0] = 0;
    lld tot = accumulate(Freq+1, Freq+4, 0LL);
    rep(three,0,tot) rep(two,0,tot) rep(one,0,tot){
        if(one == 0 && two == 0 && three == 0) continue;
        long double needed = one + two + three;
        long double zeros = n / needed;
        if(one > 0) dp[one][two][three] += (dp[one-1][two][three] + zeros) * one;
        if(two > 0) dp[one][two][three] += (dp[one+1][two-1][three] + zeros) * two;
        if(three > 0) dp[one][two][three] += (dp[one][two+1][three-1] + zeros) * three;
        dp[one][two][three] /= needed;
        Error(one, two, three, needed, dp[one][two][three]);
        // dp[one][two][three] /= (1 - rem);
        Error(dp[one][two][three]);
    }
    printf("%.10Lf\n", dp[Freq[1]][Freq[2]][Freq[3]]);
    return 0;
}