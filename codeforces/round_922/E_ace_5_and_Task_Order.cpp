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




int main(){
    int tt = scd();
    while(tt--) {
        int n = scd();
        auto Ask = [&](int i) {
            printf("? %d\n", i);
            fflush(stdout);
            char c;
            cin >> c;
            if(c == '=') return 0;
            return (c == '<') ? -1 : 1;
        };
        vector<int> pos(n + 1, -1), arr(n);
        iota(all(arr), 1);
        auto findAns = [&](auto self, vector<int>& arr, int startPos) -> void {
            int sz = arr.size();
            int randomPivotInd = rand() % sz;
            // find value of pivot
            while(true) {
                int res = Ask(arr[randomPivotInd]);
                if(res == 0) {
                    break;
                }
            }
            // left side, right side
            vector<int> left, right;
            for(auto x : arr) {
                if(x == arr[randomPivotInd]) continue;
                int res = Ask(x);
                if(res < 0) {
                    left.push_back(x);
                    Error(x);
                } else {
                    right.push_back(x);
                    Error(x);
                }
                int thisRes = Ask(arr[randomPivotInd]);
                assert(res + thisRes == 0);
            }
            if(left.size() > 0) {
                self(self, left, startPos);
            }
            pos[arr[randomPivotInd]] = startPos + sz(left);
            if(right.size() > 0) {
                self(self, right, startPos + sz(left) + 1);
            }
        };
        findAns(findAns, arr, 1);
        printf("! ");
        for(int i = 1; i <= n; ++i) {
            printf("%d ", pos[i]);
        }
        printf("\n");
        fflush(stdout);
    }
    return 0;
}