// https://atcoder.jp/contests/abc220/tasks/abc220_d

#include "bits/stdc++.h"

using namespace std;

const int mod = 998244353;

int add(int a, int b){
    return (a%mod + b%mod)%mod;
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin>>n;
    int arr[n + 1];
    for(int i = 1;i<=n;i++) cin>>arr[i];

    int dp[n + 1][10];
    
    memset(dp, 0, sizeof(dp));

    dp[1][arr[1]] = 1;

    for(int i = 2;i<=n;i++){
        for(int j = 0;j<10;j++){
            dp[i][(j + arr[i])%10] = add(dp[i][(j + arr[i])%10], dp[i - 1][j]);
            dp[i][(j * arr[i])%10] = add(dp[i][(j * arr[i])%10], dp[i - 1][j]);
        }
    }   

    for(int i = 0;i<=9;i++) cout<<dp[n][i]<<"\n";

}
