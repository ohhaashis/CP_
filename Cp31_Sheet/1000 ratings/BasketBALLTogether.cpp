#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define FOR(i,n) for(int i=0;i<n;i++)
#define icin int n; cin>>n;
#define IO                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

void solve() {
    ll n,d;
    cin>>n>>d;
    vll arr(n);
    FOR(i,n) cin>>arr[i];
    sort(arr.begin(),arr.end());
    ll lo = 0, hi = n-1,ans=0;
    while(lo<=hi){

        ll r = (d/arr[hi])+1;

        if(hi-lo+1>=r){
            ans++;
            hi--;
            lo+=(r-1);
        }else{
            break;
        }
    }
    cout<<ans<<endl;
}

int32_t main() {
    IO;
    //  int t;
    //  cin >> t;
    //  while (t--) {
        solve();
    // }
     return 0;
}