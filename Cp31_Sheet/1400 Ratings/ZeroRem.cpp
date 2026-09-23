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


ll power(ll base, ll exp, ll m = MOD) {
    ll res = 1;
    base %= m;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % m;
        base = (base * base) % m;
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

ll lcm (ll a , ll b){
    return (a*b)/(__gcd(a,b));
}

ll get_msb(ll x) {
    ll msb = -1;
    while (x > 0) {
        msb++;
        x >>= 1;
    }
    return msb;
}

void solve(){
    ll n,k; cin>>n>>k;
    // vll arr(n);
    // rep(i,0,n) cin>>arr[i];

    // ll ele = n;
    // vector<bool>done(n,false);

    // ll ans = 0;
    // rep(i,0,n){
    //     ll val = arr[i];
    //     if(val%k==0){
    //         done[i]=true;
    //         ele--;
    //     }
    // }

    // ll x = 0;

    // while(ele>0){
    //     rep(i,0,n){
    //         if(!done[i]){
    //             if((arr[i]+x)%k==0){
    //                 arr[i]+=x;
    //                 done[i]=true;
    //                 ele--;
    //                 break;
    //             }
    //         }
    //     }x++;;
    // }cout<<x<<nl;

    map<ll,ll> count;
    ll ans = 0;

    rep(i,0,n){
        ll val;cin>>val;

        if(val%k!=0){
            ll need = k-(val%k);
            count[need]++;

            ll moves = need+(count[need]-1)*k+1;
            ans = max(ans,moves);
        }
    }cout<<ans<<nl;
}

int main() {
    FAST_IO;

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    //solve();

    return 0;
}