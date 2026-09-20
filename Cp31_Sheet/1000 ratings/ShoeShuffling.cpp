#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define FOR(i,n) for(ll i=0;i<n;i++)
#define icin int n; cin>>n;
#define E endl;
#define IO                            \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);


void solve(){
    ll n;
    cin>>n;
    vll arr(n);
    FOR(i,n) cin>>arr[i];
    
    int count = 1;
    FOR(i,n){
        if(i==0) continue;
        if(arr[i]==arr[i-1]){
            count++;
        }else{
            if(count==1){
                cout<<-1<<endl;
                return;
            }
            count=1;
        }
    }
    if(count==1){
        cout<<-1<<endl;
        return;
    }

    ll l = 0;
    while(l<n){
        ll r = l;
        while(r+1<n && arr[r+1]==arr[l]){
            r++;
        }
        cout<<r+1<<" ";

        FOR(i=l,r){
            cout<<(i+1)<<" ";
        }l = r+1;
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