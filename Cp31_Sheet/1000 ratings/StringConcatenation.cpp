#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define FOR(i,n) for(long long i=0;i<n;i++)
#define icin long long n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

void solve() {
    ll n,k;cin>>n>>k;

    if(k==n-1){
        cout<<-1<<endl;
        return ;
    }

    int z = n/2 ;
    int o = (n+1)/2;

    int rem = n-k;

    int oCnt = (rem+1)/2;
    int zCnt = rem/2;

    int oRem = o-oCnt;
    int zRem = z-zCnt;

    string str = "";

    for(int i = 0 ; i<rem ; i++){
        if(i%2==0){
            str += '1';
        if(i==0){
            for(int j = 0 ; j<oRem ; j++) str += '1';
        }      
        } else{
            str += '0';
            if(i==1){
                for(int j = 0 ; j<zRem ; j++) str += '0';
            }
        } 
    }

    FOR(i,n){
        cout<<str[i];
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