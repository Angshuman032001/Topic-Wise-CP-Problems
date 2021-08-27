#include "bits/stdc++.h"
#define int long long

using namespace std;

const int N = 3001, inf = 1e18;

int dp[N][N], n;
std::vector<pair<int,int>> v;

int solve(int index, int lastStick){
    if(index == n){
        return 0;
    }
    int &ans = dp[index][lastStick];
    if(ans != -1) return ans;
    ans = inf;
    /*if i place a stick here*/
    ans = min(ans, v[index].second + solve(index + 1, index));
    /*if i dont place a stick here*/
    ans = min(ans, v[index].first - v[lastStick].first + solve(index + 1, lastStick));
    return ans;
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin>>n;
    v.resize(n);
    for(auto &x : v) cin>>x.first>>x.second;

    sort(v.begin(), v.end());

    memset(dp, -1, sizeof(dp));
    
    int ans = v[0].second + solve(1, 0);

    cout<<ans;

}
