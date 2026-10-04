#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define FOR(i,n) for(long long i=0;i<n;i++)
#define icin int n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

void solve() {
    ll w,h;
    cin>>w>>h;

    // => x axis k lie 
   
    
    // y = 0 ke lie 
    ll k0; cin>>k0;
    vll y0(k0);
    FOR(i,k0){
        cin>>y0[i];
    }

    //  y = h

    ll kh ; cin>>kh;

    vll yh(kh);
    FOR(i,kh){
        cin>>yh[i];
    }

    // => y axis ke lie 

    // x = 0
    ll k_0; cin>>k_0;

    vll x0(k_0);
    FOR(i,k_0){
        cin>>x0[i]; 
    }

    ll kw; cin>>kw;

    vll xw(kw);
    FOR(i,kw){
        cin>>xw[i];
    }

    ll ans = 0;
    ll max_horizontal_base = max(y0[k0 - 1] - y0[0], yh[kh - 1] - yh[0]);
    ll max_vertical_base = max(x0[k_0 - 1] - x0[0], xw[kw - 1] - xw[0]);
    if(w>h){
         // => x axis k lie 
        ans = max(max_horizontal_base * h, max_vertical_base * w);
    }else if(w<h){
        // => y axis k lie
        ans = max(max_horizontal_base * h, max_vertical_base * w);
    }else{
    ll base_mx = max(max_horizontal_base, max_vertical_base);
    ans = base_mx * w;       
    }    
    cout<<ans<<endl;
}


int32_t main(){
    IO;
    int t;
    cin>>t;
    while(t--){
    solve();
    }
}