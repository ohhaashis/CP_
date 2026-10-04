#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define FOR(i,n) for(long long i=0;i<n;i++)
#define icin int n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

void solve() {
    ll a,b; cin>>a>>b;
    
    ll n = a-1;
    ll rem = n%4;

    ll ax ;
    if(rem==0){
        ax = n;
    }else{
        if(rem==1){
            ax = 1;
        }else if(rem==2){
            ax = n+1;
        }else{
            ax = 0;
        }
    }

    if(ax==b){
        cout<<a<<endl;
    }else if((ax^b)!=a){
        cout<<a+1<<endl;
    }else{
        cout<<a+2<<endl;
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