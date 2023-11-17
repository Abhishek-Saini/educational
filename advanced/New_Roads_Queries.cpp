// Problem Link - https://atcoder.jp/contests/agc002/tasks/agc002_d
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
#define Error(x...) { cout << "(" << #x << ")" << " = ( "; printIt(x); }
template <typename T1> void printIt(T1 t1) { cout << t1 << " )" << endl; }
template <typename T1, typename... T2>
void printIt(T1 t1, T2... t2) { cout << t1 << " , "; printIt(t2...); }
#define errorpair(a) cout<<#a<<" = ( "<<((a).first)<<" , "<<((a).second)<<" )\n";
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

// string S[lim];
lld A[lim];

// Disjoint Union Find
struct UF {
    UF(int n) {
        A.resize(n + 1);
        Sz.resize(n + 1);
        for(int i = 1; i <= n; i++) A[i] = i, Sz[i] = 1;
    }

    int root(int a) {
        while(a != A[a]) {
            A[a] = A[A[a]];
            a = A[a];
        }
        return a;
    }

    void merge(int a, int b) {
        int par_a = root(a);
        int par_b = root(b);
        if(par_a != par_b) {
            A[par_b] = par_a;
            Sz[par_a] += Sz[par_b];
        }
    }
    vector<int> A, Sz;
};

int X[lim], Y[lim], Ans[lim];
int L[lim], H[lim];
vector<int> Mq[lim];

int main(){
    int N = scd();
    int M = scd();
    int queries = scd();
    vector<pair<int,int>> Edges;
    for(int i = 1; i <= M; i++) {
        int x = scd();
        int y = scd();
        Edges.emplace_back(x, y);
    }
    for(int i = 1; i <= queries; i++) {
        X[i] = scd();
        Y[i] = scd();
        Ans[i] = -1;
        L[i] = 1;
        H[i] = M;
    }

    bool rem = true;
    while(rem) {
        rem = false;
        // binary search
        for(int i = 1; i <= M; i++) Mq[i].clear();
        for(int i = 1; i <= queries; i++) {
            if(L[i] <= H[i]) {
                int mid = (L[i] + H[i]) >> 1;
                Mq[mid].push_back(i);
                rem = true;
            }
        }
        UF dsu(N);
        for(int mid = 1; mid <= M; mid++) {
            dsu.merge(Edges[mid - 1].first, Edges[mid - 1].second);
            for(auto i : Mq[mid]) {
                int root_x = dsu.root(X[i]);
                int root_y = dsu.root(Y[i]);
                if(root_x == root_y) {
                    Ans[i] = mid;
                    H[i] = mid - 1;
                }
                else L[i] = mid + 1;
            }
        }
    }
    for(int i = 1; i <= queries; i++) {
        if(X[i] == Y[i]) Ans[i] = 0;
        prdL(Ans[i]);
    }
    return 0;
}