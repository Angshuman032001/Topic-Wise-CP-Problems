/*

dp[mask][prevIndex] denotes the current set of dishes i have taken is mask and the previous taken dish was prevIndex
Then i iterate over the remaining dishes and update the dp values accordingly

*/

#include "bits/stdc++.h"
#define int long long

using namespace std;

const int N = 19;

int dp[(1ll << N)][N], arr[N];
int satisfactionIncrease[N][N];
int n, m, k;

int solve(int dishMask, int prevDishIndex){
    if(__builtin_popcountll(dishMask) == m){
        return 0;
    }
    int &ans = dp[dishMask][prevDishIndex];
    if(ans != -1) return ans;
    for(int i = 1;i<=n;i++){
        if(dishMask & (1ll << i)) continue;
        int tempMask = dishMask;
        tempMask ^= (1ll << i);
        int value = arr[i] + satisfactionIncrease[prevDishIndex][i] + solve(tempMask, i);
        ans = max(ans, value);
     }
    return ans;
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin>>n>>m>>k;
    for(int i = 1;i<=n;i++){
        cin>>arr[i];
    }

    memset(satisfactionIncrease, 0, sizeof(satisfactionIncrease));
    memset(dp, -1, sizeof(dp));

    for(int i = 0;i<k;i++){
        int x, y, c; cin>>x>>y>>c;
        satisfactionIncrease[x][y] = c;
    }

    int ans = solve(0, 0);

    cout<<ans<<"\n";

}
