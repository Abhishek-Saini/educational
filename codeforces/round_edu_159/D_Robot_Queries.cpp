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
map<array<int, 2>, vector<int>> mp, revMp;
array<int, 2> Pref[lim], Suff[lim];

int main(){
    int n = scd(), q = scd();
    string S;
    cin >> S;
    auto revString = S;
    reverse(all(revString));
    int currX = 0, currY = 0;
    Pref[0] = {0, 0};
    repI(i, 0, n - 1) {
        if(S[i] == 'U') currY++;
        else if(S[i] == 'D') currY--;
        else if(S[i] == 'L') currX--;
        else currX++;
        mp[{currX, currY}].push_back(i + 1);
        Pref[i + 1] = {currX, currY};
    }
    currX = 0, currY = 0;
    Suff[0] = {0, 0};
    repI(i, 0, n - 1) {
        if(revString[i] == 'U') currY++;
        else if(revString[i] == 'D') currY--;
        else if(revString[i] == 'L') currX--;
        else currX++;
        revMp[{currX, currY}].push_back(i + 1);
        Suff[i + 1] = {currX, currY};
    }
    while(q--) {
        int x = scd(), y = scd();
        int l = scd(), r = scd();
        if(x == 0 && y == 0) {
            printf("YES\n");
            continue;
        }
        auto it = mp.find({x, y});
        if(it != mp.end()) {
            auto vec = it->second;
            assert(sz(vec) > 0);
            if(vec[0] < l || vec.back() >= r) {
                printf("YES\n");
                continue;
            }
        }
        Error(x, y);
        x -= Pref[l - 1][0];
        y -= Pref[l - 1][1];
        Error(x, y);
        x += Suff[n - r][0];
        y += Suff[n - r][1];
        Error(x, y);
        auto it2 = revMp.find({x, y});
        if(it2 != revMp.end()) {
            auto vec = it2->second;
            assert(sz(vec) > 0);
            int revl = n - r + 1, revr = n - l + 1;
            auto it3 = lower_bound(all(vec), revl);
            if(it3 != vec.end() && *it3 < revr) {
                printf("YES\n");
                continue;
            }
        }
        printf("NO\n");
    }
    return 0;
}