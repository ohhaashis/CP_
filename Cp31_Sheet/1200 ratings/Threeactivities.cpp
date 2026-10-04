#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

using ll  = long long;
using ull = unsigned long long;
using lld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi  = vector<int>;
using vll = vector<ll>;
using vvi = vector<vector<int>>;
using vvll= vector<vector<ll>>;

const ll INF = 1e18;         
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

void solve(){
    ll n; cin>>n;
    vector<pll> a(n),b(n),c(n);
    rep(i,0,n){
        cin>>a[i].first;
        a[i].second = i;
    }
    rep(i,0,n){
        cin>>b[i].first;
        b[i].second = i;
    }
    rep(i,0,n){
        cin>>c[i].first;
        c[i].second = i;
    }

    ll ans = 0;

    sort(a.rbegin(),a.rend());
    sort(b.rbegin(),b.rend());
    sort(c.rbegin(),c.rend());

    rep(i,0,min((ll)3,n)){
        rep(j,0,min((ll)3,n)){
            rep(k,0,min((ll)3,n)){
                if(a[i].second != b[j].second && a[i].second != c[k].second && b[j].second != c[k].second ){
                    ll curr_sm = a[i].first + b[j].first + c[k].first;
                    ans = max(ans,curr_sm);
                }
            }
        }
    } cout<<ans<<endl;
}

int main() {
    FAST_IO;

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

    // ll day1 = -1 , day2 = -1 , day3 = -1;

    // ll ans = 0;
    // ll prev_max = INT_MIN;

    // ll mxa = INT_MIN , mxb = INT_MIN , mxc = INT_MIN ;

    // for(ll ele : a){
    //     mxa = max(mxa,ele);
    // }
    // for(ll ele : b){
    //     mxb = max(mxb,ele);
    // }
    // for(ll ele : c){
    //     mxc = max(mxc,ele);
    // }

    // rep(i,0,n){
    //     if()
    // }