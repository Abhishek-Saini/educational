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


lld A[1003][1003];


int main(){
    int tt = scd();
    while(tt--) {
        int n = scd();
        repI(i, 1, n) {
            repI(j, 1, n) {
                A[i][j] = sc();
            }
        }
        vector<lld> ans(n + 1, 0);
        repI(i, 1, n) {
            lld val = -1;
            repI(j, 1, n) {
                if(i == j) continue;
                if(val == -1) {
                    val = A[i][j];
                }
                else {
                    val &= A[i][j];
                }
            }
            ans[i] = val;
        }
        bool ok = true;
        repI(i, 1, n) {
            repI(j, 1, n) {
                if(i == j) continue;
                if((ans[i] | ans[j]) != A[i][j]) {
                    ok = false;
                    break;
                }
            }
            if(!ok) break;
        }
        if(!ok) {
            printf("NO\n");
        }
        else {
            printf("YES\n");
            repI(i, 1, n) {
                if(ans[i] == -1) ans[i] = 0;
                prS(ans[i]);
            }
            printf("\n");
        }
    }
    return 0;
}