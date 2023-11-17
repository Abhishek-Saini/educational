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

#define lim 3010
#define lim2 200010
// std::ios::sync_with_stdio(false); // Ab :)

lld dp[lim][lim], CostStore[lim][lim];
lld Prefix[lim], A[lim], Count[lim];

lld Cost(lld a, lld b) {
    return CostStore[a][b];
}

void compute(lld prev[],lld curr[], lld L, lld R, lld optL, lld optR){
    lld a, b, M, currOpt;
    if(L > R) return ;
    M = (L+R)/2;
    lld val = LLONG_MAX;
    // Error4(d,M,optL,optR);
    a = max(optL, 1LL);
    b = min(optR, M);
    // Error2(a,b);
    rep(rVariab,a,b){
        // Error4(rVariab,dp[d-1][rVariab-1],Cost(rVariab,M),dp[d-1][rVariab-1]+Cost(rVariab,M));
        if(prev[rVariab - 1] + Cost(rVariab, M) < val){
            // Error(dp[d-1][rVariab-1]+Cost(rVariab,M));
            val = prev[rVariab - 1] + Cost(rVariab, M);
            currOpt = rVariab;
        }
    }
    curr[M] = val;
    if(L == R) return ;
    compute(prev, curr, L, M-1, optL, currOpt);
    compute(prev, curr, M+1, R, currOpt, optR);
}

void bruteForceCompute(lld prev[], lld curr[], lld n) {
    repI(i, 1, n) {
        curr[i] = LLONG_MAX;
        repI(j, 1, i) {
            curr[i] = min(curr[i], prev[j - 1] + Cost(j, i));
        }
    }
}


int main(){
    lld n = sc(), k = sc();
    repI(i, 1, n) {
        A[i] = sc();
        Prefix[i] = A[i] * i + Prefix[i - 1];
        Count[i] = A[i] + Count[i - 1];
    }
    repI(i, 1, n) {
        int mid = i;
        repI(j, i, n) {
            while(Count[mid] - Count[i - 1] < Count[j] - Count[mid]) mid++;
            CostStore[i][j] = (Count[mid] - Count[i - 1]) * mid - (Prefix[mid] - Prefix[i - 1]);
            CostStore[i][j] += (Prefix[j] - Prefix[mid]) - (Count[j] - Count[mid]) * mid;
        }
    }
    repI(i, 1, n) dp[1][i] = Cost(1, i);
    rep(split, 2, k) {
        auto &prev = dp[split - 1];
        auto &curr = dp[split];
        compute(prev, curr, 1, n, 1, n);
        // bruteForceCompute(prev, curr, n);
    }
    prL(dp[k][n]);
    return 0;
}