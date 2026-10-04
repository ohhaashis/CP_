#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define FOR(i,n) for(int i=0;i<n;i++)
#define icin int n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

void solve() {
    icin;
    vll arr(n);
    FOR(i,n) cin>>arr[i];

    ll left = 0 , right = n-1 ;
    ll s = 0 , d= 0;
    bool flag = true;

    while(left<=right){
        ll c ;
        if(arr[left]>arr[right]){
            c= arr[left];
            left++;
        }else{
            c = arr[right];
            right--;
        }

        if(flag){
            s+=c;
        }else{
            d += c;
        }

        flag = !flag;
    }cout<<s<<" "<<d<<endl;
}


int32_t main(){
    IO;
    // int t;
    // cin>>t;
    // while(t--){
    solve();
    //}
}