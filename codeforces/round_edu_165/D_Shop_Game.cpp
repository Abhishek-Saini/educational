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


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while(tt--) {
        int n, k;
        cin >> n >> k;
        vector<array<lld, 2>> A(n);
        for(int i = 0; i < n; i++) {
            cin >> A[i][0];
        }
        for(int i = 0; i < n; i++) {
            cin >> A[i][1];
        }
        sort(all(A), [&](array<lld, 2> a, array<lld, 2> b) {
            return a[1] > b[1];
        });
        lld ans = 0;
        priority_queue<lld> pq;
        lld profit = 0, paid = 0;
        rep(i, 0, n - 1) profit += max(0LL, A[i][1] - A[i][0]);
        if(k == 0) {
            cout << profit << "\n";
            continue;
        }
        repI(i, 0, k - 1) {
            pq.push(A[i][0]);
            paid += A[i][0];
            profit -= max(0LL, A[i][1] - A[i][0]);
        }
        ans = max(ans, profit - paid);
        repI(i, k, n - 1) {
            if(A[i][0] < pq.top()) {
                paid -= pq.top();
                pq.pop();
                pq.push(A[i][0]);
                paid += A[i][0];
            }
            profit -= max(0LL, A[i][1] - A[i][0]);
            ans = max(ans, profit - paid);
        }
        cout << ans << "\n";
    }
    return 0;
}