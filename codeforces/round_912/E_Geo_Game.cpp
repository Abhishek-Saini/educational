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


lld A[lim], B[lim];

int main(){
    int tt = scd();
    while(tt--) {
        int n = scd();
        if(n == -1) {
            break;
        }
        lld xS = sc(), yS = sc();
        repI(i, 1, n) {
            A[i] = sc();
            B[i] = sc();
        }
        set<int> good, bad;
        rep(i, 1, n) {
            lld diff = abs(A[i] - xS) + abs(B[i] - yS);
            if(diff & 1) {
                bad.insert(i);
            }
            else {
                good.insert(i);
            }
        }
        int turn = 0;
        if(sz(bad) > n / 2) {
            turn = 1;
            swap(good, bad);
        }
        if(turn == 0) {
            printf("First\n");
        }
        else {
            printf("Second\n");
        }
        fflush(stdout);
        int times = n;
        int x;
        auto printChoice = [&](int x) {
            printf("%d\n", x);
            fflush(stdout);
        };
        turn ^= 1;
        while(times--) {
            turn ^= 1;
            if(turn == 0) {
                if(sz(bad) == 0) {
                    x = *good.begin();
                    good.erase(good.begin());
                    printChoice(x);
                }
                else {
                    x = *bad.begin();
                    bad.erase(bad.begin());
                    printChoice(x);
                }
                continue;
            }
            x = scd();
            if(x == -1) {
                break;
            }
            if(good.find(x) != good.end()) {
                good.erase(x);
            }
            else {
                bad.erase(x);
            }
        }
        if(x == -1) {
            break;
        }
    }
    return 0;
}