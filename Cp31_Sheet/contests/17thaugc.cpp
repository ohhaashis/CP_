#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define For(i,n) for(long long i=0;i<n;i++)
#define icin long long n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

void solve(){
    ll s,q ; cin>>s>>q;

    vector< pair<ll,ll>> rects;
    for(ll i = 1 ;i*i<=s ; i++){
        if(s%i==0){
            rects.push_back({i,s/i});
            if( i!=s/i ) rects.push_back({s/i,i});
        }
    }

    sort(rects.begin(),rects.end());

    ll m = rects.size();

    vll pre(m);
    pre[0] = rects[0].first*rects[0].second ;

    for(ll i = 1; i<m ; i++){
        pre[i] = (rects[i].first - rects[i-1].first)*rects[i].second + pre[i-1];
    }

    For(i,q){
        ll x,y ; cin>>x>>y;

        ll lo = 0 , hi = m;

        while(hi-lo>1){
            ll mid = lo + (hi-lo)/2 ;
            if(rects[mid].second >= y) lo = mid;
            else hi = mid;
        }
        ll idx1 = lo ;
        
        lo = 0 , hi = m;

        while(hi-lo>1){
            ll mid = lo + (hi-lo)/2 ;

            if(rects[mid].first <=x) lo = mid;
            else hi = mid;
        }

        ll idx2 = lo;

        idx1 = min(idx1,idx2);
        ll ans = rects[idx1].first*y + pre[idx2]-pre[idx1];

        if(idx2 + 1 <m){
            ans += (x-rects[idx2].first)*min(y,rects[idx2+1].second);
        }

        cout<<ans<<endl;
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