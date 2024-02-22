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
int Mat[8][8];

int main(){
    repI(i, 0, 7) {
        string S; cin >> S;
        repI(j, 0, 7) {
            if(S[j] == '*') Mat[i][j] = -1;
            else Mat[i][j] = 0;
        }
    }
    int ans = 0, taken = 0;
    auto countAll = [&](auto self, int x, int y) {
        if(taken == 8) {
            ans++;
            return;
        }
        if(y == 8) {
            x++;
            y = 0;
            if(x == 8) {
                return;
            }
        }
        self(self, x, y + 1);
        if(Mat[x][y] == -1) {
            return;
        }
        repI(i, 0, x) {
            repI(j, 0, 7) {
                if(Mat[i][j] != 1) continue;
                if(x - y == i - j || x + y == i + j || x == i || y == j) {
                    return;
                }
            }
        }
        Mat[x][y] = 1;
        taken++;
        Error(taken);
        self(self, x, y + 1);
        Mat[x][y] = 0;
        taken--;
    };
    countAll(countAll, 0, 0);
    prdL(ans);
    return 0;
}