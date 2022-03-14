//https://codeforces.com/contest/1447/problem/D

#include "bits/stdc++.h"

using namespace std;

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m; cin>>n>>m;

    string a, b; cin>>a>>b;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int> (m + 1, 0));
	
    int ans = 0;

    for(int i = n;i>=1;i--){
        for(int j = m;j>=1;j--){
            if(a[i - 1] == b[j - 1]){
                dp[i][j] = 2;
                if(i + 1 <= n && j + 1 <= m) dp[i][j] = max(dp[i][j], 2 + dp[i + 1][j + 1]);
            }
            else{
                dp[i][j] = -2;
                if(i + 1 <= n && j + 1 <= m) dp[i][j] = max(dp[i][j], -2 + dp[i + 1][j + 1]);
            }
            if(i + 1 <= n) dp[i][j] = max(dp[i][j], -1 + dp[i + 1][j]);
            if(j + 1 <= m) dp[i][j] = max(dp[i][j], -1 + dp[i][j + 1]);
            ans = max(ans, dp[i][j]);
        }
    }

    cout<<ans;

}
