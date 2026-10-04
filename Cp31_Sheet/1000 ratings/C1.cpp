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
    vll a(n);
    FOR(i, n) cin>>a[i];
    ll ans = 0;
    FOR(i, n) ans += a[i];


    int flips = 0;
    vll idx;
    for(int i = n-1 ; i>=0 ; i--){
        if(flips%2!=0){
            a[i] = -a[i];
        } 

        if(a[i]>0){
            flips++;
            idx.push_back(i);
        }
        
    }
    cout<<flips<<endl;
    for(int i = 0 ; i<idx.size() ; i++){
        cout<<idx[i]+1<<" ";
    }
    cout<<endl;
}


int32_t main(){
    IO;
    int t;
    cin>>t;
    while(t--){
    solve();
    }
}