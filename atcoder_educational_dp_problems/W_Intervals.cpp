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

struct SegmentTreeLazy {
    vector<lld> M;
    vector<lld> Lazy;
    vector<bool> ToPush;
    lld n;
    SegmentTreeLazy(lld n) : n(n) {
        M.resize((n << 2) + 5, 0);
        Lazy.resize((n << 2) + 5, 0);
        ToPush.resize((n << 2) + 5, false);
    }

    void push(lld ind) {
        if(!ToPush[ind]) return;
        lld a = (ind << 1) + 1;
        lld b = (ind << 1) + 2;

        if(ToPush[a]) {
            Lazy[a] += Lazy[ind];
        }
        else {
            Lazy[a] = Lazy[ind];
            ToPush[a] = true;
        }

        if(ToPush[b]) {
            Lazy[b] += Lazy[ind];
        }
        else {
            Lazy[b] = Lazy[ind];
            ToPush[b] = true;
        }

        M[a] += Lazy[ind];
        M[b] += Lazy[ind];

        ToPush[ind] = false;
    }

    void buildTree(lld st, lld end, lld ind){
        if(st == end){
            // change here to initialize
            M[ind] = A[st];
            ToPush[ind] = false;
            return;
        }
        lld mid = (st + end) >> 1;
        lld a = (ind << 1) + 1;
        lld b = (ind << 1) + 2;
        buildTree(st, mid, a);
        buildTree(mid + 1, end, b);
        // change here for how to merge
        M[ind] = min(M[a], M[b]);
        ToPush[ind] = false;
    }

    void updateTree(lld st, lld end, lld ind, lld updateLeftInd, lld updateRightInd, lld val){
        if(updateLeftInd > updateRightInd) return;
        if(st == updateLeftInd && end == updateRightInd){
            // change here to update
            if(ToPush[ind]) Lazy[ind] += val;
            else {
                Lazy[ind] = val;
                ToPush[ind] = true;
            }
            M[ind] += val;
            return;
        }
        lld mid = (st + end) >> 1;
        lld a = (ind << 1) + 1;
        lld b = (ind << 1) + 2;
        // no need to worry about leaf node here, because that would always get inside the above condition
        // otherwise push function may give segfault, because of trying to access child of leaf node
        push(ind);
        updateTree(st, mid, a, updateLeftInd, min(mid, updateRightInd), val);
        updateTree(mid + 1, end, b, max(mid + 1, updateLeftInd), updateRightInd, val);
        // change here for how to merge
        M[ind] = min(M[a], M[b]);
    }

    lld queryTree(lld st, lld end, lld ind, lld l, lld r){
        if(st == l && end == r) return M[ind];
        lld mid = (st + end) >> 1;
        lld a = (ind << 1) + 1;
        lld b = (ind << 1) + 2;
        push(ind);
        if(r <= mid) return queryTree(st, mid, a, l, r);
        if(l > mid) return queryTree(mid + 1, end, b, l, r);
        lld p1 = queryTree(st, mid, a, l, mid);
        lld p2 = queryTree(mid + 1, end, b, mid + 1, r);
        // change here for how to merge
        return min(p1, p2);
    }

    // A[] input array should be ready before calling this
    void build() {
        buildTree(0, n - 1, 0);
    }
    void update(lld updateLeftInd, lld updateRightInd, lld val) {
        updateTree(0, n - 1, 0, updateLeftInd, updateRightInd, val);
    }
    lld query(lld l, lld r) {
        return queryTree(0, n - 1, 0, l, r);
    }
};

lld L[lim], R[lim];
vector<lld> St[lim], En[lim];

int main(){
    lld n = sc(), m = sc();
    rep(i,1,m) {
        lld st = sc(), en = sc();
        A[i] = sc();
        St[st].push_back(i);
        En[en].push_back(i);
        L[i] = st;
        R[i] = en;
    }
    vector<lld> dp(n + 1, 0);
    SegmentTreeLazy seg(n + 1);
    lld mn = accumulate(A + 1, A + n + 1, 0);
    // notStarted is for intervals that start after the current index.
    lld notStarted = accumulate(A + 1, A + n + 1, 0);
    rep(i,1,n) {
        rep(var,0,i-1) {
            Error(i, var, seg.query(var, var));
        };
        dp[i] = seg.query(0, i - 1);
        for(auto ind : En[i]) {
            seg.update(0, L[ind] - 1, A[ind]);
        }
        // dp[i] = min(dp[i], seg.query(0, i - 1));
        seg.update(i, i, dp[i]);

        for(auto ind : St[i]) {
            notStarted -= A[ind];
        }
        mn = min(mn, dp[i] + notStarted);
        
        Error(i, dp[i]);
    }
    prL(accumulate(A + 1, A + n + 1, 0) - mn);
    return 0;
}
