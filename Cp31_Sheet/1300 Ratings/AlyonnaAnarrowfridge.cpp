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
    ll n,h; cin>>n>>h;
    vll arr(n);
    rep(i,0,n) cin>>arr[i];

    ll k_ans= 0;

    rep(k,1,n+1){
        vll temp(arr.begin(),arr.begin()+k);
        sort(rall(temp));
        ll ht = 0;
        for(ll i = 0 ; i<k ; i+=2){
            ht += temp[i];
        }

        if(ht<=h){
            k_ans = k;
        }else{
            break;
        }
    }cout<<k_ans<<"\n";
}

int main() {
    int T = 1;
    //cin>>T;
    while(T--){
        int n;
        cin>>n;
        int cnt = 0;

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                int t;
                cin>>t;
                if(i!=j && t>0)
                    cnt++;
            }
        }
        if(cnt == n*(n-1))
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
    return 0;
}