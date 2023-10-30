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


lld A[lim];

struct FenwickTree {
    vector<lld> Fen;
    lld n;
    FenwickTree(lld n) : n(n) {
        Fen.resize(n + 1, 0);
    }
    lld ReadFen(lld idx) {
        lld sum = 0;
        while (idx > 0) {
            sum += Fen[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }
 
    void ChangeFen(lld idx, lld val) {
        assert(idx >= 1 && idx <= n);
        while (idx <= n) {
            Fen[idx] += val;
            idx += (idx & -idx);
        }
    }
 
    lld findSum(lld l, lld r) {
        // assert(l <= r && l >= 1 && r <= n);
        return ReadFen(r) - ReadFen(l - 1);
    }
 
    lld findKth(lld l, lld r, lld k) {
        lld lo = l, hi = r;
        lld ans = -1;
        while (lo <= hi) {
            lld mid = (lo + hi) >> 1;
            if (findSum(l, mid) >= k) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return ans;
    }
};

int main(){
    int tt = scd();
    while(tt--) {
        vector<array<lld, 3>> query;
        int q = scd();
        int n = 1;
        while(q--) {
            lld t = sc(), x = sc();
            lld y = -1;
            if(t == 2) {
                y = sc();
            }
            else ++n;
            query.push_back({t, x, y});
        }
        vector<vector<int>> adj(n + 10);
        int nextNode = 2;
        for(auto [t, x, y] : query) {
            if(t == 2) continue;
            Error(x, n);
            assert(x <= n);
            adj[x].push_back(nextNode);
            ++nextNode;
        }
        // dfsNumbering
        vector<int> dfsNum(n + 1, -1);
        vector<int> dfsNumEnd(n + 1, -1);
        vector<int> dfsNumStart(n + 1, -1);
        int dfsCnt = 1;
        auto dfs = [&](auto self, int node) -> void {
            Error("dfs", node, dfsCnt);
            dfsNum[node] = dfsCnt++;
            dfsNumStart[node] = dfsNum[node];
            for(auto child : adj[node]) {
                self(self, child);
            }
            dfsNumEnd[node] = dfsCnt - 1;
        };
        dfs(dfs, 1);
        vector<lld> Ans(n + 1, 0);
        FenwickTree Fen(dfsCnt + 5);
        nextNode = 2;
        for(auto [t, x, y] : query) {
            if(t == 1) {
                Ans[nextNode] -= Fen.ReadFen(dfsNumStart[nextNode]);
                ++nextNode;
                continue;
            }
            Fen.ChangeFen(dfsNum[x], y);
            Fen.ChangeFen(dfsNumEnd[x] + 1, -y);
        }
        rep(i, 1, n) {
            Error(i, dfsNumStart[i]);
            Ans[i] += Fen.ReadFen(dfsNumStart[i]);
            prS(Ans[i]);
        }
        printf("\n");
    }
    return 0;
}