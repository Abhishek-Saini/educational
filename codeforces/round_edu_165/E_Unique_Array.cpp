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


int A[lim], nextOccurence[lim], lastReachable[lim];

// Segment Tree Class
// call buildTree() please, intentionally not inside the constructor
// change
// - treeNode default function for initialization without doing anything
// - buildNode for initialization, building stage
// - operator+ for merging
// - applyToNode for updating value, on modify queries
template<typename StoreType>
struct SegmentTreeTemplate {
    using updateType = StoreType;
    struct treeNode{
        StoreType mx;
        treeNode() {
            // mx = 0;
        }
        treeNode operator+(const treeNode& rhs) const {
            treeNode res;
            res.mx = max(mx, rhs.mx);
            return res;
        }
        void buildNode(StoreType val) {
            mx = val;
        }
        void applyToNode(updateType val) {
            mx = val;
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
            // Error(st, end, val);
            M[ind].applyToNode(val);
            // Error(ind, M[ind].mx);
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
        if(st == l && end == r) {
            // Error(st, end, ind, M[ind].mx);
            return M[ind];
        }
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
        if(updateInd >= n) return ;
        // Error(updateInd, val);
        updateTree(0, n - 1, 0, updateInd, val);
    }
    treeNode query(int l, int r) {
        // Error(l, r);
        auto ans = queryTree(0, n - 1, 0, l, r);
        // Error(ans.mx);
        return ans;
    }
    // int findFirstOne(int l, int r) {
    //     return findFirstOneTree(0, n - 1, 0, l, r);
    // }
};



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        map<int, int> lastOccurence;
        repI(i, 1, n) {
            // nextOccurence[i] = n + 1;
            cin >> A[i];
        }
        repDI(i, n, 1) {
            if(lastOccurence.find(A[i]) != lastOccurence.end())
                nextOccurence[i] = lastOccurence[A[i]];
            else nextOccurence[i] = n + 1;
            lastOccurence[A[i]] = i;
        }
        SegmentTreeTemplate<int> fen(n + 1, nextOccurence);
        fen.build();
        repDI(i, n, 1) {
            // Error(i, nextOccurence[i]);
            fen.update(i, nextOccurence[i]);
            fen.update(nextOccurence[i], 0);
            int mxInd = i;
            while(mxInd <= n) {
                // Error(i, mxInd);
                int newMx = fen.query(i, mxInd).mx;
                // Error(i, mxInd, newMx);
                if(newMx == mxInd) break;
                mxInd = newMx;
            }
            lastReachable[i] = mxInd;
            Error(i, lastReachable[i]);
        }
        int ans = 0;
        int ind = 1, curr = lastReachable[1];
        while(ind <= n) {
            curr = min(curr, lastReachable[ind]);
            if(curr == ind) {
                ans++;
                ind++;
                curr = lastReachable[ind];
            }
            else ind++;
            Error(ind, curr, ans);
        }
        cout << ans << "\n";
    }
    return 0;
}