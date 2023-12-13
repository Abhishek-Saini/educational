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

struct MergeSortTree {
    vector<vector<lld> > M, Pre, Ele;
    int n;
	lld ans;
    // n = number of elements, tree is zero-indexed
    MergeSortTree(int n) : n(n) {
        M.resize((n << 2) + 5);
        Pre.resize((n << 2) + 5);
        Ele.resize((n << 2) + 5);
    }
    // change below function and initilization step in buildTree
    // it uses A[] while building the tree
    // and change updateTree for updating
    inline lld combineNodes(lld p1, lld p2){
        return max(p1, p2);
    }
    void buildTree(int st, int end, int ind){
        if(st == end){
            // change here to initialize
            M[ind].emplace_back(A[st]);
			Pre[ind].emplace_back(0);
            Ele[ind].emplace_back(A[st]);
            return ;
        }
        int mid, a, b;
        mid = st+(end-st)/2;
        a = (ind << 1) + 1;
        b = (ind << 1) + 2;
        buildTree(st, mid, a);
        buildTree(mid + 1, end, b);
        // merge(M[a].begin(), M[a].end(), 
        //     M[b].begin(), M[b].end(), back_inserter(M[ind]));

		lld val = 0, mx = INT_MIN, ele = 0;
		rep(i,st,end) {
			mx = max(mx, A[i]);
			// Error(i,mx,val);
			M[ind].emplace_back(mx);
			Pre[ind].emplace_back(val += mx - A[i]);
            Ele[ind].emplace_back(ele += A[i]);
            Error(st, end, i, mx, val);
		}
    }
    lld queryTree(int st, int end, int ind, int l, int r, lld maxOfLeftArr){
        if(st == l && end == r) {
            int firstLargerInd = lower_bound(M[ind].begin(), M[ind].end(), maxOfLeftArr) - M[ind].begin();
			// Error(l, r, maxOfLeftArr, firstLargerInd);
			// rep(i,0,end-st) Error(i + l,M[ind][i],Pre[ind][i+1]);
			// Error(Pre[ind][end - st + 1]);
			ans += Pre[ind][end - st] - (firstLargerInd > 0 ? Pre[ind][firstLargerInd - 1] : 0);
            Error(st, end, maxOfLeftArr);
            Error(ans, Pre[ind][end - st]);
			if(firstLargerInd > 0) {
				ans += firstLargerInd * maxOfLeftArr;
				// ans -= Pre[ind][firstLargerInd - 1];
                ans -= Ele[ind][firstLargerInd - 1];
			}
            Error(M[ind][end - st]);
			return M[ind][end - st];
        }
        int mid, leftInd, rightInd;
        lld p1, p2;
        mid = st+(end-st)/2;
		leftInd = (ind << 1) + 1;
        rightInd = (ind << 1) + 2;
        if(r <= mid) return queryTree(st, mid, leftInd, l, r, maxOfLeftArr);
        if(l > mid) return queryTree(mid + 1, end, rightInd, l, r, maxOfLeftArr);
        p1 = queryTree(st, mid, leftInd, l, mid, maxOfLeftArr);
        p2 = queryTree(mid + 1, end, rightInd, mid + 1, r, max(maxOfLeftArr, p1));
        return combineNodes(p1, p2);
    }
    void build() {
        buildTree(0, n - 1, 0);
    }
    lld query(int l, int r) {
		ans = 0;
        queryTree(0, n - 1, 0, l, r, INT_MIN);
		return ans;
    }
};


int main(){
    int n = scd();
    int q = scd();
    repI(i, 0, n - 1) A[i] = sc();
    MergeSortTree T(n);
    T.build();
    while(q--) {
        int a = scd(), b = scd();
        prL(T.query(a - 1, b - 1));
    }
    return 0;
}