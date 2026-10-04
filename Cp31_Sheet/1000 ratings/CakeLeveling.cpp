#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define FOR(i,n) for(long long i=0;i<n;i++)
#define icin int n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

void solve() {
    icin;
    vll arr(n);
    FOR(i,n) cin>>arr[i];
    
    ll ans = INT_MAX , prefix = 0;

    FOR(i,n){
        prefix += arr[i];
        ll curr_h = (prefix/(i+1));
        ans = min(ans,curr_h);
         cout<<ans<<" ";
    }cout<<endl;
   
}


int32_t main(){
    IO;
    int t;
    cin>>t;
    while(t--){
    solve();
    }
}