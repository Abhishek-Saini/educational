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

using ll = long long;
using ull = unsigned long long;
typedef unsigned int uint;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {
    return (ull)rng() % B;
}

const uint MOD = 1000000007;
template<uint mod = MOD> struct mint { // 1000000007  1000000009
    uint x;
 
    mint() : x(0) {}
    mint(ll _x) {
        _x %= mod;
        if (_x < 0) _x += mod;
        x = _x;
    }
 
    mint& operator += (const mint &a) {
        x += a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    mint& operator -= (const mint &a) {
        x += mod - a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    mint& operator *= (const mint &a) {
        x = (ull)x * a.x % mod;
        return *this;
    }
    mint pow(ll pw) const {
        mint res = 1;
        mint cur = *this;
        while(pw) {
            if (pw & 1) res *= cur;
            cur *= cur;
            pw >>= 1;
        }
        return res;
    }
    mint inv() const {
        assert(x != 0);
        uint t = x;
        uint res = 1;
        while(t != 1) {
            uint z = mod / t;
            res = (ull)res * (mod - z) % mod;
            t = mod - t * z;
        }
        return res;
    }
    mint& operator /= (const mint &a) {
        return *this *= a.inv();
    }
    mint operator + (const mint &a) const {
        return mint(*this) += a;
    }
    mint operator - (const mint &a) const {
        return mint(*this) -= a;
    }
    mint operator * (const mint &a) const {
        return mint(*this) *= a;
    }
    mint operator / (const mint &a) const {
        return mint(*this) /= a;
    }
 
    bool sqrt(mint &res) const {
        if (mod == 2 || x == 0) {
            res = *this;
            return true;
        }
        if (pow((mod - 1) / 2) != 1) return false;
        if (mod % 4 == 3) {
            res = pow((mod + 1) / 4);
            return true;
        }
        int pw = (mod - 1) / 2;
        int K = 30;
        while((1 << K) > pw) K--;
        while(true) {
            mint t = myRand(mod);
            mint a = 0, b = 0, c = 1;
            for (int k = K; k >= 0; k--) {
                a = b * b;
                b = b * c * 2;
                c = c * c + a * *this;
                if (((pw >> k) & 1) == 0) continue;
                a = b;
                b = b * t + c;
                c = c * t + a * *this;
            }
            if (b == 0) continue;
            c -= 1;
            c *= mint() - b.inv();
            if (c * c == *this) {
                res = c;
                return true;
            }
        }
        assert(false);
    }
 
    bool operator == (const mint &a) const {
        return x == a.x;
    }
    bool operator != (const mint &a) const {
        return x != a.x;
    }
    bool operator < (const mint &a) const {
        return x < a.x;
    }
};
using Mint = mint<MOD + 2>;

Mint Fen[lim], RevFen[lim];

Mint ReadFen(Mint Fen[], lld idx) {
  Mint sum = 0;
  while (idx > 0) {
    sum += Fen[idx];
    idx -= (idx & -idx);
  }
  return sum;
}

void ChangeFen(Mint Fen[], lld idx, lld n, Mint val) {
    // Error(idx, val.x);
  while (idx <= n) {
    Fen[idx] += val;
    idx += (idx & -idx);
  }
}

int main(){
    int n = scd(), m = scd();
    string S, Rev;
    cin >> S; Rev = S;
    reverse(all(Rev));
    Mint prime = 31;
    Mint po = prime;
    repI(i, 1, n) {
        ChangeFen(Fen, i, n, Mint(S[i - 1]) * po);
        po *= prime;
    }
    po = prime;
    repI(i, 1, n) {
        ChangeFen(RevFen, i, n, Mint(Rev[i - 1]) * po);
        po *= prime;
    }
    // repI(i, 1, n) {
    //     Mint val = ReadFen(RevFen, i) - ReadFen(RevFen, i - 1);
    //     Error(i, val.x);
    // }
    while(m--) {
        int type = scd();
        if(type == 1) {
            int idx = scd(); char c; cin >> c;
            ChangeFen(Fen, idx, n, (Mint(c) - Mint(S[idx - 1])) * Mint(prime).pow(idx));
            ChangeFen(RevFen, n - idx + 1, n, (Mint(c) - Mint(Rev[n - idx])) * Mint(prime).pow(n - idx + 1));
            // Error((Mint(c) - Mint(S[idx - 1])).x);
            // Error((Mint(prime).pow(idx)).x);
            // Error((Mint(c) - Mint(S[idx - 1])).x * Mint(prime).pow(idx).x);
            // Error((Mint(c) - Mint(Rev[n - idx])).x);
            // Error((Mint(prime).pow(n - idx + 1)).x);
            // Error((Mint(c) - Mint(Rev[n - idx])).x * Mint(prime).pow(n - idx + 1).x);
            S[idx - 1] = c;
            Rev[n - idx] = c;
            // repI(i, 1, n) {
            //     Mint val = ReadFen(RevFen, i) - ReadFen(RevFen, i - 1);
            //     Error(i, val.x);
            // }
        } else {
            int l = scd(), r = scd();
            Mint hash1 = ReadFen(Fen, r) - ReadFen(Fen, l - 1);
            hash1 *= Mint(prime).pow(n - r);
            Mint hash2 = ReadFen(RevFen, n - l + 1) - ReadFen(RevFen, n - r);
            hash2 *= Mint(prime).pow(l - 1);
            Error(hash1.x, hash2.x);
            if(hash1 == hash2) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
    // Mint val = 943047246;
    // Error(val.x);
    // val += Mint(22) * 642275998;
    // Error(val.x);
    // val += Mint(999999987) * 642275998;
    // Error(val.x);
    // val = Mint(56952883) + 926881040;
    // Error(val.x);
    return 0;
}