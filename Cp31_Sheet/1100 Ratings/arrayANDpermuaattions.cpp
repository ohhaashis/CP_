#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define FOR(i,n) for(int i=0;i<n;i++)
#define icin int n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

void solve() {
    ll n;cin>>n;
    for(ll k = 2 ; ; k++){
        ll su =(1LL<<k) - 1;
        if(n%su == 0){
            cout<<n/su<<endl;
            break;
        }
    }


}


int32_t main(){
    IO;
    int t;
    cin>>t;
    while(t--){
    solve();
    }
}