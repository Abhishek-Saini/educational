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
lld dp[lim][12];


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while(tt--) {
        int n, k;
        cin >> n >> k;
        repI(i, 1, n) {
            cin >> A[i];
        }
        repI(i, 0, n) {
            repI(j, 0, k) {
                dp[i][j] = 0;
            }
        }
        repI(i, 1, n) {
            repI(j, 0, k) {
                lld mn = A[i], sum = A[i];
                dp[i][j] = dp[i - 1][j];
                repI(take, 1, j) {
                    if(i - take >= 1) {
                        mn = min(mn, A[i - take]);
                        sum += A[i - take];
                        dp[i][j] = max(dp[i][j], dp[i - take - 1][j - take] + (sum - mn * (take + 1)));
                    }
                }
            }
        }
        lld sum = accumulate(A + 1, A + n + 1, 0LL);
        sum -= dp[n][k];
        cout << sum << "\n";
    }
    return 0;
}