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

struct state {
    int len, link, pos, cnt;
    map<char, int> next;
};

const int MAXLEN = 100005;
state st[MAXLEN * 2];
int sz, last;

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    st[0].pos = -1;
    st[0].cnt = 0;
    sz++;
    last = 0;
}

void sa_extend(int ind, char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].pos = ind;
    st[cur].cnt = 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        // Error(cur, c, p, q);
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            st[clone].pos = st[q].pos;
            st[clone].cnt = 0;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}
int main(){
    string S;
    cin >> S;
    sa_init();
    int ind = 0;
    for(auto c : S) sa_extend(ind++, c);
    lld k = sc();
    vector<int> order(sz, 0);
    iota(all(order), 0);
    sort(all(order), [&](int a, int b) {
        return st[a].len > st[b].len;
    });
    for(auto i : order) {
        if(st[i].link != -1) {
            st[st[i].link].cnt += st[i].cnt;
        }
    }
    st[0].cnt = 0;
    vector<lld> dp(sz, -1);
    auto findAns = [&](auto findAns, int cur) -> lld {
        if(dp[cur] != -1) return dp[cur];
        lld& ans = dp[cur];
        ans = st[cur].cnt * (cur > 0);
        for(auto &it : st[cur].next) {
            ans += findAns(findAns, it.second);
        }
        return ans;
    };
    findAns(findAns, 0);
    // repI(i, 0, sz - 1) Error(i, dp[i]);
    int cur = 0;
    string ans;
    while(true) {
        if(k <= st[cur].cnt) {
            break;
        }
        k -= st[cur].cnt;
        for(auto &it : st[cur].next) {
            if(dp[it.second] >= k) {
                cur = it.second;
                ans += it.first;
                break;
            } else {
                k -= dp[it.second];
            }
        }
    }
    cout << ans << endl;
    return 0;
}