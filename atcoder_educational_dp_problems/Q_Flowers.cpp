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

lld A[lim], H[lim];

template<typename StoreType>
struct SegmentTreeTemplate {
    vector<StoreType> M;
    int n;
    StoreType* A;
    SegmentTreeTemplate(int n, StoreType TempA[]) : n(n) {
        M.resize((n << 2) + 5);
        A = TempA;
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
    int findFirstOneTree(int st, int end, int ind, int l, int r) {
        if(st == end and l == r) return l;
        int mid;
        StoreType p1;
        mid = st + (end - st) / 2;
        if(r <= mid) return findFirstOneTree(st, mid, (ind << 1) + 1, l, r);
        if(l > mid) return findFirstOneTree(mid + 1, end, (ind << 1) + 2, l, r);
        p1 = queryTree(st, mid, (ind << 1) + 1, l, mid);
        if(p1 > 0) return findFirstOneTree(st, mid, (ind << 1) + 1, l, mid);
        return findFirstOneTree(mid + 1, end, (ind << 1) + 2, mid + 1, r);
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
    int findFirstOne(int l, int r) {
        return findFirstOneTree(0, n - 1, 0, l, r);
    }
};

using SegmentTree = SegmentTreeTemplate<lld>;


int main(){
    lld n = sc();
    rep(i,0,n-1) H[i] = sc();
    SegmentTree st(n + 1, A);
    st.build();
    lld ans = 0;
    rep(i,0,n-1) {
        A[i] = sc();
        lld height = H[i];
        lld mx = st.query(0, height - 1);
        ans = max(ans, mx + A[i]);
        st.update(height, mx + A[i]);
    }
    prL(ans);
    return 0;
}