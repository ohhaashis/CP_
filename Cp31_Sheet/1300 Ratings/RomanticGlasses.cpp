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

ll lcm (ll a , ll b){
    return (a*b)/(__gcd(a,b));
}

ll calcSum(ll st , ll end){
    ll sum = ( (st+end)*(end-st+1) )/2;
    return sum;
}

void solve(){  
    ll n; cin>>n;
    vll a(n);
    rep(i,0,n) cin>>a[i];
    vll ev , od;
    ll cntE = 0, cntO = 0;
    rep(i,0,n){
        if((i+1)%2==0){
            ev.push_back(a[i]);
            cntE += a[i];
        }else{
            od.push_back(a[i]);
            cntO += a[i];
        }
    }
    if(cntE==cntO){
        cout<<"YES"<<endl;
        return;
    }
    vll pf(n);
    pf[0]=a[0];
    rep(i,1,n){
        if((i)%2==0){
            pf[i] = a[i]+pf[i-1];
        }else{
            pf[i] = pf[i-1]-a[i];
        }
    }
    rep(i,0,n){
        if(pf[i]==0){
            cout<<"YES"<<endl;
            return;
        }
    }
    sort(all(pf));
    rep(i,1,n){
        if(pf[i]==pf[i-1]){
            cout<<"YES"<<endl;
            return;
        }
    }
    cout<<"NO"<<endl;
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