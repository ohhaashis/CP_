#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define FOR(i,n) for(long long i=0;i<n;i++)
#define icin int n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

void solve() {
    int n,x,s;
    cin>>n>>x>>s;

    string str;
    cin>>str;

    int table_left = x;
    int ppl_in_seaats = 0;
    int ppl_seated = 0;
    ll seat_avail = 0;
    for(char ch : str){
        if(ch=='I'){
            if(table_left!=0){
                table_left--;
                seat_avail +=(s-1);
                ppl_seated++;
            }
        }else if(ch == 'A'){
            if(seat_avail !=0){
                seat_avail--;
                ppl_in_seaats++;
                ppl_seated++;
            }else if(table_left!=0){
                table_left--;
                seat_avail += (s-1);
                ppl_seated++;
            }
        }else if(ch=='E'){
            if(seat_avail != 0){
                seat_avail--;
                ppl_seated++;
            }else if(ppl_in_seaats!=0 && table_left!=0){
                ppl_in_seaats--;
                table_left--;
                seat_avail += (s-1);
                ppl_seated++;
            }
        }
    }cout<<ppl_seated<<endl;
}


int32_t main(){
    IO;
    int t;
    cin>>t;
    while(t--){
    solve();
    }
}