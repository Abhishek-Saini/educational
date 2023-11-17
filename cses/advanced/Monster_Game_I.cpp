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

struct Line {
    long long m, c;

    Line(long long _m, long long _c) : m(_m), c(_c) {}

    long long eval(long long x) {
        return m * x + c;
    }
};

struct ConvexHullTrick {
    vector<Line> lines;

    // Function to check if line l3 is not needed, given l1 and l2
    bool isNotNeeded(const Line &l1, const Line &l2, const Line &l3) {
        return (l3.c - l1.c) * (l1.m - l2.m) >= (l2.c - l1.c) * (l1.m - l3.m);
    }

    // Add a new line to the structure
    void addLine(long long m, long long c) {
        Line line(m, c);
        while (lines.size() >= 2 && isNotNeeded(lines[lines.size() - 2], lines[lines.size() - 1], line)) {
            lines.pop_back();
        }
        lines.push_back(line);
    }

    // Query the minimum/maximum value at a point x
    long long query(long long x) {
        int left = 0, right = lines.size() - 1;
        while (left < right) {
            int mid = (left + right) / 2;
            // change here for maximum/minimum
            if (lines[mid].eval(x) <= lines[mid + 1].eval(x)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return lines[left].eval(x);
    }
};

lld S[lim], F[lim], dp[lim];

int main(){
    int n = scd();
    lld startSkill = sc();
    repI(i, 1, n) S[i] = sc();
    repI(i, 1, n) F[i] = sc();
    dp[n] = startSkill * S[n];
    ConvexHullTrick cht;
    cht.addLine(-S[n], dp[n]);
    lld ans = dp[n];
    repDI(i, n - 1, 1) {
        dp[i] = cht.query(startSkill - F[i]);
        dp[i] += startSkill * S[i];
        cht.addLine(-S[i], dp[i]);
        ans = min(ans, dp[i]);
    }
    prL(ans);
    return 0;
}