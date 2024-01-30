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
        repI(i, 1, n) {
            A[i] = sc();
        }
        repI(i, 1, n) {
            B[i] = sc();
        }
        vector<int> posInSortedA(n + 1), posInSortedB(n + 1);
        vector<array<lld, 2>> P;
        repI(i, 1, n) {
            P.push_back({A[i], i});
        }
        sort(all(P));
        repI(i, 0, n - 1) {
            posInSortedA[P[i][1]] = i;
        }
        repI(i, 1, n) {
            P[i - 1][0] = B[i];
            P[i - 1][1] = i;
        }
        sort(all(P));
        repI(i, 0, n - 1) {
            posInSortedB[P[i][1]] = i;
        }
        vector<int> combinedSorted(n);
        iota(all(combinedSorted), 1);
        sort(all(combinedSorted), [&](int i, int j) {
            return posInSortedA[i] + posInSortedB[i] < posInSortedA[j] + posInSortedB[j];
        });
        repI(i, 0, n - 1) {
            prdS(A[combinedSorted[i]]);
        }
        printf("\n");
        repI(i, 0, n - 1) {
            prdS(B[combinedSorted[i]]);
        }
        printf("\n");
    }
    return 0;
}