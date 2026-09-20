#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define For(i,n) for(long long i=0;i<n;i++)
#define icin long long n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

void solve(){
    ll n,k; cin>>n>>k;

    string s;
    cin>>s;
    
    ll len = 2*n;
    string next_s=s;
    For(i,len){
        if(s[i]=='1' && s[(i+1)%len]=='0'){
            next_s[i]='0';
            next_s[(i+1)%len]='1';
        }
    }
    ll r=0,b=0;
    For(i,len){
        if(next_s[i]=='1'){
            if(i%2!=0) r++;
            else b++;
        }
    }
    cout<<r<<" "<<b<<endl;
}

int32_t main(){
    IO;
    int t;
    cin>>t;
    while(t--){
    solve();
    }
}