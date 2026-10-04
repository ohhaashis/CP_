#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define FOR(i,n) for(int i=0;i<n;i++)
#define icin int n; cin>>n;
#define E endl;
#define IO                            \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);


void solve(){
    ll n,k;cin>>n>>k;
    vector<char>ch(n);
    for(int i = 0 ; i<n ; i++){
        cin>>ch[i];
    }
    int op = 0;
    
    FOR(i,k){
        if(ch[i]=='W') op++;
    }
    int steps = op;
    for(int i = k ; i<n ; i++){
        if(ch[i]=='W') op++;
        if(ch[i-k]=='W') op--;

        steps = min(steps,op);
    }cout<<steps<<endl;
}


int32_t main(){
    IO;
    int t;
    cin>>t;
    while(t--){
    solve();
    }
}