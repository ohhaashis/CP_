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
    ll n;cin>>n;

    ll b_len = n*(n-1)/2;
    vll b(b_len);
    rep(i,0,b_len) cin>>b[i];
    sort(b.begin(),b.end());

    ll idx = 0;
    ll step = n-1;

    while(step>0){
        cout<<b[idx]<<" ";
        idx+= step;
        step--;
    }
    cout<<b.back();
    cout<<endl;




    // ll a_len = n;
    // n = n*(n-1)/2;
    // vll b(n);
    // rep(i,0,n) cin>>b[i];
    // //
    // //sort(b.begin(),b.end());
    // map<ll, ll> fq;
    // ll mx = INT_MIN;
    // for(ll ele : b){
    //     fq[ele]++;
    //     mx = max(mx,ele);
    // }
    // vll a;
    
    // rep(i,0,a_len-1){
    //     auto it = fq.begin();
    //     ll curr_min = it->first;

    //     a.push_back(curr_min);

    //     ll pf = a_len-1-i;
    //     it->second -= pf ;

    //     if(it->second<=0){
    //         fq.erase(it);
    //     }
    // }
    // a.push_back(mx);
    // for(ll ele : a) cout<<ele<<" ";
    // cout<<endl;
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