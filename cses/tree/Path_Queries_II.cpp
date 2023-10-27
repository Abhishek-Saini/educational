// https://www.spoj.com/problems/QTREE3/
#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 
 
using namespace std;
long long mod = 1e9 + 7;
long long INF = 1e7;
double EPS = 1e-12;
typedef long long int lld;
long double tick(){static clock_t oldt; clock_t newt=clock();
    long double diff=1.0L*(newt-oldt)/CLOCKS_PER_SEC; oldt = newt; return diff; }
#define rep(i,a,n) for(long long int i = (a); i <= (n); ++i)
#define repI(i,a,n) for(int i = (a); i <= (n); ++i)
#define repD(i,a,n) for(long long int i = (a); i >= (n); --i)
#define repDI(i,a,n) for(int i = (a); i >= (n); --i)
inline lld sc() { lld a; scanf("%lld", &a); return a; }
inline int scd() { int a; scanf("%d", &a); return a; }
inline double scf() { double a; scanf("%lf",&a); return a; }
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


#define lim 200010

vector<int> G[lim];
// string S[lim];
int A[lim], Org[lim];

// Segment Tree Class
template<typename StoreType>
struct SegmentTreeTemplate {
    vector<StoreType> M;
    int n;
    SegmentTreeTemplate(int n, StoreType TempA[]) : n(n) {
        M.resize((n << 2) + 5);
    }
    void buildTree(int st, int end, int ind){
        if(st == end){
            // change here to initialize
            M[ind] = A[st];
            return ;
        }
        int mid, a, b;
        mid = st+(end-st)/2;
        a = (ind << 1) + 1;
        b = (ind << 1) + 2;
        buildTree(st, mid, a);
        buildTree(mid + 1, end, b);
        M[ind] = max(M[a], M[b]);
    }

    void updateTree(int st, int end, int ind, int updateInd, StoreType val){
        if(st == updateInd && end == updateInd){
            // change here to update
            M[ind] = val;
            return ;
        }
        int mid, a, b;
        mid = st + (end-st)/2;
        a = (ind << 1) + 1;
        b = (ind << 1) + 2;
        if(updateInd <= mid) updateTree(st, mid, a, updateInd, val);
        else updateTree(mid + 1, end, b, updateInd, val);
        M[ind] = max(M[a], M[b]);
    }
    StoreType queryTree(int st, int end, int ind, int l, int r){
        if(st == l && end == r) return M[ind];
        int mid;
        StoreType p1, p2;
        mid = st+(end-st)/2;
        if(r <= mid) return queryTree(st, mid, (ind << 1) + 1, l, r);
        if(l > mid) return queryTree(mid + 1, end, (ind << 1) + 2, l, r);
        p1 = queryTree(st, mid, (ind << 1) + 1, l, mid);
        p2 = queryTree(mid + 1, end, (ind << 1) + 2, mid + 1, r);
        return max(p1, p2);
    }
    void build() {
        buildTree(0, n - 1, 0);
    }
    void update(int updateInd, StoreType val) {
        updateTree(0, n - 1, 0, updateInd, val);
    }
    StoreType query(int l, int r) {
        return queryTree(0, n - 1, 0, l, r);
    }
};

using SegmentTree = SegmentTreeTemplate<int>;


int Sz[lim], BigChild[lim], LowerEndVertex[lim];
int Par[lim][18],L[lim];

void initDfs(int x, int par, int depth) {
    Par[x][0] = par;
    L[x] = depth;
    int bc = -1, mx = -1;
    Sz[x] = 1;
    for(auto c : G[x]) {
        if(c != par) {
            // can be used if changes in vertex
            // LowerEndVertex[ind] = c;
            initDfs(c, x, depth + 1);
            Sz[x] += Sz[c];
            if(Sz[c] > mx) mx = Sz[c], bc = c;
        }
    }
    BigChild[x] = bc;
}

void buildSparse(int mask,int n){
    rep(j,1,mask){
        rep(i,1,n){
            Par[i][j]=Par[Par[i][j-1]][j-1];
        }
    }
}
// Lowest common ancestor
int lca(int p,int q){
    int t;
    if(L[p]<L[q]){
        t=q;
        q=p;
        p=t;
    }
    int logy;
    for (logy = 1; 1 << logy <= L[p]; logy++);
    logy--;
    repD(i,logy,0){
        if((L[p]-(1<<i))>=L[q]) p=Par[p][i];
    }
    if(p==q) return p;
    repD(i,logy,0){
        if(Par[p][i]!=Par[q][i]){
            p=Par[p][i];
            q=Par[q][i];
        }
    }
    return Par[p][0];
}

int totalChains, totalVerticesDone;
int ChainHead[lim], ChainNum[lim], PosInChain[lim], PosInFlatArray[lim], ReversePosInFlatArray[lim];
// A[] is flat array which is used by seg tree while building
// Heavy Light Decomposition
// Cost can be some value associated with the node/path till now, not used in template example
// TODO(Abhishek) Someday speed it up if needed by pre-calculating values for prefix of heavy paths.
// So that extra log(n) factor of segment tree can be removed while querying.
void HLD(int x, int par, int cost) {
    if(ChainHead[totalChains] == -1) ChainHead[totalChains] = x;
    ChainNum[x] = totalChains;
    PosInFlatArray[x] = totalVerticesDone;
    ReversePosInFlatArray[totalVerticesDone] = x;
    A[totalVerticesDone] = Org[x];
    totalVerticesDone++;
    int bc = BigChild[x], bcEdge;
    // find something about bc(bigChild) here if needed
    if(bc != -1) {
        HLD(bc, x, 0);
    }
    for(auto c : G[x]) {
        if(c != par and c != bc) {
            totalChains++;
            HLD(c, x, 0);
        }
    }
}

int query(int x, int topNode, SegmentTree& SegTree) {
    int tval, vChain = ChainNum[topNode], xChain, ans = 0;
    int res = 0;
    while(true) {
        xChain = ChainNum[x];
        if(xChain == vChain) {
            tval =  SegTree.query(PosInFlatArray[topNode], PosInFlatArray[x]);
            res = max(res, tval);
            break;
        }
        tval = SegTree.query(PosInFlatArray[ChainHead[xChain]], PosInFlatArray[x]);
        res = max(res, tval);
        x = Par[ChainHead[xChain]][0];
    }
    return res;
}

int main(){
    int n = scd();
    int q = scd();
    // clear
    repI(i,1,n) {
        Org[i] = scd();
    }
    repI(i,0,n) {
        ChainHead[i] = -1;
    }
    SegmentTree SegTree(n, A);

    repI(i,1,n-1) {
        int a = scd();
        int b = scd();
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }
    totalChains = 0;
    totalVerticesDone = 0;
    // init for lca
    // repI(i,1,n) repI(j,0,17) Par[i][j]=0;
    initDfs(1, -1, 0);
    buildSparse(17, n);
    HLD(1, -1, 0);
    SegTree.build();

    while(q--) {
        int type = scd();
        if(type == 1) {
            int s = scd(), x = scd();
            SegTree.update(PosInFlatArray[s], x);
        }
        else {
            // Here LCA calculation can also be done often
            int a = scd(), b = scd();
            int l = lca(a, b);
            auto res = query(a, l, SegTree);
            res = max(res, query(b, l, SegTree));
            printf("%d ", res);
        }
    }
    return 0;
}