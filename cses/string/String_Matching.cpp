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

// KMP Algorithm
vector<int> KMP(string S, string pattern){
    int n = S.size();
    int m = pattern.size();
    vector<int> pi(m);
    for(int i = 1, j = 0; i < m; i++){
        while(j > 0 && pattern[i] != pattern[j]) j = pi[j-1];
        if(pattern[i] == pattern[j]) j++;
        pi[i] = j;
    }
    vector<int> ans;
    for(int i = 0, j = 0; i < n; i++){
        while(j > 0 && S[i] != pattern[j]) j = pi[j-1];
        if(S[i] == pattern[j]) j++;
        if(j == m){
            ans.push_back(i - m + 1);
            j = pi[j-1];
        }
    }
    return ans;
}


int main(){
    string A, pat;
    cin >> A >> pat;
    int ans = KMP(A, pat).size();
    cout << ans << endl;
    return 0;
}