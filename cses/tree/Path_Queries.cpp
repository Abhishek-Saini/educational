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
lld Fen[lim];

lld ReadFen(lld idx) {
  lld sum = 0;
  while (idx > 0) {
    sum += Fen[idx];
    idx -= (idx & -idx);
  }
  return sum;
}

void ChangeFen(lld idx, lld n, lld val) {
  while (idx <= n) {
    Fen[idx] += val;
    idx += (idx & -idx);
  }
}

lld Org[lim];
lld A[lim];

int main(){
    int n = scd(), q = scd();
    repI(i, 1, n) Org[i] = sc();
    vector<vector<int>> G(n + 1);
    repI(i, 1, n - 1) {
        int u = scd();
        int v = scd();
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<int> dfsNumber(n + 1, 0), endDfsNumber(n + 1, 0);
    int currNum = 1;
    auto dfsNumbering = [&](auto self, int u, int par) -> void {
        dfsNumber[u] = currNum++;
        for(auto v : G[u]) {
            if(v == par) continue;
            self(self, v, u);
        }
        endDfsNumber[u] = currNum - 1;
    };
    dfsNumbering(dfsNumbering, 1, 0);
    repI(i, 1, n) Error(i, dfsNumber[i], endDfsNumber[i]);
    // int numFen = n + 1;
    repI(i, 1, n) {
        ChangeFen(dfsNumber[i], n, Org[i]);
        ChangeFen(endDfsNumber[i] + 1, n, -Org[i]);
    }
    while(q--) {
        int type = scd();
        if(type == 1) {
            int s = scd(), x = scd();
            lld diff = x - Org[s];
            Org[s] = x;
            ChangeFen(dfsNumber[s], n, diff);
            ChangeFen(endDfsNumber[s] + 1, n, -diff);
        }
        else {
            int s = scd();
            prL(ReadFen(dfsNumber[s]));
        }
    }
    return 0;
}