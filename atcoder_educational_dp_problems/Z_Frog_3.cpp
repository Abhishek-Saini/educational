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


int main(){
    lld n = sc(), c = sc();
    vector<lld> H(n+1);
    rep(i,1,n) H[i] = sc();
    vector<lld> dp(n+1, 0), val(n+1, 0);
    vector<array<lld,2>> arr;
    dp[1] = 0;
    val[1] = dp[1] + H[1] * H[1];
    arr.push_back({0, 1});
    Error(1, H[1], dp[1], val[1]);
    rep(i,2,n) {
        auto it = lower_bound(all(arr), array<lld,2>{H[i] + 1, 0});
        it--;
        lld ind = it->at(1);
        Error(ind);
        // dp[i] = dp[ind] + (H[i] - H[ind]) * (H[i] - H[ind]) + c;
        dp[i] = val[ind] - 2 * H[ind] * H[i] + H[i] * H[i] + c;
        val[i] = dp[i] + H[i] * H[i];
        auto find = [&](lld a, lld b) {
            lld diff = val[b] - val[a];
            lld diffHeight = H[b] - H[a];
            Error(diff, diffHeight, (diff - 1) / (2 * diffHeight) + 1);
            return (diff - 1) / (2 * diffHeight) + 1;
        };
        while(arr.size() > 0) {
            lld needed = find(arr.back()[1], i);
            if(needed <= arr.back()[0]) arr.pop_back();
            else break;
        }
        assert(arr.size() > 0);
        arr.push_back({find(arr.back()[1], i), i});
        // for(auto it : arr) {
        //     Error(it[0], it[1]);
        // }
        Error(i, H[i], dp[i], val[i]);
    }
    cout << dp[n] << endl;
    return 0;
}