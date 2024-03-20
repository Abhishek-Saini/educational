// https://www.spoj.com/problems/LPS/
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
#define errorpair(a) cout<<#a<<" = ( "<<((a).first)<<" , "<<((a).second)<<" )\n";
#else
#define Error(x...) 42
#define errorpair(a) 42
#endif
template <typename T1> void printIt(T1 t1) { cout << t1 << " )" << endl; }
template <typename T1, typename... T2>
void printIt(T1 t1, T2... t2) { cout << t1 << " , "; printIt(t2...); }
#define mset(a, v) memset(a, v, sizeof(a))
#define popcount __builtin_popcountll

#define lim 300010
#define lim2 200010
// unordered_map<lld,lld>::iterator it; // Ab :)
// std::ios::sync_with_stdio(false);

lld A[lim];

// Manacher Algorithm All Palindrome Substrings
vector<lld> FindLPSOddLength(const string& S) {
    lld n = S.size();
    vector<lld> lps(n, -1);
    lld l = 0, r = -1;
    for(lld i = 0; i < n; ++i) {
        lld k = (i > r) ? 1 : min(lps[l + r - i], r - i + 1);
        while(0 <= i - k && i + k < n && S[i - k] == S[i + k]) {
            ++k;
        }
        lps[i] = k--;
        if(i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    return lps;
}


int main(){
    string S;
    cin >> S;
    lld n = S.size();
    vector<lld> lps = FindLPSOddLength(S);
    for(int i = 0; i < n; ++i) {
        Error(i, lps[i]);
    }
    string Even;
    for(int i = 0; i < n; ++i) {
        Even += '#';
        Even += S[i];
    }
    Even += '#';
    vector<lld> lps2 = FindLPSOddLength(Even);
    lld mx = 0, mxInd = -1;
    for(int i = 0; i < n; i++) {
        if(lps[i] > mx) {
            mx = lps[i];
            mxInd = i;
        }
    }
    string mxLenEvenString, mxLenOddString;
    assert(mxInd != -1);
    mxLenEvenString = S.substr(mxInd - mx + 1, 2 * mx - 1);
    mx = -1, mxInd = -1;
    for(int i = 1; i < n; i++) {
        Error(i, lps2[2 * i], mx);
        if(lps2[2 * i] > mx) {
            mx = lps2[2 * i];
            mxInd = i  - 1;
        }
    }
    // assert(mxInd != -1);
    Error(mxInd, mx);
    int len = mx / 2 * 2;
    mxLenOddString = S.substr(mxInd - mx / 2 + 1, len);
    Error(mxLenEvenString, mxLenOddString);
    if(sz(mxLenEvenString) > sz(mxLenOddString)) {
        cout << mxLenEvenString << "\n";
    } else {
        cout << mxLenOddString << "\n";
    }
    return 0;
}