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

typedef struct Node* PNode;
struct Node {
    lld val;
    PNode left, right;
    Node(lld val, PNode left, PNode right) :
    val(val), left(left), right(right) {}
    PNode insert(int l, int r, int idx, int val);
    lld findSum(int l, int r, int kst, int ken);
};

// Use these to send as l and r in initial Call
const int minEle = 1;
const int maxEle = 2e5;
PNode nullNode = new Node(0, nullptr, nullptr);
// initialize as nullNode->left = nullNode->right = nullNode;
PNode Root[lim];

PNode Node::insert(int l, int r, int idx, int val) {
    if(l <= idx and idx <= r) {
        if(l == r) {
            return new Node(val, nullNode, nullNode);
        }
        int mid = (l + r) >> 1;
        auto left = this->left->insert(l, mid, idx, val);
        auto right = this->right->insert(mid + 1, r, idx, val);
        return new Node(left->val + right->val, left, right);
    }
    return this;
}

lld Node::findSum(int l, int r, int kst, int ken) {
    if(kst > ken) return 0;
    if(kst <= l && r <= ken) {
        return this->val;
    }
    int mid = (l + r) >> 1;
    lld sum = 0;
    if(this->left != nullptr) sum += this->left->findSum(l, mid, kst, min(mid, ken));
    if(this->right != nullptr) sum += this->right->findSum(mid + 1, r, max(kst, mid + 1), ken);
    return sum;
}
// call this to init PNode
void initPNode() {
    nullNode->left = nullNode->right = nullNode;
    // Starting Root is nullNode
}


int main(){
    initPNode();
    Root[1] = nullNode;
    int n = scd(), q = scd();
    repI(i, 1, n) Root[1] = Root[1]->insert(minEle, maxEle, i, scd());
    // prL(Root[1]->findSum(minEle, maxEle, 1, n));
    int currArray = 1;
    while(q--) {
        int type = scd();
        int arrId = scd();
        if(type == 1) {
            int id = scd(), x = scd();
            Root[arrId] = Root[arrId]->insert(minEle, maxEle, id, x);
        }
        else if(type == 2) {
            int l = scd(), r = scd();
            lld ans = Root[arrId]->findSum(minEle, maxEle, l, r);
            prL(ans);
        }
        else {
            Root[++currArray] = Root[arrId];
        }
    }
    return 0;
}