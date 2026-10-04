#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define FOR(i,n) for(int i=0;i<n;i++)
#define icin int n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

void solve() {
    icin;
    vll arr(n);
    FOR(i,n) cin>>arr[i];
    sort(arr.begin(),arr.end());

    ll ans = 0;
    bool flag = true;

    FOR(i,n-1){
        if(arr[i]!=arr[i+1]){
            flag = false;
        }
    }
    if(flag == true){
        cout<<0<<endl;
        return;
    }

    ll target = arr[0]; 

    for(int i = 1; i < n; i++){ 
        ll temp = arr[i];
        ll steps = 0;
        while(temp != target){
            if(temp % 2 != 0) temp += 1;
            else temp /= 2;
            steps++;
        }
        ans += steps;
    }cout<<ans<<endl;
}


int32_t main(){
    IO;
    int t;
    cin>>t;
    while(t--){
    solve();
    }
}