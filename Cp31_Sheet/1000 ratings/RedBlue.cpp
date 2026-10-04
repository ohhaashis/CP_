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
    int n,r,b;cin>>n>>r>>b;
    string str;

    int l = r/(b+1);

    int l_r = r%(b+1);

    for(int i = 1 ; i<=b+1 ; i++){
        for(int j = 0; j<l ; j++){
            str+='R';
        }
        if(l_r>0){
            str+='R';
            l_r--;
        }

        if(i != b+1){
            str+='B';
        }
    }cout<<str<<endl;
}


int32_t main(){
    IO;
    int t;
    cin>>t;
    while(t--){
    solve();
    }
}