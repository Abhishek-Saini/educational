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

#define lim 200010
#define lim2 200010
// std::ios::sync_with_stdio(false); // Ab :)


int A[lim];
int Move[lim][20];

int main(){
    int n = scd(), quer = scd();
    vector<int> In(n + 1, 0);
    repI(i, 1, n) A[i] = scd(), In[A[i]]++;
    queue<int> q;
    vector<int> Vis(n + 1, 0);
    repI(i, 1, n) {
        if(In[i] == 0) q.push(i);
    }
    vector<int> order;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        Vis[u] = 1;
        order.push_back(u);
        In[A[u]]--;
        if(In[A[u]] == 0) q.push(A[u]);
    }
    vector<int> steps(n + 1, 0), cyclePos(n + 1, 0);
    vector<int> cycleTouch(n + 1, 0);
    int cId = 1;
    vector<int> cycleId(n + 1, 0), CycleLen(n + 1, 0);
    repI(i, 1, n) {
        if(Vis[i] != 0) continue;
        vector<int> cycle;
        int u = i;
        while(Vis[u] != 2) {
            cycle.push_back(u);
            Vis[u] = 2;
            u = A[u];
        }
        int cycleSize = cycle.size();
        int ind = 0;
        for(auto u : cycle) cycleTouch[u] = u, cyclePos[u] = ind++, cycleId[u] = cId;
        CycleLen[cId] = cycleSize;
        cId++;
    }
    repDI(i, order.size() - 1, 0) {
        int u = order[i];
        steps[u] = steps[A[u]] + 1;
        cycleTouch[u] = cycleTouch[A[u]];
        cycleId[u] = cycleId[A[u]];
    }

    repI(i, 1, n) {
        Move[i][0] = A[i];
    }
    repI(bit, 1, 19) repI(i, 1, n) {
        Move[i][bit] = Move[Move[i][bit - 1]][bit - 1];
    }

    while(quer--) {
        int a = scd(), b = scd();
        Error(a, b);
        Error(cycleId[a], cycleId[b]);
        if(cycleId[a] != cycleId[b]) {
            printf("-1\n");
            continue;
        }
        auto disInCycle = [&](int a, int b) {
            Error("cycdis", a, b);
            if(cyclePos[b] >= cyclePos[a]) return cyclePos[b] - cyclePos[a];
            int cId = cycleId[a];
            return CycleLen[cId] - cyclePos[a] + cyclePos[b];
        };
        if(Vis[b] == 2) {
            int dis = steps[a];
            a = cycleTouch[a];
            dis += disInCycle(a, b);
            printf("%d\n", dis);
            continue;
        }
        if(Vis[a] == 2) {
            printf("-1\n");
            continue;
        }
        if(cycleTouch[a] == cycleTouch[b] && steps[a] >= steps[b]) {
            int val = steps[a] - steps[b];
            Error(dis);
            int dis = val;
            while(dis > 0) {
                int num = dis & (-dis);
                int bit = __builtin_ctz(num);
                dis -= num;
                a = Move[a][bit];
            }
            if(a != b) val = -1;
            printf("%d\n", val);
            continue;
        }
        printf("-1\n");
    }
    return 0;
}