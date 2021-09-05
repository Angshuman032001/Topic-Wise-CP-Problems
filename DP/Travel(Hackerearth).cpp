// https://www.hackerearth.com/practice/algorithms/dynamic-programming/introduction-to-dynamic-programming-1/practice-problems/algorithm/travel-2-faeafba1/

#include "bits/stdc++.h"
#define int long long
#define sz(x) (int)x.size()

using namespace std;

void solve(){
    int n, k; cin>>n>>k;
    std::vector<int> v(n + 1);
    vector<std::vector<int>>pos(k + 1);
    for(int i = 1;i<=n;i++){
        cin>>v[i];
        pos[v[i]].push_back(i);
    }

    std::vector<array<int,2>> dp(k + 1);
    for(int i = 2;i<=k;i++){
        int extremeLeftPos = pos[i][0], extremeRightPos = pos[i].back();
        int prevExtremeLeftPos = pos[i - 1][0], prevExtremeRightPos = pos[i - 1].back();
        dp[i][0] = max(dp[i - 1][0] + abs(extremeLeftPos - prevExtremeLeftPos), dp[i - 1][1] + abs(extremeLeftPos - prevExtremeRightPos));
        dp[i][1] = max(dp[i - 1][0] + abs(extremeRightPos - prevExtremeLeftPos), dp[i - 1][1] + abs(extremeRightPos - prevExtremeRightPos));
    }
    cout<<max(dp[k][0], dp[k][1])<<"\n";
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
