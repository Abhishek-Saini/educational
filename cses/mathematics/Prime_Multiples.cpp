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
lld Prod[(int)2e6 + 4];

int main(){
    lld k = sc(), n = sc();
    rep(i,0,n-1) A[i] = sc();
    lld ans = 0;
    int tot = (1 << n) - 1;
    Prod[0] = 1;
    repI(mask, 1, tot) {
        int setbit = mask & (-mask);
        lld prod = Prod[mask ^ setbit];
        int bit = ffsll(setbit) - 1;
        if(prod > k / A[bit]) {
            prod = k + 1;
        }
        else prod *= A[bit];
        Error(mask, setbit, Prod[mask ^ setbit], prod);
        Prod[mask] = prod;
        if(prod > k) continue;
        int count = popcount(mask);
        lld contri = k / prod;
        if(count & 1) ans += contri;
        else ans -= contri;
    }
    prL(ans);
    return 0;
}