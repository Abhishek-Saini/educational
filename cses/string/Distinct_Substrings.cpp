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

const int MAXN = 100005;
const int ALPH = 256;
const int MAXLOG = 20;

int p[MAXN]; // suffix array itself
int pcur[MAXN];
int c[MAXN][MAXLOG];
int num[MAXN];
int classesNum;

void buildSuffixArray(string s) {
    int n=s.size();
    n++;
    for (int i = 0;i < ALPH;i++)
        num[i] = 0;
    for (int i = 0; i < n; i++)
        num[s[i]]++;

    for (int i = 1; i < ALPH; i++)
        num[i] += num[i - 1];

    for (int i = 0; i < n; i++) {
        p[num[s[i]] - 1] = i;
        num[s[i]]--;
    }

    c[p[0]][0] = 1;
    classesNum = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]])
            classesNum++;
        c[p[i]][0] = classesNum;
    }

    for (int i = 1; ; i++) {

        int half = (1 << (i - 1));

        for (int j = 0; j < n; j++) {
            pcur[j] = p[j] - half;
            if (pcur[j] < 0)
                pcur[j] += n;
        }

        for (int j = 1; j <= classesNum; j++)
            num[j] = 0;

        for (int j = 0; j < n; j++)
            num[c[pcur[j]][i - 1]]++;
        for (int j = 2; j <= classesNum; j++)
            num[j] += num[j - 1];

        for (int j = n - 1; j >= 0; j--) {
            p[num[c[pcur[j]][i - 1]] - 1] = pcur[j];
            num[c[pcur[j]][i - 1]]--;
        }

        c[p[0]][i] = 1;
        classesNum = 1;

        for (int j = 1; j < n; j++) {
            int p1 = (p[j] + half) % n, p2 = (p[j - 1] + half) % n;
            if (c[p[j]][i - 1] != c[p[j - 1]][i - 1] || c[p1][i - 1] != c[p2][i - 1])
                classesNum++;
            c[p[j]][i] = classesNum;
        }

        if ((1 << i) >= n)
            break;
    }

    for (int i = 0; i < n; i++)
        p[i] = p[i + 1];
    n--;
}

// length of longest common prefix in suffix at a and at b
// RMQ Can be used for any two suffix's prefixes (after preprocessing for consecutive suffixes)
int getLcp(int a, int b,int n) {
    int res = 0;
    for (int i = MAXLOG - 1; i >= 0; i--) {
        int curlen = (1 << i);
        if (curlen > n)
            continue;
        if (c[a][i] == c[b][i]) {
            res += curlen;
            a += curlen;
            b += curlen;
        }
    }
    return res;
}


int main(){
    string S;
    cin >> S;
    lld ans = 0;
    buildSuffixArray(S);
    int n = S.size();
    repI(i, 0, n - 1) {
        int ind = p[i];
        int len = n - ind;
        ans += len;
        if(i > 0) ans -= getLcp(ind, p[i - 1], n);
    }
    prL(ans);
    return 0;
}