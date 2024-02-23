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


int main(){
    int tt = scd();
    while(tt--) {
        int n = scd();
        repI(i, 1, n) A[i] = sc();
        vector<int> prevNonEqual(n + 1, 0), nextNonEqual(n + 1, n + 1);
        map<lld, lld> lastOccur;
        repI(i, 1, n) {
            int last = lastOccur[A[i]];
            if(last == 0 || last < i - 1) {
                prevNonEqual[i] = i - 1;
            }
            else {
                prevNonEqual[i] = prevNonEqual[i - 1];
            }
            lastOccur[A[i]] = i;
        }
        lastOccur.clear();
        repDI(i, n, 1) {
            int last = lastOccur[A[i]];
            if(last == 0 || last > i + 1) {
                nextNonEqual[i] = i + 1;
            }
            else {
                nextNonEqual[i] = nextNonEqual[i + 1];
            }
            lastOccur[A[i]] = i;
        }
        vector<lld> prefixSum(n + 1, 0);
        repI(i, 1, n) prefixSum[i] = prefixSum[i - 1] + A[i];
        repI(i, 1, n) {
            int val = n + 10;
            // next
            int ind = upper_bound(all(prefixSum), prefixSum[i] + A[i]) - prefixSum.begin();
            Error(i);
            if(ind <= n) {
                int next = nextNonEqual[ind];
                if(prevNonEqual[ind] > i || ind == i + 1) next = ind;
                if(next <= n) {
                    Error("next", ind, next);
                    val = min(val, next - i);
                }
            }

            // prev
            if(prefixSum[i - 1] > A[i]) {
                ind = lower_bound(all(prefixSum), prefixSum[i - 1] - A[i]) - prefixSum.begin();
                int prev = prevNonEqual[ind];
                if(nextNonEqual[ind] < i || ind == i - 1) prev = ind;
                if(prev > 0) {
                    Error("prev", ind, prev);
                    val = min(val, i - prev);
                }
            }
            if(val == n + 10) {
                printf("-1 ");
            }
            else {
                printf("%d ", val);
            }
        }
        printf("\n");
    }
    return 0;
}   