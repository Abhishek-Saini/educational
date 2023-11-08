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

const int SZ = 104;
struct matrix{
    lld arr[SZ][SZ];
    void reset(){
        for(int i = 0 ; i < SZ ; ++i){
            for(int j = 0 ; j < SZ ; ++j){
                arr[i][j] = LLONG_MAX / 2;
            }
        }
    }
    void makeiden(){
        reset();
        for(int i = 0 ; i < SZ ; ++i){
            arr[i][i] = 0;
        }
    }
    matrix operator * (const matrix &o) const {
        matrix res;
        for(int i = 0 ; i < SZ ; ++i){
            for(int j = 0 ; j < SZ ; ++j){
                res.arr[i][j] = LLONG_MAX / 2;
                for(int k = 0 ; k < SZ ; ++k){
                    res.arr[i][j] = min(arr[i][k] + o.arr[k][j], res.arr[i][j]);
                }
            }
        }
        return res;
    }
    matrix pow(lld b) const {
        matrix res;
        res.makeiden();
        matrix cur = *this;
        while(b){
            if(b & 1){
                res = res * cur;
            }
            cur = cur * cur;
            b >>= 1;
        }
        return res;
    }
    void printMatrix() const {
        for(int i = 0;i < SZ; ++i){
            for(int j = 0;j < SZ; ++j){
                printf("%lld ",arr[i][j]);
            }
            printf("\n");
        }
    }
};

int main(){
    int n = scd(), m = scd();
    int k = scd();
    matrix pathLen;
    for(int i = 0; i < SZ; i++) for(int j = 0; j < SZ; j++) pathLen.arr[i][j] = LLONG_MAX / 2;
    while(m--) {
        int a = scd(), b = scd();
        lld w = sc();
        pathLen.arr[a][b] = min(pathLen.arr[a][b], w);
    }
    matrix res = pathLen.pow(k); 
    if(res.arr[1][n] == LLONG_MAX / 2) res.arr[1][n] = -1;
    cout << res.arr[1][n];
    return 0;
}