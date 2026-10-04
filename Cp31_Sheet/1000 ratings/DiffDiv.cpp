#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define v vector<int>
#define vll vector<long long>
#define v2d vector< vector<long long >>
#define vp vector< pair<int,int> >
#define For(i,n) for(long long i=0;i<n;i++)
#define icin long long n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

const long long inf = 1e15;
const int mod = 998244353;

bool isPrime(int n){
    if(n<=1) return false;
    for(int  i = 2 ; i*i <=n ; i++){
        if(n%i==0) return false;
    }return true;
}

void solve(){
    icin;

    ll p1 = 1+n;
    while(!isPrime(p1)) p1++;

    ll p2 = p1+n;
    while(!isPrime(p2)) p2++;

    cout<<p1*p2<<endl;
}

int32_t main(){
    IO;
    int t;
    cin>>t;
    while(t--){
    solve();
    }
}