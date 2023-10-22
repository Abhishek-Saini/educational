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

#define lim 1000010
#define lim2 200010
// std::ios::sync_with_stdio(false); // Ab :)


lld A[lim];
string S[lim];
vector<int> G[lim];
vector<char> direc[lim];
vector<char> value;
vector<int> reachedVia, reachedDirec;

int main(){
    int row = scd(), col = scd();
    rep(i, 0, row - 1) cin >> S[i];
    int n = row * col;
    value.resize(n);
    reachedDirec.resize(n);
    reachedVia.resize(n);
    int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
    vector<int> visit(n + 1, 0);
    char dir[4] = {'U', 'D', 'L', 'R'};
    rep(i, 0, row - 1) rep(j, 0, col - 1) {
        int u = i * col + j + 1;
        value[u] = S[i][j];
        if(S[i][j] == '#') {
            visit[u] = 1;
            continue;
        }
        rep(k, 0, 3) {
            int x = i + dx[k];
            int y = j + dy[k];
            if(x < 0 || x >= row || y < 0 || y >= col || S[x][y] == '#') continue;
            G[u].push_back(x * col + y + 1);
            direc[u].push_back(dir[k]);
        }
    }
    function<void(int, int, int)> dfs = [&](int u, int par, char c) {
        if(visit[u] == 1) return ;
        reachedVia[u] = par;
        reachedDirec[u] = c;
        // int word = u - 1;
        // Error(word / col ,word % col);
        visit[u] = 1;
        int sz = G[u].size();
        rep(i, 0, sz - 1) {
            int x = G[u][i];
            if(x == par) continue;
            dfs(x, u, direc[u][i]);
        }
    };
    vector<int> Nodes;
    int tar;
    rep(i, 1, n) {
        if(value[i] == 'B') {
            tar = i;
            continue;
        }
        if(value[i] != 'A') continue;
        Error(i);
        dfs(i, -1, 'X');
    }
    // assert(sz > 0);
    if(visit[tar] == 0) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    string ans = "";
    while(tar != -1) {
        int par = reachedVia[tar];
        char c = reachedDirec[tar];
        // if(c != 'X') ans += c;
        tar = par;
    }
    reverse(all(ans));
    cout << sz(ans) << "\n";
    return 0;
}