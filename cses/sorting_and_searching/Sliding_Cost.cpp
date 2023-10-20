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

struct MiddleElement {
    MiddleElement() {}
    void balance() {
        while(sz(left) < sz(right)) {
            leftSum += *right.begin();
            rightSum -= *right.begin();
            left.insert(*right.begin());
            right.erase(right.begin());
        }
        while(sz(left) > sz(right) + 1) {
            rightSum += *left.rbegin();
            leftSum -= *left.rbegin();
            right.insert(*left.rbegin());
            left.erase(left.find(*left.rbegin()));
        }
    }
    void insert(lld x) {
        if(left.empty() || x <= *left.rbegin()) left.insert(x), leftSum += x;
        else right.insert(x), rightSum += x;
        balance();
    }
    void erase(lld x) {
        if(left.count(x)) left.erase(left.find(x)), leftSum -= x;
        else right.erase(right.find(x)), rightSum -= x;
        balance();
    }
    lld get() {
        assert(!left.empty());
        // returning smaller if two middle elements
        lld median = *left.rbegin();
        lld leftSz = sz(left) - 1, rightSz = sz(right);
        lld pre = leftSum - median, suff = rightSum;
        lld ans = leftSz * median - pre + suff - rightSz * median;
        return ans;
    }
    multiset<lld> left, right;
    lld leftSum = 0, rightSum = 0;
};

int main(){
    int n = scd(), k = scd();
    MiddleElement mde;
    repI(i, 1, n) {
        A[i] = scd();
        mde.insert(A[i]);
        if(i >= k) {
            prS(mde.get());
            mde.erase(A[i - k + 1]);
        }
    }
    return 0;
}