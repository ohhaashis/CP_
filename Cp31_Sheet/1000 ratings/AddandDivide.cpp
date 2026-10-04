#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define v vector<int>
#define vll vector<long long>
#define v2d vector< vector<long long >>
#define vp vector< pair<int,int> >
#define For(i,n) for(long long i=0;i<n;i++)
#define icin long long n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

const long long inf = 1e15;
const int mod = 998244353;

void solve(){
    ll a,b; cin>>a>>b;

    ll x = a;

    ll cnt = inf;
    for(ll i = 0; i < 30; ++i){
        ll curr_b = b+i;
        if(curr_b ==1){
            continue;
        }

        ll temp_a = a;
        ll curr_ops = i;

        while(temp_a>0){
            temp_a /= curr_b;
            curr_ops++;
        }

        cnt = min(cnt,curr_ops);
    }
    cout<<cnt<<endl;
}

int32_t main(){
    IO;
    int t;
    cin>>t;
    while(t--){
    solve();
    }
}