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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef struct item* pitem;
struct item {
    int prior, value, cnt;
    lld sum;
    bool rev;
    pitem l, r;
    item(int value) : value(value), prior(rng()), cnt(1), rev(false), l(nullptr), r(nullptr) {
        sum = value;
    }
};

struct Treap{
    Treap(){
        root = nullptr;
    }
    int cnt (pitem it) {
        return it ? it->cnt : 0;
    }

    lld sum(pitem it) {
        return it ? it->sum : 0LL;
    }

    inline void upd_cnt (pitem it) {
        if (it)
            it->cnt = cnt(it->l) + cnt(it->r) + 1;
    }

    inline void upd_sum(pitem it) {
        if (it)
            it->sum = sum(it->l) + sum(it->r) + it->value;
    }

    void updateNode(pitem it) {
        upd_cnt(it);
        upd_sum(it);
    }

    void push (pitem it) {
        if (it && it->rev) {
            it->rev = false;
            swap (it->l, it->r);
            if (it->l)  it->l->rev ^= true;
            if (it->r)  it->r->rev ^= true;
        }
    }

    void merge (pitem & t, pitem l, pitem r) {
        push (l);
        push (r);
        if (!l || !r)
            t = l ? l : r;
        else if (l->prior > r->prior)
            merge (l->r, l->r, r),  t = l;
        else
            merge (r->l, l, r->l),  t = r;
        updateNode (t);
    }

    void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
        if (!t)
            return void( l = r = 0 );
        push (t);
        int cur_key = add + cnt(t->l);
        if (key <= cur_key)
            split (t->l, l, t->l, key, add),  r = t;
        else
            split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
        updateNode (t);
    }

    void reverse (pitem t, int l, int r) {
        pitem t1, t2, t3;
        split (t, t1, t2, l);
        split (t2, t2, t3, r-l+1);
        t2->rev ^= true;
        merge (t, t1, t2);
        merge (t, t, t3);
    }

    void output (pitem t) {
        if (!t)  return;
        push (t);
        output (t->l);
        // print tree preorder
        printf ("%c", t->value);
        output (t->r);
    }

    void insert (pitem & t, int key, int value) {
        pitem toInsert = new item(value);
        pitem L, R;
        split(t, L, R, key);
        merge(L, L, toInsert);
        merge(t, L, R);
        // updateNode(t);
    }

    int erase(pitem & t, int key) {
        pitem L, toErase, R;
        split(t, L, toErase, key);
        split(toErase, toErase, R, 1);
        merge(t, L, R);
        // updateNode(t);
        int erasedValue = toErase->value;
        delete toErase;
        return erasedValue; 
    }

    lld query(pitem & t, int l, int r) {
        pitem L, needed, R;
        split(t, L, needed, l);
        split(needed, needed, R, r - l + 1);
        lld ans = sum(needed);
        merge(t, L, needed);
        merge(t, t, R);
        return ans;
    }
    
    pitem root;
};

int main(){
    Treap tr;
    int n = scd(), m = scd();
    repI(i, 0, n - 1) {
        int c = scd();
        tr.insert(tr.root, i, c);
    }
    // prL(tr.query(tr.root, 0, n - 1));
    while(m--) {
        int type = scd();
        int l = scd(), r = scd();
        if(type == 1) tr.reverse(tr.root, --l, --r);
        else prL(tr.query(tr.root, --l, --r));
    }
    return 0;
}