// #pragma GCC optimize("O3,unroll-loops")   // uncomment for heavy loops (most judges already use -O2)
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll   = long long;
using ull  = unsigned long long;
using ld   = long double;
using u128 = __uint128_t;
using pii  = pair<int, int>;
using pll  = pair<ll, ll>;
using vi   = vector<int>;
using vll  = vector<ll>;
using vvi  = vector<vector<int>>;
using vvll = vector<vector<ll>>;
using vllp = vector<pair<ll, ll>>;

const ll INF = 1e18;          // safe headroom: INF + INF still fits in ll
const ll MOD = 1e9 + 7;       // ll, so a*b%MOD never overflows by accident

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)((x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

#define rep(i, a, b) for (ll i = (a); i < (b); ++i)
#define per(i, a, b) for (ll i = (b) - 1; i >= (a); --i)
#define fll(x) for (ll ele : (x))
#define fch(x) for (char ch : (x))
#define fit(it, x) for (auto &it : (x))

#define nl '\n'

// ---------- I/O helpers (pair first so vector<pair> works) ----------
template<class A, class B> istream& operator>>(istream& is, pair<A, B>& p) { return is >> p.fi >> p.se; }
template<class A, class B> ostream& operator<<(ostream& os, const pair<A, B>& p) { return os << p.fi << ' ' << p.se; }
template<class T> istream& operator>>(istream& is, vector<T>& v) { for (auto& x : v) is >> x; return is; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) {
    for (size_t i = 0; i < v.size(); i++) os << (i ? " " : "") << v[i];
    return os;
}

// ---------- Debug (compile with -DLOCAL; vanishes on the judge) ----------
#ifdef LOCAL
template<class T> void _dbg(const T& t) { cerr << t << endl; }
template<class T, class... U> void _dbg(const T& t, const U&... u) { cerr << t << " | "; _dbg(u...); }
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]: ", _dbg(__VA_ARGS__)
#else
#define dbg(...)
#endif

// ---------- Small utilities ----------
template<class T> bool chmin(T& a, const T& b) { return b < a ? a = b, true : false; }
template<class T> bool chmax(T& a, const T& b) { return a < b ? a = b, true : false; }

ll fdiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }   // floor division (handles negatives)
ll cdiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); }   // ceil division (handles negatives)

ll isqrt(ll n) {                                                 // exact floor(sqrt(n)), no float errors
    ll r = sqrtl((ld)n);
    while (r * r > n) r--;
    while ((r + 1) * (r + 1) <= n) r++;
    return r;
}

int topbit(ll x) { return x ? 63 - __builtin_clzll(x) : -1; }
int lowbit(ll x) { return x ? __builtin_ctzll(x) : -1; }
int popcnt(ll x) { return __builtin_popcountll(x); }

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// ---------- Number theory ----------
ll power(ll base, ll exp, ll m = MOD) {                          // fast, for m up to ~3e9
    ll res = 1;
    base %= m; if (base < 0) base += m;
    while (exp > 0) {
        if (exp & 1) res = res * base % m;
        base = base * base % m;
        exp >>= 1;
    }
    return res;
}

ll modInverse(ll n, ll m = MOD) { return power(n, m - 2, m); }   // m must be prime

ll mulmod(ll a, ll b, ll m) { return (u128)a * b % m; }           // safe for m up to 1e18
ll powmod(ll base, ll exp, ll m) {
    ll res = 1;
    base %= m; if (base < 0) base += m;
    while (exp > 0) {
        if (exp & 1) res = mulmod(res, base, m);
        base = mulmod(base, base, m);
        exp >>= 1;
    }
    return res;
}

bool isPrime(ll n) {                                              // deterministic Miller-Rabin, O(log n), exact for all 64-bit n
    if (n < 2) return false;
    for (ll p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
        if (n % p == 0) return n == p;
    ll d = n - 1; int s = 0;
    while ((d & 1) == 0) d >>= 1, s++;
    for (ll a : {2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL}) {
        if (a % n == 0) continue;
        ll x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mulmod(x, x, n);
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

// use std::gcd(a, b) and std::lcm(a, b) directly (C++17)

// ---------- Data structures ----------
// ordered_set: find_by_order(k) -> k-th element (0-indexed), order_of_key(x) -> count of elements < x
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// for duplicates use ordered_set<pair<T, int>> with a unique index as the second value

struct custom_hash {                                             // anti-hack hash: unordered_map<ll, ll, custom_hash>
    static ull splitmix64(ull x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(ull x) const {
        static const ull FIXED = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED);
    }
};

// =====================================================================

void solve() {

}

int main() {
    FAST_IO;
    int t = 1;
    cin >> t;            // comment out for single-test problems
    while (t--) solve();
    return 0;
}