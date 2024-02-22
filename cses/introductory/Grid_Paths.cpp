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


lld moveOrder[lim];
bool vis[10][10];

int main(){
    string S;
    cin >> S;
    const int totalMoves = 48;
    int n = 7, m = 7;
    map<char, int> mp = {{'R', 0}, {'D', 1}, {'L', 2}, {'U', 3}, {'?', -1}};
    rep(i, 0, sz(S) - 1){
        moveOrder[i] = mp[S[i]];
    }
    int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
    repI(i, 0, n + 1) repI(j, 0, m + 1) vis[i][j] = true;
    repI(i, 1, n) repI(j, 1, m) vis[i][j] = false;
    vis[1][1] = true;
    auto numComponents = [&](int x, int y) {
        auto isValid = [&](int x, int y) -> bool {
            if(vis[x][y]) return false;
            return true;
        };
        if(isValid(x, y - 1) && isValid(x, y + 1) && !isValid(x - 1, y) && !isValid(x + 1, y)) return false;
        if(isValid(x - 1, y) && isValid(x + 1, y) && !isValid(x, y - 1) && !isValid(x, y + 1)) return false;
        return true;
    };
    int totPaths = 0;
    auto tryAll = [&](auto self, int x, int y, int moveInd) -> void {
        if(!numComponents(x, y)) return;
        if(x == n && y == 1) {
            if(moveInd == totalMoves) totPaths++;
            return;
        }
        if(moveOrder[moveInd] != -1) {
            int nx = x + dx[moveOrder[moveInd]], ny = y + dy[moveOrder[moveInd]];
            if(vis[nx][ny]) return;
            vis[nx][ny] = true;
            self(self, nx, ny, moveInd + 1);
            vis[nx][ny] = false;
            return;
        }
        rep(i, 0, 3){
            int nx = x + dx[i], ny = y + dy[i];
            if(vis[nx][ny]) continue;
            vis[nx][ny] = true;
            self(self, nx, ny, moveInd + 1);
            vis[nx][ny] = false;
        }
    };
    tryAll(tryAll, 1, 1, 0);
    prdL(totPaths);
    return 0;
}