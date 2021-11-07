/*

dp[i][j] denotes i am currently at index j and i havent taken ith index in the past
Since we can take any 2 out of first 3 index, we will always have atmost 1 index in the previous part

We calculate the dp table and simultaneously fill up the most optmial path we need to take in the choice table
choice[i][j] denotes the optimal indices which i need to select when i have a suffix from jth index and ith index in the past

*/

#include "bits/stdc++.h"

using namespace std;

const int N = 1005;

pair<int,int>choice[N][N];
int dp[N][N], arr[N], n; 

int solve(int a, int b){
    if(dp[a][b] != -1) return dp[a][b];
    if(b > n){
        choice[a][b] = make_pair(a, a);
        return dp[a][b] = arr[a];
    }
    if(b == n){
        choice[a][b] = make_pair(a, b);
        return dp[a][b] = max(arr[a], arr[b]);
    }
    dp[a][b] = max(arr[a], arr[b]) + solve(b + 1, b + 2);
    choice[a][b] = make_pair(a, b);

    pair<int,int>p = make_pair(a, b + 1);
    int cost = max(arr[a], arr[b + 1]) + solve(b, b + 2);
    if(cost < dp[a][b]){
        dp[a][b] = cost;
        choice[a][b] = p;
    }

    p = make_pair(b, b + 1);
    cost = max(arr[b], arr[b + 1]) + solve(a, b + 2);
    if(cost < dp[a][b]){
        dp[a][b] = cost;
        choice[a][b] = p;
    }
    return dp[a][b];
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    n; cin>>n;
    for(int i = 1;i<=n;i++) cin>>arr[i];
    memset(dp, -1, sizeof(dp));

    int ans = solve(1, 2);

    cout<<ans<<"\n";

    int a = 1, b = 2;
    while(true){
        if(choice[a][b].first == choice[a][b].second)
            cout<<choice[a][b].first<<"\n";
        else cout<<choice[a][b].first<<" "<<choice[a][b].second<<"\n";
        if(b >= n) break;
        if(choice[a][b] == make_pair(a, b)) a = b + 1, b = b + 2;
        else if(choice[a][b] == make_pair(a, b + 1)) a = b, b = b + 2;
        else if(choice[a][b] == make_pair(b, b + 1)) b = b + 2;
    }
    return 0;
}
