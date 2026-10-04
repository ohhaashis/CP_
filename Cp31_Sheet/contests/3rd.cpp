#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define For(i,n) for(long long i=0;i<n;i++)
#define icin long long n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

ll calcPart(ll x , vector<ll>& d , vector<ll>& p){
    if(x<=0){
        return 0;
    }

    x = min(x,d.back());

    ll i= lower_bound(d.begin(),d.end(),x) - d.begin();
    ll p_d = 0;
    if(i>0){
        p_d = d[i-1];
    }

    ll ht = d.back()/d[i];
    ll pt = x - p_d;

    return p[i]+(pt*ht);
}

void solve(){
    ll s , q;
    cin>>s>>q;

    vll d;
    for(ll i = 1 ; i*i<=s ; i++){
        if(s%i==0){
            d.push_back(i);

            if(i*i !=s){
                d.push_back(s/i);
            }
        }
    } sort(d.begin(),d.end());

    int j = d.size() ;

    vll arr(j+1,0);

    For(i,j){
        ll p = 0;
        if(i==0){
            p = 0;
        }else{
            p = d[i-1];
        }

        ll h = s/d[i];
        arr[i+1] = arr[i] + (d[i]-p)*h;
    }

    while(q--){
        ll x,y;
        cin>>x>>y;

        int pos = upper_bound(d.begin(),d.end(),s/y) - d.begin();
        ll lim_d = 0;

        if(pos>0) lim_d = d[pos-1];

        if(x<= lim_d){
            cout<<x*y<<endl;
        }else{
            ll full_area = lim_d*y;
            ll rem_area = calcPart(x,d,arr) - calcPart(lim_d,d,arr);
            cout<<full_area+rem_area<<endl;
        }
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