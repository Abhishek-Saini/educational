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
    value.resize(n + 1);
    reachedDirec.resize(n + 1);
    reachedVia.resize(n + 1);
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
    function<vector<int>(int, int, int)> bfs = [&](int u, int par, char c) {
        queue<int> Q;
        Q.push(u);
        visit[u] = 1;
        reachedVia[u] = par;
        reachedDirec[u] = c;
        vector<int> dis(n + 1, 1e9);
        dis[u] = 0;
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for(int i = 0; i < sz(G[u]); ++i) {
                int v = G[u][i];
                char d = direc[u][i];
                if(visit[v] == 0) {
                    visit[v] = 1;
                    Q.push(v);
                    reachedVia[v] = u;
                    reachedDirec[v] = d;
                    dis[v] = dis[u] + 1;
                }
            }
        }
        return dis;
    };
    int tar = -1;
    const int INF = 1e9;
    vector<int> monsterDis(n + 1, INF);
    queue<int> Q;
    rep(i, 1, n) {
        if(value[i] == 'M') Q.push(i), monsterDis[i] = 0;
    }
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for(auto x : G[u]) {
            if(monsterDis[u] + 1 < monsterDis[x]) {
                Q.push(x);
                monsterDis[x] = monsterDis[u] + 1;
            }
        }
    }
    rep(i, 1, n) {
        if(value[i] != 'A') continue;
        Error(i);
        auto dis = bfs(i, -1, 'X');
        rep(i, 1, n) {
            if(dis[i] < monsterDis[i]) {
                int r = (i - 1) / col;
                int c = (i - 1) % col;
                if(r == 0 || r == row - 1 || c == 0 || c == col - 1) {
                    tar = i;
                    break;
                }
            }
        }
        break;
    }
    // assert(sz > 0);
    if(tar == -1) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    string ans = "";
    while(tar != -1) {
        int par = reachedVia[tar];
        char c = reachedDirec[tar];
        Error(par, c, tar);
        if(c != 'X') ans += c;
        tar = par;
    }
    reverse(all(ans));
    cout << sz(ans) << "\n";
    cout << ans << "\n";
    return 0;
}