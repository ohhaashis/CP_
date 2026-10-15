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
    vll a(n+1);
    rep(i,1,n+1) cin>>a[i];

    vllp spanning_tree;
    vector<bool>vis(n+1,false);

    queue<ll>q;
    q.push(1);
    vis[1]= true;

    while(!q.empty()){
        ll u = q.front();
        q.pop();

        rep(v,1,n+1){
            if(vis[v]==false && a[u]!=a[v]){
                vis[v]=true;
                spanning_tree.push_back({u,v});
                q.push(v);
            }
        }
    }

    if(sz(spanning_tree)==n-1){
        cout<<"YES\n";
        fit(edge,spanning_tree){
            cout<<edge.fi<<" "<<edge.se<<nl;
        }
    }else{
        cout<<"NO\n";
    }
    // vllp edges;

    // int v1 =1 , v2=-1;

    // rep(i,2,n+1){
    //     if(a[i]!=a[1]){
    //         edges.push_back({1,i});
    //         v2  = i;
    //         break;
    //     }
    // }
    // if(v2 == -1){
    //     cout<<"NO\n";
    //     return;
    // }

    // rep(i,2,n+1){
    //     if(i==v2){
    //         continue;
    //     }
    //     if(a[i]!=a[v1]){
    //         edges.push_back({v1,i});
    //     }else{
    //         edges.push_back({v2,i});
    //     }
    // }

    // cout<<"YES\n";
    // fit(it,edges){
    //     cout<<it.fi<<" "<<it.se<<nl;
    // }

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