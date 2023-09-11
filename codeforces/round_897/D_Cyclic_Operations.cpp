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


int A[lim];


int main(){
    int tt = scd();
    while(tt--) {
        int n = scd(), k = scd();
        bool allSelf = true;
        vector<int> indegree(n + 1, 0);
        repI(i, 1, n) {
            A[i] = scd();
            indegree[A[i]]++;
            if(A[i] != i) allSelf = false;
        }
        if(k == 1) {
            if(allSelf) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
            continue;
        }
        vector<int> visited(n + 1, 0);
        queue<int> q;
        repI(i, 1, n) {
            if(indegree[i] == 0) {
                q.push(i);
            }
        }
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            visited[u] = 1;
            indegree[A[u]]--;
            if(indegree[A[u]] == 0) {
                q.push(A[u]);
            }
        }
        bool ans = true;
        repI(i, 1, n) {
            if(visited[i] == 1) continue;
            int u = i;
            int cnt = 0;
            while(visited[u] == 0) {
                visited[u] = 1;
                u = A[u];
                cnt++;
            }
            if(cnt != k) {
                ans = false;
                break;
            }
        }
        if(ans) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}
