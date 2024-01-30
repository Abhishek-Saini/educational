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


lld A[lim], Prefix[lim];

// Segment Tree Class
// call buildTree() please, intentionally not inside the constructor
// change
// - treeNode default function for initialization without doing anything
// - buildNode for initialization, building stage
// - operator+ for merging
// - applyToNode for updating value, on modify queries
const lld HIGH = 1e15;
template<typename StoreType>
struct SegmentTreeTemplate {
    using updateType = StoreType;
    struct treeNode{
        StoreType mn;
        treeNode() {
            mn = HIGH;
        }
        treeNode operator+(const treeNode& rhs) const {
            treeNode res;
            res.mn = min(mn, rhs.mn);
            return res;
        }
        void buildNode(StoreType val) {
            mn = val;
        }
        void applyToNode(updateType val) {
            mn = val;
        }
    };

    vector<treeNode> M;
    int n;
    StoreType* A;
    SegmentTreeTemplate(int n, StoreType TempA[]) : n(n) {
        M.resize((n << 2) + 5);
        A = TempA;
    }
    void buildTree(int st, int end, int ind){
        if(st == end){
            M[ind].buildNode(A[st]);
            return ;
        }
        int mid, a, b;
        mid = st+(end-st)/2;
        a = (ind << 1) + 1;
        b = (ind << 1) + 2;
        buildTree(st, mid, a);
        buildTree(mid + 1, end, b);
        M[ind] = M[a] + M[b];
    }

    void updateTree(int st, int end, int ind, int updateInd, updateType val){
        if(st == updateInd && end == updateInd){
            M[ind].applyToNode(val);
            return ;
        }
        int mid, a, b;
        mid = st + (end-st)/2;
        a = (ind << 1) + 1;
        b = (ind << 1) + 2;
        if(updateInd <= mid) updateTree(st, mid, a, updateInd, val);
        else updateTree(mid + 1, end, b, updateInd, val);
        M[ind] = M[a] + M[b];
    }
    treeNode queryTree(int st, int end, int ind, int l, int r){
        if(st == l && end == r) return M[ind];
        int mid;
        mid = st+(end-st)/2;
        if(r <= mid) return queryTree(st, mid, (ind << 1) + 1, l, r);
        if(l > mid) return queryTree(mid + 1, end, (ind << 1) + 2, l, r);
        treeNode p1 = queryTree(st, mid, (ind << 1) + 1, l, mid);
        treeNode p2 = queryTree(mid + 1, end, (ind << 1) + 2, mid + 1, r);
        return p1 + p2;
    }
    // int findFirstOneTree(int st, int end, int ind, int l, int r) {
    //     if(st == end and l == r) return l;
    //     int mid;
    //     mid = st + (end - st) / 2;
    //     if(r <= mid) return findFirstOneTree(st, mid, (ind << 1) + 1, l, r);
    //     if(l > mid) return findFirstOneTree(mid + 1, end, (ind << 1) + 2, l, r);
    //     treeNode p1 = queryTree(st, mid, (ind << 1) + 1, l, mid);
    //     if(p1.sum > 0) return findFirstOneTree(st, mid, (ind << 1) + 1, l, mid);
    //     return findFirstOneTree(mid + 1, end, (ind << 1) + 2, mid + 1, r);
    // }
    void build() {
        buildTree(0, n - 1, 0);
    }
    void update(int updateInd, updateType val) {
        updateTree(0, n - 1, 0, updateInd, val);
    }
    treeNode query(int l, int r) {
        return queryTree(0, n - 1, 0, l, r);
    }
    // int findFirstOne(int l, int r) {
    //     return findFirstOneTree(0, n - 1, 0, l, r);
    // }
};

int main(){
    int tt = scd();
    while(tt--) {
        int n = scd();
        repI(i, 1, n) A[i] = sc(), Prefix[i] = Prefix[i - 1] + A[i];
        lld low = 0, high = 1e15;
        Prefix[n + 1] = high;
        lld ans = high;
        while(low <= high) {
            lld mid = (low + high) / 2;
            SegmentTreeTemplate<lld> dp(n + 2, A);
            dp.update(n + 1, 0);
            lld lastDp = 0;
            bool ok = true;
            Error("MIDDDDDDDDDDDD", mid);
            repDI(i, n, 1) {
                int limitInd = upper_bound(Prefix + i, Prefix + n + 1, Prefix[i - 1] + mid) - Prefix;
                if(limitInd == i) {
                    ok = false;
                    break;
                }
                dp.update(i, A[i] + lastDp);
                Error(i, limitInd, A[i] + lastDp);
                lastDp = dp.query(i, limitInd).mn;
                Error(lastDp);
            }
            if(lastDp > mid) {
                ok = false;
            }
            if(ok) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        prL(ans);
    }
    return 0;
}