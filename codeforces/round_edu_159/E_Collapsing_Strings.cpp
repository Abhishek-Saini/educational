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

class Trie {
    struct Node {
        vector<int> edge;
        int count{0};
        Node() {
            edge.assign(26, -1);
        }
        bool someEndsHere{false};
    };
    int numNodes{1};
    vector<Node> Tree;
    public:
    Trie() {
        Tree.assign(1, Node());
    }
    void addString(const string& S) {
        int sz = S.size();
        int ind = 0, currNode = 0;
        Tree[currNode].count++;
        while(ind < sz) {
            int& nextNode = Tree[currNode].edge[S[ind] - 'a'];
            if(nextNode == -1) {
                Tree.emplace_back();
                nextNode = numNodes++;
            }
            currNode = nextNode;
            Tree[currNode].count++;
            ind++;
        }
        Tree[currNode].someEndsHere = true;
    }
    lld findAns(const string& S) {
        int sz = S.size();
        int ind = 0, currNode = 0;
        lld val = 0;
        while(ind < sz) {
            int& nextNode = Tree[currNode].edge[S[ind] - 'a'];
            if(nextNode == -1) return val;
            currNode = nextNode;
            val += Tree[currNode].count;
            ind++;
        }
        return val;
    }
};

string S[(int) 1e6 + 10];

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n;
    cin >> n;
    Trie T;
    lld ans = 0;
    repI(i, 1, n) {
        cin >> S[i];
        T.addString(S[i]);
        ans += 1LL * 2 * n * sz(S[i]);
    }
    repI(i, 1, n) {
        string re = S[i];
        reverse(all(re));
        ans -= 2LL * T.findAns(re);
    }
    cout << ans << endl;
    return 0;
}