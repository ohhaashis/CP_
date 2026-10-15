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

void solve(){
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x :a) cin >> x;

    vector<int> ones;
    int firstNeg = -1, lastNeg = -1;
    rep(i,0,n){
        if (a[i]==1) ones.push_back(i);
        else if (a[i] == -1) {
            if (firstNeg==-1) firstNeg = i;
            lastNeg = i;
        }
    }

    int li = -1,rj = -1;
    if(ones.empty()){
        if (firstNeg != -1) {
            li = firstNeg;
            rj = lastNeg;
        }
    }else{
        int bestLen = 1;
        li = ones[0];
        rj = ones[0];
        if(firstNeg != -1 && firstNeg < ones[0]){
            int len = ones[0] - firstNeg + 1;
            if (len>bestLen) { bestLen = len; li = firstNeg; rj = ones[0]; }
        }
        if(lastNeg != -1 && lastNeg > ones.back()){
            int len = lastNeg - ones.back() + 1;
            if (len > bestLen) { bestLen = len; li = ones.back(); rj = lastNeg; }
        }
        for(int k = 0; k + 1 < (int)ones.size(); k++){
            int len = ones[k+1] - ones[k] + 1;
            if (len > bestLen) { bestLen = len; li = ones[k]; rj = ones[k+1]; }
        }
    }

    if(li != -1){
        a[li] = 1;
        a[rj] = 1;
    }

    rep(i,0,n){
        if(a[i]== -1) a[i]= 0;
    }

    rep(i,0,n){
        cout<<a[i]<<" ";
    }cout<<endl;
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
