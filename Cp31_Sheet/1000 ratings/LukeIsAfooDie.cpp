#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define FOR(i,n) for(long long i=0;i<n;i++)
#define icin int n; cin>>n;
#define IO                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

void solve() {
    ll n,x;
    cin>>n>>x;
    vll arr(n);
    FOR(i,n) cin>>arr[i];

    ll mn = arr[0],mx=arr[0];
    int changes = 0;
    FOR(i,n){
        mn = min(mn,arr[i]);
        mx = max(mx,arr[i]);
        if((mx-mn)>2*x){
            changes++;
            mn = arr[i];
            mx = arr[i];
        }
    }cout<<changes<<endl;
}

int32_t main() {
    IO;
     int t;
     cin >> t;
     while (t--) {
        solve();
    }
     return 0;
}