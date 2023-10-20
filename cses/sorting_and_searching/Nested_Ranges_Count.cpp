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


int main(){
    int n = scd();
    vector<array<int, 3>> A;
    repI(i, 1, n) {
        int a = scd(), b = scd();
        A.push_back({a, b, i});
    }
    sort(all(A), [](auto a, auto b) {
        if(a[0] == b[0]) return a[1] > b[1];
        return a[0] < b[0];
    });
    vector<array<int, 2>> Ans(n + 1, {0, 0});
    vector<int> V;
    repI(i, 0, n - 1) V.push_back(A[i][1]);
    sort(all(V));
    V.resize(unique(all(V)) - V.begin());
    map<int, int> Pos;
    repI(i, 0, sz(V) - 1) Pos[V[i]] = i + 1;
    repI(i, 0, n - 1) ChangeFen(Pos[A[i][1]], sz(V), 1);
    repI(i, 0, n - 1) {
        ChangeFen(Pos[A[i][1]], sz(V), -1);
        auto [st, en, id] = A[i];
        auto cnt = ReadFen(Pos[en]);
        Error(i, en);
        Ans[id][0] += cnt;
    }
    repI(i, 0, n - 1) ChangeFen(Pos[A[i][1]], sz(V), 1);
    repDI(i, n - 1, 0) {
        ChangeFen(Pos[A[i][1]], sz(V), -1);
        auto [st, en, id] = A[i];
        auto cnt = ReadFen(sz(V)) - ReadFen(Pos[en] - 1);
        Ans[id][1] += cnt;
    }
    repI(i, 1, n) prdS(Ans[i][0] > 0);
    puts("");
    repI(i, 1, n) prdS(Ans[i][1] > 0);
    return 0;
}