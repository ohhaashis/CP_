#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define For(i,n) for(int i=0;i<n;i++)
#define icin long long n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

void solve(){
    int n,m; cin>>n>>m;

    vll a(n) , b(m);
    For(i,n) cin>>a[i];
    For(i,m) cin>>b[i];

    ll a_cnt = a[0] + n-1;
    ll b_cnt = b[0] + m-1;

    if(a_cnt>=b_cnt){
        cout<<1<<endl;
    }else{
        cout<<2<<endl;
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