// https://atcoder.jp/contests/dp/tasks/dp_p

#include "bits/stdc++.h"
#define int long long

using namespace std;

const int mod = 1e9+7, N = 1e5 + 1;

int add(int a, int b){
    a += b;
    if(a > mod) a -= mod;
    return a;
}

int mul(int a, int b){
    return (a%mod * 1ll * b%mod)%mod;
}

std::vector<int> adj[N];
std::vector<array<int,2>> dp(N);

void dfs(int node, int par){
    dp[node][0] = dp[node][1] = 1;
    for(auto child : adj[node]){
        if(child == par) continue;
        dfs(child, node);
        dp[node][1] = mul(dp[node][1], dp[child][0]);
        dp[node][0] = mul(dp[node][0], add(dp[child][0], dp[child][1]));
    }
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin>>n;    
    for(int i = 1;i<=n - 1;i++){
        int a, b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);

    cout<<add(dp[1][0], dp[1][1]);

}
