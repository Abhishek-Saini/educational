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



int main(){
    int tt = scd();
    while(tt--) {
        lld a = sc(), b = sc();
        lld r = sc();
        vector<int> diffBits;
        auto IsBitSet = [](lld num, int bit) {
            return (num & (1LL << bit)) != 0;
        };
        auto findAns = [&](lld a, lld b, lld r) {
            lld ans = 0;
            if(a > b) swap(a, b);
            diffBits.clear();
            repI(i, 0, 62) {
                if(IsBitSet(a, i) != IsBitSet(b, i)) {
                    diffBits.push_back(i);
                    ans += (1LL << i) * (IsBitSet(a, i) ? -1 : 1);
                    Error("diff", i, 1 << i, IsBitSet(a, i));
                }
            }
            if(ans == 0) {
                return ans;
            }
            lld best = ans;
            repDI(ind, sz(diffBits) - 2, 0) {
                int bit = diffBits[ind];
                if(IsBitSet(a, bit)) {
                    continue;
                }
                if(r < (1LL << bit)) {
                    continue;
                }
                Error(bit);
                r -= (1LL << bit);
                ans -= (1LL << bit) * 2;
            }
            assert(ans <= best);
            return ans;
        };
        lld best = findAns(a, b, r);
        Error(best);
        if(diffBits.empty()) {
            prL(best);
            continue;
        }
        int highestBit = diffBits.back();
        if((r < (1LL << highestBit))) {
            prL(best);
            continue;
        }
        best = min(best, findAns(a ^ (1LL << highestBit), b ^ (1LL << highestBit), r - (1LL << highestBit)));
        prL(best);
    }
    return 0;
}