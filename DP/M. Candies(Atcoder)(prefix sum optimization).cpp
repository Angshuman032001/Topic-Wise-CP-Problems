// https://atcoder.jp/contests/dp/tasks/dp_m

#include "bits/stdc++.h"
#define int long long

using namespace std;

const int mod = 1e9 + 7;

int add(int a, int b){
    a += b;
    if(a > mod) a -= mod;
    return a;
}

int sub(int a, int b){
    a -= b;
    if(a < 0) a += mod;
    return a;
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, k; cin>>n>>k;
    std::vector<std::vector<int>>dp(2, std::vector<int>(k + 1));
    std::vector<int> v(n + 1), pref(k + 1);
    for(int i = 1;i<=n;i++) cin>>v[i];

    dp[0][0] = 1;

    for(int i = 1;i<=n;i++){
        pref[0] = 1;
        for(int j = 1;j<=k;j++){
            pref[j] = add(pref[j - 1], dp[(i - 1)%2][j]);
        }
        dp[i%2][0] = 1;
        for(int j = 1;j<=k;j++){
            if(j - v[i] - 1 <= -1){
                dp[i%2][j] = pref[j];
            }
            else{
                int index = max(0ll, j - v[i] - 1);
                dp[i%2][j] = sub(pref[j], pref[index]);
            }
        }
    }

    cout<<dp[n%2][k];

}
