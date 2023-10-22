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
int dx[] = {1,1,-1,-1,2,2,-2,-2}, dy[] = {2,-2,2,-2,1,-1,1,-1};

int main(){
    auto isValid = [&](int x, int y){
        return (x >= 0 && x < 8 && y >= 0 && y < 8);
    };
    auto findUnvisitedAdjacent = [&](int x, int y){
        int cnt = 0;
        repI(i,0,7){
            int nx = x + dx[i], ny = y + dy[i];
            if(isValid(nx,ny) && A[nx*8+ny] == -1){
                cnt++;
            }
        }
        return cnt;
    };
    auto dfs = [&](auto dfs, int x, int y, int cnt) -> void{
        if(cnt == 64){
            repI(i,0,7){
                repI(j,0,7){
                    cout << A[i*8+j] + 1 << " ";
                }
                cout << endl;
            }
            exit(0);
        }
        vector<pair<int,int>> order;
        repI(i,0,7){
            int nx = x + dx[i], ny = y + dy[i];
            if(isValid(nx,ny) && A[nx*8+ny] == -1){
                order.push_back({findUnvisitedAdjacent(nx,ny),i});
                // A[nx*8+ny] = cnt;
                // dfs(dfs,nx,ny,cnt+1);
                // A[nx*8+ny] = -1;
            }
        }
        sort(all(order));
        for(auto it : order){
            int nx = x + dx[it.second], ny = y + dy[it.second];
            A[nx*8+ny] = cnt;
            dfs(dfs,nx,ny,cnt+1);
            A[nx*8+ny] = -1;
        }
    };
    repI(i,0,7){
        repI(j,0,7){
            A[i*8+j] = -1;
        }
    }
    int x = scd() - 1, y = scd() - 1;
    swap(x,y);
    A[x*8+y] = 0;
    dfs(dfs,x,y,1);
    return 0;
}