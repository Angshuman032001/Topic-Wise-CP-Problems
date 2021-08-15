#include "bits/stdc++.h"
#define int long long

using namespace std;

const int N = 3001;

int dp[N][N], a[N], n;

int solve(int left, int right){
    if(left > right) return 0;
    if(left == right) return dp[left][right] = a[left];
    int &ans = dp[left][right];
    if(ans != -1) return ans;
    ans = max(a[left] - solve(left + 1, right), a[right] - solve(left, right - 1));
    return ans;
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin>>n;
    for(int i = 1;i<=n;i++) cin>>a[i];
    memset(dp, -1, sizeof(dp));

    cout<<solve(1, n);

}
