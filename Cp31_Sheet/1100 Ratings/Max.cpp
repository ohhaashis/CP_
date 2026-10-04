// #include <bits/stdc++.h>
// using namespace std;

// #define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

// using ll  = long long;
// using ull = unsigned long long;
// using lld = long double;
// using pii = pair<int, int>;
// using pll = pair<ll, ll>;
// using vi  = vector<int>;
// using vll = vector<ll>;
// using vvi = vector<vector<int>>;
// using vvll= vector<vector<ll>>;
// using vllp = vector<pair<ll,ll>>;

// const ll INF = 2e18;         
// const int MOD = 1e9 + 7;    
// const int MOD2 = 998244353;

// #define all(x) (x).begin(), (x).end()
// #define rall(x) (x).rbegin(), (x).rend()
// #define sz(x) (int)((x).size())
// #define pb push_back
// #define eb emplace_back
// #define fi first
// #define se second

// #define rep(i, a, b) for (ll i = (a); i < (b); ++i)
// #define per(i, a, b) for (ll i = (b) - 1; i >= (a); --i)
// #define fll(x) for(ll ele : (x))
// #define fch(x) for(char ch : (x))
// #define fe(it, x) for(auto& it : (x))

// #define nl '\n'


// ll power(ll base, ll exp, ll m = MOD) {
//     ll res = 1;
//     base %= m;
//     while (exp > 0) {
//         if (exp & 1) res = (res * base) % m;
//         base = (base * base) % m;
//         exp >>= 1;
//     }
//     return res;
// }

// ll modInverse(ll n, ll m = MOD) {
//     return power(n, m - 2, m);
// }

// bool isPrime(ll n) {
//     if (n <= 1) return false;
//     if (n <= 3) return true;
//     if (n % 2 == 0 || n % 3 == 0) return false;
//     for (ll i = 5; i * i <= n; i += 6) {
//         if (n % i == 0 || n % (i + 2) == 0) return false;
//     }
//     return true;
// }

// ll lcm (ll a , ll b){
//     return (a*b)/(__gcd(a,b));
// }

// void solve(){
//     ll n,k; cin>>n>>k;
//     vll arr(n);
//     ll ans = 0;
//     rep(i,0,n){
//         cin>>arr[i];
//         ans += arr[i];
//     }
//     sort(all(arr));
//     ll lo1 = 0 ,lo2 = 1, hi = n-1;
//     while(k--){
//         if( (arr[lo1]+arr[lo2])<arr[hi] ){
//             ans -= (arr[lo1]+arr[lo2]);
//             lo1+=2;
//             lo2+=2;
//         }else{
//             ans -= arr[hi];
//             hi--;
//         }
//         if((lo2>=n) || (hi<=0) ){
//             break;
//         }
//     }
//     cout<<ans<<nl;
// }

// int main() {
//     FAST_IO;
//     int t;
//     cin >> t;
//     while (t--) {
//         solve();
//     }
//     return 0;
// }

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
#define fe(it, x) for(auto& it : (x))

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
    return (a / __gcd(a, b)) * b;
}

// void solve(){
//     ll n, k; 
//     cin >> n >> k;
//     vll arr(n);  
//     rep(i, 0, n){
//         cin >> arr[i];
//     }
//     sort(all(arr));
//     vll pref(n + 1, 0);
//     rep(i, 0, n){
//         pref[i + 1] = pref[i] + arr[i];
//     }
    
//     ll max_sum = 0;
//     for(int i = 0; i <= k; i++){
//         int left_removed = 2 * i;
//         int right_removed = k - i;       
//         ll current_sum = pref[n - right_removed] - pref[left_removed];
//         max_sum = max(max_sum, current_sum);
//     }
//     cout << max_sum << nl;
// }


void solve(){
    int n; cin>>n;
    ll cs = 0 ;
    ll rs =0;
    bool poss = true;
    rep(i,1,n+1){
        ll ai ;
        cin>>ai;
        cs+=ai;
        rs+=i;
        if(cs<rs){
            poss=false;
        }
    }
    if(poss){
        cout<<"YES"<<nl;
    }else{
        cout<<"NO"<<nl;
    }
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