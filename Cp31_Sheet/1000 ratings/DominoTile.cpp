#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define For(i,n) for(long long i=0;i<n;i++)
#define icin long long n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

void solve(){
    icin;
    string s; cin>>s;

    For(i,n){
        if(s[i] != '?'){
            if( (i/2)%2 != 0 ){
                if( s[i] == '0' ) s[i]='1';
                else s[i] = '0';
            }
        }
    }

    bool e0 = false, e1 = false , o0 = false, o1 = false;

    For(i,n){
        if(s[i] != '?'){
            if(i%2==0){
            if(s[i]=='0') e0 = true;
            if(s[i]=='1') e1= true;
            }else{
            if(s[i]=='0') o0 = true;
            if(s[i]=='1') o1= true;
            }
        }
    }

    ll eve = 0 , od = 0;

    if(!e0 && !e1) eve=2;
    else if(e0 && e1) eve = 0;
    else eve = 1;

    if(!o0 && !o1) od=2;
    else if(o0 && o1) od = 0;
    else od = 1;

    cout<<(od*eve)%998244353<<endl;
}

int32_t main(){
    IO;
    int t;
    cin>>t;
    while(t--){
    solve();
    }
}