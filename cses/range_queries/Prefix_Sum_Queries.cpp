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

template<typename StoreType>
struct SegmentTreeLazy {
    typedef struct node{
        StoreType leftSum,rightSum;
        StoreType maxSum,totalSum;
    }treeNode;

    treeNode combineNodes(treeNode& p1,treeNode& p2){
        treeNode pAns;
        pAns.totalSum=p1.totalSum+p2.totalSum;
        pAns.leftSum=max(p1.leftSum,p1.totalSum+p2.leftSum);
        pAns.rightSum=max(p2.rightSum,p2.totalSum+p1.rightSum);
        pAns.maxSum=max(max(p1.maxSum,p2.maxSum),p1.rightSum+p2.leftSum);
        return pAns;
    }
    vector<treeNode> M;
    vector<StoreType> Lazy;
    vector<bool> ToPush;
    int n;
    StoreType *A;
    SegmentTreeLazy(StoreType TempA[], int n) : n(n) {
        M.resize((n << 2) + 5);
        Lazy.resize((n << 2) + 5);
        ToPush.resize((n << 2) + 5);
        A = TempA;
    }

    inline void apply(int ind, int st, int end, StoreType val) {
        ToPush[ind] = true;
        Lazy[ind] = val;
        M[ind].totalSum = (end - st + 1) * val;
        if(val >= 0) {
            M[ind].leftSum = M[ind].rightSum = M[ind].maxSum = M[ind].totalSum;
        }
        else {
            M[ind].leftSum = M[ind].rightSum = M[ind].maxSum = val;
        }
    }

    inline void push(int ind, int st, int end) {
        if(!ToPush[ind]) return;
        int mid = (st + end) >> 1;
        int a = (ind << 1) + 1;
        int b = (ind << 1) + 2;

        apply(a, st, mid, Lazy[ind]);
        apply(b, mid + 1, end, Lazy[ind]);

        ToPush[ind] = false;
    }

    void buildTree(int st, int end, int ind){
        if(st == end){
            // change here to initialize
            apply(ind, st, end, A[st]);
            ToPush[ind] = false;
            return;
        }
        int mid = (st + end) >> 1;
        int a = (ind << 1) + 1;
        int b = (ind << 1) + 2;
        buildTree(st, mid, a);
        buildTree(mid + 1, end, b);
        // change here for how to merge
        M[ind] = combineNodes(M[a], M[b]);
        ToPush[ind] = false;
    }

    void updateTree(int st, int end, int ind, int updateLeftInd, int updateRightInd, StoreType val){
        if(updateLeftInd > updateRightInd) return;
        if(st == updateLeftInd && end == updateRightInd){
            // change here to update
            apply(ind, st, end, val);
            return;
        }
        int mid = (st + end) >> 1;
        int a = (ind << 1) + 1;
        int b = (ind << 1) + 2;
        // no need to worry about leaf node here, because that would always get inside the above condition
        // otherwise push function may give segfault, because of trying to access child of leaf node
        push(ind, st, end);
        updateTree(st, mid, a, updateLeftInd, min(mid, updateRightInd), val);
        updateTree(mid + 1, end, b, max(mid + 1, updateLeftInd), updateRightInd, val);
        // change here for how to merge
        M[ind] = combineNodes(M[a], M[b]);
    }

    treeNode queryTree(int st, int end, int ind, int l, int r){
        if(st == l && end == r) return M[ind];
        int mid = (st + end) >> 1;
        int a = (ind << 1) + 1;
        int b = (ind << 1) + 2;
        push(ind, st, end);
        if(r <= mid) return queryTree(st, mid, a, l, r);
        if(l > mid) return queryTree(mid + 1, end, b, l, r);
        treeNode p1 = queryTree(st, mid, a, l, mid);
        treeNode p2 = queryTree(mid + 1, end, b, mid + 1, r);
        // change here for how to merge
        return combineNodes(p1, p2);
    }

    // A[] input array should be ready before calling this
    void build() {
        buildTree(0, n - 1, 0);
    }
    void update(int updateLeftInd, int updateRightInd, StoreType val) {
        updateTree(0, n - 1, 0, updateLeftInd, updateRightInd, val);
    }
    StoreType query(int l, int r) {
        return queryTree(0, n - 1, 0, l, r).leftSum;
    }
};

lld A[lim];


int main(){
    int n = scd(), q = scd();
    repI(i, 0, n - 1) A[i] = scd();
    SegmentTreeLazy<lld> S(A, n);
    S.build();
    while(q--) {
        int type = scd();
        if(type == 1) {
            int k = scd() - 1;
            lld x = sc();
            S.update(k, k, x);
            continue;
        }
        int a = scd(), b = scd();
        lld ans = S.query(a - 1, b - 1);
        if(ans < 0) ans = 0;
        prL(ans);
    }
    return 0;
}