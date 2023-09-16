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


int dp[2][(int)1e6 + 5];
int C[103];

int main(){
    int n = scd(), x = scd();
    repI(i, 1, n) C[i] = scd();
    repI(i,1,x) dp[0][i] = x + 1;
    int ind = 1;
    repI(j,1,n) {
        auto& curr = dp[ind];
        auto& prev = dp[ind ^ 1];
        ind ^= 1;

        repI(i,0,x) {
            curr[i] = prev[i];
            if(i >= C[j]) {
                curr[i] = min(curr[i], prev[i - C[j]] + 1);
                curr[i] = min(curr[i], curr[i - C[j]] + 1);
            }
        }
    }
    ind ^= 1;
    int ans = dp[ind][x];
    if(ans == x + 1) ans = -1;
    cout << ans;
    return 0;
}