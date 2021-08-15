#include "bits/stdc++.h"
#define int long long

using namespace std;

const int inf = 1e18;

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin>>n;
    std::vector<int> v(n), pref(n);
    for(int i = 0;i<n;i++){
        cin>>v[i];
        pref[i] = v[i] + (i - 1 >= 0 ? pref[i - 1] : 0);
    }
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
    for(int gap = 0;gap<n;gap++){
        for(int i = 0, j = gap;j<n;i++, j++){
            if(i == j) dp[i][j] = 0;
            else if(j == i + 1) dp[i][j] = v[i] + v[j];
            else{
                dp[i][j] = inf;
                for(int k = i;k<=j - 1;k++){
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + pref[j] - (i == 0 ? 0 : pref[i - 1]));
                }
            }
        }
    }

    cout<<dp[0][n - 1];

}
