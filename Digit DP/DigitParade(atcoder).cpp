#include "bits/stdc++.h"
#define int long long
#define sz(x) (int)x.size()

using namespace std;

const int N = 1e5 + 1, mod = 1e9 + 7;

int add(int a, int b){
    a += b;
    if(a > mod) a -= mod;
    return a;
}

string s; 
int n; 
int dp[N][13];

int solve(int index, int rem){
    if(index == n){
        if(rem == 5) return 1;
        else return 0;
    }

    int &ans = dp[index][rem];
    if(ans != -1) return ans;

    ans = 0;

    if(s[index] != '?') ans = solve(index + 1, (rem * 10 + (s[index] - '0'))%13);
    else{
        for(int digit = 0;digit<=9;digit++){
            ans = add(ans, solve(index + 1, (rem * 10 + digit)%13));
        }
    }
    return ans;
}

int solve(){
    memset(dp, -1, sizeof(dp));
    return solve(0, 0);
}


int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin>>s;
    n = s.length();

    cout<<solve();

}
