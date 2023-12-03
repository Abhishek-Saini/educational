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

typedef pair<lld,lld> PA;

lld powP(lld x, lld y) {
    lld ans = 1, po = x % mod;
    while(y > 0) {
        if(y & 1) ans = ans * po % mod;
        y >>= 1; po = po * po % mod;
    }
    return ans;
}
 
bool bitSet(lld n, lld bit){
    if((n & (1LL << bit)) != 0) return true;
    else return false;
}
 
lld findGcd(lld a, lld b){
    while(a != 0) { lld temp = b % a; b = a; a = temp; }
    return b;
}

#define lim 300010
#define lim2 200010
#define qqqqqq 210
// Ab :)
// inline lld sqr(lld x) { return x * x; }
// unordered_map<lld,lld>::iterator it;
// std::ios::sync_with_stdio(false);
// priority_queue<PA> Q;
// lld dp[1<<18];

vector<int> G[lim];
// string S[lim];
int A[lim];

struct TreeNode {
    vector<int> basis;
    TreeNode operator+(const TreeNode& rhs) {
        TreeNode res;
        res.basis = basis;
        for(auto x : rhs.basis) {
            res.add(x);
        }
        return res;
    }
    void add(int x) {
        for(auto y : basis) {
            x = min(x, x ^ y);
        }
        if(x) {
            basis.push_back(x);
            for(int i = basis.size() - 1; i > 0; --i) {
                if(basis[i] > basis[i - 1]) swap(basis[i], basis[i - 1]);
            }
        }
    }
    bool canMade(int x) {
        for(auto y : basis) {
            x = min(x, x ^ y);
        }
        return x == 0;
    }
};

// Segment Tree Class
template<typename StoreType>
struct SegmentTreeTemplate {
    vector<TreeNode> M;
    int n;
    StoreType* A;
    SegmentTreeTemplate(int n, StoreType TempA[]) : n(n) {
        M.resize((n << 2) + 5);
        A = TempA;
    }
    void buildTree(int st, int end, int ind){
        if(st == end){
            // change here to initialize
            // M[ind] = A[st];
            M[ind].add(A[st]);
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

    // void updateTree(int st, int end, int ind, int updateInd, StoreType val){
    //     if(st == updateInd && end == updateInd){
    //         // change here to update
    //         // M[ind] = val;
    //         M[ind].add(val);
    //         return ;
    //     }
    //     int mid, a, b;
    //     mid = st + (end-st)/2;
    //     a = (ind << 1) + 1;
    //     b = (ind << 1) + 2;
    //     if(updateInd <= mid) updateTree(st, mid, a, updateInd, val);
    //     else updateTree(mid + 1, end, b, updateInd, val);
    //     M[ind] = M[a] + M[b];
    // }
    TreeNode queryTree(int st, int end, int ind, int l, int r){
        if(st == l && end == r) return M[ind];
        int mid;
        TreeNode p1, p2;
        mid = st+(end-st)/2;
        if(r <= mid) return queryTree(st, mid, (ind << 1) + 1, l, r);
        if(l > mid) return queryTree(mid + 1, end, (ind << 1) + 2, l, r);
        p1 = queryTree(st, mid, (ind << 1) + 1, l, mid);
        p2 = queryTree(mid + 1, end, (ind << 1) + 2, mid + 1, r);
        return p1 + p2;
    }
    // int findFirstOneTree(int st, int end, int ind, int l, int r) {
    //     if(st == end and l == r) return l;
    //     int mid;
    //     StoreType p1;
    //     mid = st + (end - st) / 2;
    //     if(r <= mid) return findFirstOneTree(st, mid, (ind << 1) + 1, l, r);
    //     if(l > mid) return findFirstOneTree(mid + 1, end, (ind << 1) + 2, l, r);
    //     p1 = queryTree(st, mid, (ind << 1) + 1, l, mid);
    //     if(p1 > 0) return findFirstOneTree(st, mid, (ind << 1) + 1, l, mid);
    //     return findFirstOneTree(mid + 1, end, (ind << 1) + 2, mid + 1, r);
    // }
    void build() {
        buildTree(0, n - 1, 0);
    }
    // void update(int updateInd, StoreType val) {
    //     updateTree(0, n - 1, 0, updateInd, val);
    // }
    TreeNode query(int l, int r) {
        return queryTree(0, n - 1, 0, l, r);
    }
    // int findFirstOne(int l, int r) {
    //     return findFirstOneTree(0, n - 1, 0, l, r);
    // }
};

using SegmentTree = SegmentTreeTemplate<int>;


int Sz[lim], BigChild[lim], LowerEndVertex[lim];
int Par[lim][23],L[lim];
// Trie
struct Trio{
    int x, y;
}Edge[lim];
void initDfs(int x, int par, int depth) {
    Par[x][0] = par;
    L[x] = depth;
    int bc = -1, mx = -1;
    Sz[x] = 1;
    for(auto ind : G[x]) {
        int c = Edge[ind].x + Edge[ind].y - x;
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
            if(Par[i][j-1]!=-1) Par[i][j]=Par[Par[i][j-1]][j-1];
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
        if(Par[p][i]!=-1 && Par[p][i]!=Par[q][i]){
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
void HLD(int x, int par, int cost, vector<int>& valNode) {
    if(ChainHead[totalChains] == -1) ChainHead[totalChains] = x;
    ChainNum[x] = totalChains;
    PosInFlatArray[x] = totalVerticesDone;
    ReversePosInFlatArray[totalVerticesDone] = x;
    // A[totalVerticesDone] = cost;
    A[totalVerticesDone] = valNode[x];
    totalVerticesDone++;
    int bc = BigChild[x], bcEdge;
    // find something about bc(bigChild) here if needed
    if(bc != -1) {
        HLD(bc, x, 0, valNode);
    }
    for(auto ind : G[x]) {
        int c = Edge[ind].x + Edge[ind].y - x;
        if(c != par and c != bc) {
            totalChains++;
            HLD(c, x, 0, valNode);
        }
    }
}

// pair<int,int> query(int x, int topNode, SegmentTree& SegTree) {
//     int tval, vChain = ChainNum[topNode], xChain, ans = 0;
//     pair<int,int> res = {-1, -1};
//     while(true) {
//         xChain = ChainNum[x];
//         if(xChain == vChain) {
//             tval =  SegTree.query(PosInFlatArray[topNode], PosInFlatArray[x]);
//             if(tval > 0) res = {topNode, x};
//             break;
//         }
//         tval = SegTree.query(PosInFlatArray[ChainHead[xChain]], PosInFlatArray[x]);
//         if(tval > 0) res = {ChainHead[xChain], x};
//         x = Par[ChainHead[xChain]][0];
//     }
//     return res;
// }

TreeNode queryTree(int x, int topNode, SegmentTree& SegTree) {
    int tval, vChain = ChainNum[topNode], xChain, ans = 0;
    TreeNode res;
    while(true) {
        xChain = ChainNum[x];
        if(xChain == vChain) {
            res = res + SegTree.query(PosInFlatArray[topNode], PosInFlatArray[x]);
            break;
        }
        res = res + SegTree.query(PosInFlatArray[ChainHead[xChain]], PosInFlatArray[x]);
        x = Par[ChainHead[xChain]][0];
    }
    return res;
}

// A[] is the transformed [flatten] array which is used by seg tree while building
int main(){
    int n = scd();
    vector<int> valNode(n + 1);
    repI(i, 1, n) {
        valNode[i] = scd();
    }
    repI(i, 1, n - 1) {
        int x = scd(), y = scd();
        G[x].push_back(i);
        G[y].push_back(i);
        Edge[i] = {x, y};
    }
    rep(i,0,n) {
        ChainHead[i] = -1;
    }
    SegmentTree SegTree(n, A);
    totalChains = 0;
    totalVerticesDone = 0;
    // init for lca
    repI(i,1,n) repI(j,0,20) Par[i][j]=-1;
    initDfs(1, -1, 0);
    buildSparse(20, n);
    HLD(1, -1, 0, valNode);
    SegTree.build();
    int q = scd();
    while(q--) {
        int x = scd(), y = scd();
        int k = scd();
        int l = lca(x, y);
        auto res1 = queryTree(x, l, SegTree);
        auto res2 = queryTree(y, l, SegTree);
        // auto res3 = queryTree(l, Par[l][0], SegTree);
        auto res = res1 + res2;

        if(res.canMade(k)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}