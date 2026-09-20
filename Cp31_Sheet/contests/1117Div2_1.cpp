#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vi vector<int>
#define vll vector<long long>
#define For(i,n) for(int i=0;i<n;i++)
#define icin long long n; cin>>n;
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);

void solve(){
    int n , m ; cin>>n>>m;

    vector<string>words(n);
    vector<string>abb(m);

    For(i,n){
        cin>>words[i];
    }

    For(i,m){
        cin>>abb[i];
    }
    vector<int>freq(26,0);

    For(i,n){
        if(words[i].size()!= 0){
            freq[ toupper(words[i][0]) - 'A' ]++;
        }
    }

    bool flag = true;
    For(i,m){
        for( char ch : abb[i]){
            if(freq[ch-'A']==0){
                flag = false;
                break;
            }
        }
    }

    if(flag==true){
        cout<<"YES"<<endl;
    }else{
        cout<<"NO"<<endl;
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