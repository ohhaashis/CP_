#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

using ll  = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi  = vector<int>;
using vll = vector<ll>;
using vvi = vector<vector<int>>;
using vvll= vector<vector<ll>>;
using vllp = vector<pair<ll,ll>>;

const ll INF = 2e18;         
const int MOD = 1e9 + 7;    
const int MOD2 = 998244353;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)((x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

#define rep(i, a, b) for (ll i = (a); i < (b); ++i)
#define per(i, a, b) for (ll i = (b) - 1; i >= (a); --i)
#define fll(x) for(ll ele : (x))
#define fch(x) for(char ch : (x))
#define fit(it, x) for(auto& it : (x))

#define nl '\n'

template<class T> istream& operator>>(istream& is, vector<T>& v) {
    for (auto& x : v) is >> x;
    return is;
}

ll power(ll base, ll exp, ll m = MOD) {
    ll res = 1;
    base %= m;
    if (base < 0) base += m;
    while (exp > 0) {
        if (exp & 1) res = res * base % m;
        base = base * base % m;
        exp >>= 1;
    }
    return res;
}

ll modInverse(ll n, ll m = MOD) {
    return power(n, m - 2, m);
}

bool isPrime(ll n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

ll lcm(ll a, ll b) {
    return a/ __gcd(a, b)*b;
}

void solve(){
    ll n; cin>>n;
    vll a(n) ; cin>>a;
   // ll m = n/2;
    vll l , r;
    l.pb(a[0]);
    rep(i,1,n){
        ll x = l[i-1]+a[i];
        l.pb(x);
    }
    r.pb(a[n-1]);
    for(ll i = n-2 ; i>=0 ; i--){
        ll x = r.back() + a[i];
        r.pb(x);
    }
    ll i = 0, j = 0;
    //bool found = false;
    ll ans = 0;

    while(i<sz(l) && j<sz(r)){
    if(l[i]== r[j]){
        if( (i+j+2)<=n){
            ans = max(ans,(i+j+2));
        }i++;j++;
    }else if(l[i]<r[j]){
        i++;
    }else{
        j++;
    }

} cout<<ans<<nl;
}

int main() {
    FAST_IO;
    int t ;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}