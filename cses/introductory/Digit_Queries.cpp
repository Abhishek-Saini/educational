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


int main(){
    int tt = scd();
    vector<lld> Num(19, 0), Sum(19, 0);
    Num[0] = 0;
    lld tot = 0;
    rep(i, 1, 17) {
        Num[i] = (tot + 1) * 9;
        if(i == 1) Num[i] = 9;
        tot += Num[i];
        Sum[i] = Sum[i - 1] + Num[i] * i;
        Error(i, Num[i], Sum[i], Sum[i] >= 1e18);
    }
    while(tt--) {
        lld k = sc();
        lld i = 0;
        Error(k, Sum[i]);
        while(k > Sum[i]) {
            Error(k, Sum[i], k > Sum[i]);
            i++;
        }
        lld num = k - Sum[i - 1];
        Error(i, num);
        lld temp = (num - 1) / i;
        lld t = 1, times = i - 1;
        while(times--) t = t * 10;
        num -= temp * i;
        temp += t;
        Error(temp);
        Error(num);
        cout << to_string(temp)[num - 1] << endl;
    }
    return 0;
}