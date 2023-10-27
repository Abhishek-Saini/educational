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


int main(){
    int n = scd();
    vector<vector<int>> G(n + 1);
    repI(i, 1, n - 1) {
        int u = scd();
        int v = scd();
        G[u].push_back(v);
        G[v].push_back(u);
    }
    auto findDistVector = [&](int st) {
        vector<int> dist(n + 1, -1);
        queue<int> Q;
        Q.push(st);
        dist[st] = 0;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for(auto v : G[u]) {
                if(dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    Q.push(v);
                }
            }
        }
        return dist;
    };
    auto Dis = findDistVector(1);
    int diaOne = max_element(Dis.begin() + 1, Dis.end()) - (Dis.begin());
    Dis = findDistVector(diaOne);
    int diaTwo = max_element(Dis.begin() + 1, Dis.end()) - (Dis.begin());
    auto Dis2 = findDistVector(diaTwo);
    repI(i, 1, n) prdS(max(Dis[i], Dis2[i]));
    return 0;
}