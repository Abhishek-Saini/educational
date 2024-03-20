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


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string S;
    cin >> S;
    int n = S.size();
    vector<int> candidates(n);
    iota(all(candidates), 0);
    auto remove = [&](vector<int>& curr, int len) {
        vector<int> newOnes;
        repI(i, 0, sz(curr) - 1) {
            if(i == 0 || curr[i] - curr[i - 1] != len) newOnes.push_back(curr[i]);
        }
        return newOnes;
    };
    repI(len, 1, n) {
        vector<int> newCandidates;
        char mn = 'z' + 1;
        repI(i, 0, sz(candidates) - 1) {
            int idx = candidates[i];
            mn = min(mn, S[(idx + len - 1) % n]);
        }
        repI(i, 0, sz(candidates) - 1) {
            int idx = candidates[i];
            if(S[(idx + len - 1) % n] == mn) newCandidates.push_back(idx);
        }
        candidates = remove(newCandidates, len);
    }
    S += S;
    cout << S.substr(candidates[0], n) << endl;
    return 0;
}