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
    ll n,k;
    cin>>n>>k;
    vll a(n) , q(k); cin>>a>>q;
    // vll ans;

    // rep(i,0,sz(q)){
    //     ll x= q[i];
    //     ll ans_i = 0;
    //     rep(j,0,sz(a)){
    //         ll y = a[j];
    //         if(x>=y){
    //             ans_i += a[j];
    //         }else{
    //             break;
    //         }
    //     }
    //     ans.pb(ans_i);
    // }

    // fll(ans){
    //     cout<<ele<<" ";
    // }cout<<nl;

    vll p_max(n+1,0);
    vll p_sum(n+1,0);

    vll ans;

    rep(i,0,n){
        p_max[i+1] = max(p_max[i],a[i]);
        p_sum[i+1] = p_sum[i]+a[i];
    }

    fll(q){
        ll lo = 1 , hi = n;
        ll idx = 0;
        while(lo<=hi){
            ll mid = lo+(hi-lo)/2;

            if(ele>=p_max[mid]){
                idx = mid;
                lo = mid+1;
            }else{
                hi = mid-1;
            }
        }
        cout<<p_sum[idx]<<" ";
    }cout<<nl;
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