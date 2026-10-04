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
    ll n,m; cin>>n>>m;

    vector<vll> adj(n+1);
    vector<vll> un_adj(n+1);
    vll in(n+1,0);

    rep(i,0,m){
        ll u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        un_adj[u].push_back(v);
        un_adj[v].push_back(u);
        in[v]++;
    }

    vector<bool>visited(n+1,false);
    ll ans =0;

    rep(i,1,n+1){
        if(visited[i]==true){
            continue;
        }
        queue<ll>q;
        vll nodes;

        q.push(i);
        visited[i]=true;

        while(!q.empty()){
            ll u = q.front();
            q.pop();
            nodes.push_back(u);
            for(ll v: un_adj[u]){
                if(visited[v]==false){
                    visited[v]=true;
                    q.push(v);
                }
            }//
        }

            ll k = nodes.size();
            
            if(k<=1) continue;

            queue<ll>q2;

            for(ll v : nodes){
                if(in[v]==0){
                    q2.push(v);
                }
            }

            ll cnt = 0;
            while(!q2.empty()){
                ll u = q2.front();
                q2.pop();
                cnt++;
                for(ll v : adj[u]){ 
                    in[v]--;
                    if(in[v]==0){
                        q2.push(v);
                    }
                }
            }

            if(cnt==k){
                ans += (k-1);
            }else{
                ans+=k;
            }
        }
        cout<<ans<<"\n";
}

int main() {
    FAST_IO;
    // int t;
    // cin >> t;
    // while (t--) {
        solve();
    //}
    return 0;
}