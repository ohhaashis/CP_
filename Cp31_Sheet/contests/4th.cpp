#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define v2d vector< vector<long long >>
#define vp vector< pair<int,int> >
#define For(i,n) for(long long i=0;i<n;i++)
#define icin long long n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

const long long inf = 1e15;
const int mod = 998244353;

void solve(){
    icin;

    For(i,n-1){
        int p ; cin>>p;
    }
    int m ; cin>>m;

    vector<ll>dams(m);
    For(i,m){
        cin>>dams[i];
    }
    cout<<m-1<<" ";

    if(m==1){
        cout<<endl;
        return;
    }

    sort(dams.begin(),dams.end());

    for(ll i = 1 ; i<m ;i++){
        cout<<dams[i]<<" ";
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