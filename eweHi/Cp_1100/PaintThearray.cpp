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

bool isPd(const vector<ll>& arr) {
    if (arr.empty() || arr.size()==1) return true;
    int l = 0, r = arr.size() - 1;
    while(l < r) {
        if(arr[l] != arr[r]) {
            return false;
        }
        l++;
        r--;
    }
    return true;
}

pair<ll, ll> pDindices(const vector<ll>& arr) {
    if (arr.size() <= 1) return {-1, -1};
    
    ll l = 0, r = arr.size() - 1;
    while(l < r) {
        if(arr[l] != arr[r]) {
            return {l, r};
        }
        l++;
        r--;
    }
    return {-1, -1};
}

void solve(){
    ll n;cin>>n;
    vll arr(n);
    cin>>arr;

    ll G1 = 0, G2 =0;
    rep(i,0,n){
        if((i+1)%2==0 ){
            G1 = __gcd(G1,arr[i]);
        }else{
            G2 = __gcd(G2,arr[i]);
        }
    }
    bool G1_is = true , G2_is = true;
    rep(i,0,n){
        if((i+1)%2==0 ){
            if(arr[i]%G2==0){
                G2_is= false;
            }
        }else{
            if( arr[i]%G1==0 ){
                G1_is = false;
            }
        }
    }
    if(G1_is){
        cout<<G1<<nl;
        return;
    }else if(G2_is){
        cout<<G2<<nl;
        return;
    }else if(!G1_is && !G2_is){
        cout<<0<<nl;
        return;
    }
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