#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define FOR(i,n) for(long long i=0;i<n;i++)
#define icin int n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

void solve() {
    icin;
    vector< pair<ll,int> > br(n);
    FOR(i,n){
        cin>>br[i].first;
        br[i].second = i+1;
    }

    sort(br.begin(),br.end(),[](const pair< ll , int>& a , const pair<ll,int>& b){
        return a.first > b.first;
    });

    vll ans(n+1);
    ans[0]=0;

    ll tot_time = 0;
    ll curr_dis = 1;
    bool flag = true;

    FOR(i,n){
        ll assign_coor = flag ? curr_dis : -curr_dis;

        ans[br[i].second] = assign_coor;

        tot_time += 2*br[i].first*curr_dis;

        if(!flag){
            curr_dis++;
        }
        flag = !flag;


    }
         cout<<tot_time<<endl;
        for(int i = 0  ; i<= n ; i++){
            cout<<ans[i]<<" ";
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