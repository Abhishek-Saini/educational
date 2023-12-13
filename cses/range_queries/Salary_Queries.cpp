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

#define lim 600010
#define lim2 200010
// std::ios::sync_with_stdio(false); // Ab :)


lld A[lim];
struct que{
    int type;
    int a, b;
};
que Q[lim];

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
    int n = scd(), q = scd();
    vector<int> P;
    repI(i, 1, n) A[i] = scd(), P.push_back(A[i]);
    repI(i, 1, q) {
        char type;
        cin >> type;
        Q[i].type = (type == '!');
        Q[i].a = scd();
        Q[i].b = scd();
        if(Q[i].type == 1) P.push_back(Q[i].b);
    }
    sort(all(P));
    P.resize(unique(all(P)) - P.begin());
    // repI(i, 0, sz(P) - 1) Error(i, P[i]);
    auto findPos = [&](int x) {
        return lower_bound(all(P), x) - P.begin() + 1;
    };
    repI(i, 1, n) ChangeFen(findPos(A[i]), sz(P), 1);
    repI(i, 1, q) {
        if(Q[i].type == 1) {
            ChangeFen(findPos(A[Q[i].a]), sz(P), -1);
            A[Q[i].a] = Q[i].b;
            ChangeFen(findPos(A[Q[i].a]), sz(P), 1);
        } else {
            int l = findPos(Q[i].a), r = findPos(Q[i].b);
            if(r - 1 < sz(P) && P[r - 1] > Q[i].b) r--;
            // Error(l, r);
            lld val = ReadFen(r) - ReadFen(l - 1);
            if(val < 0) val = 0;
            prL(val);
        }
    }
    return 0;
}