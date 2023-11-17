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

typedef complex<long double> complex_t;
const long double PI = acos((long double)-1.0);

void fft(vector<complex_t>& a,int s=1){
    int n=(int)a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1 ;
        for (; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;
        if (i < j)
            swap (a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        long double ang = 2 * s * PI / len;
        complex_t wlen(cos(ang), sin(ang));
        for (int i = 0 ; i < n ; i += len) {
            complex_t w(1);
            for (int j = 0 ; j < len / 2 ; ++ j) {
                complex_t u = a[i + j] ,  v = a[i + j + len / 2] * w ;
                a[i + j] = u + v ;
                a[i + j + len / 2] = u - v ;
                w *= wlen ;
            }
        }
    }
    if (s == -1)
        for (int i = 0; i < n; ++i)
            a[i] /= n;

}

typedef long long ll;
// change ll to complex_t if needed
vector <ll> multiply (const vector<ll>& a, const vector<ll>& b) {
    vector <complex_t> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < max(a.size(), b.size()))
        n <<= 1;
    n <<= 1;
    fa.resize(n), fb.resize(n);
    fft(fa), fft(fb);
    for (int i = 0; i < n; ++i)
        fa[i] *= fb[i];
    fft (fa, -1);
    vector <ll> res(n);
    // mostly take mod here
    for (size_t i = 0; i < n; ++i)
        res[i] = ((ll)(fa[i].real() + 0.5));
    return res;
}

int main(){
    int n = scd(), m = scd();
    vector<lld> a(n, 0), b(m, 0);
    rep(i, 0, n - 1) a[i] = sc();
    rep(i, 0, m - 1) b[m - i - 1] = sc();
    auto res = multiply(a, b);
    repI(i, m - 1 - (m - 1), m - 1 + (n - 1)) prS(res[i]);
    return 0;
}