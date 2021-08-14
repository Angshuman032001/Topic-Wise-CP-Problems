#include "bits/stdc++.h"
#define int long long
#define sz(x) (int)x.size()

using namespace std;

const int N = 1e5 + 1;

std::vector<pair<int,int>> adj[N];
std::vector<array<int,2>> dp(N);

/*

dp[node][0] -> minimum cost of travel if he starts and ends at node
dp[node][1] -> minimum cost of travel if he starts and ends at node's subtree

*/

void dfs(int node, int par){
    if(sz(adj[node]) == 1 and node != 1){
        dp[node][0] = dp[node][1] = 0;
        return;
    }

    for(auto child : adj[node]){
        int childNode = child.first;
        if(childNode == par) continue;
        dfs(childNode, node);
    }

    for(auto child : adj[node]){
        int childNode = child.first, weight = child.second;
        if(childNode == par) continue;
        dp[node][0] += (dp[childNode][0] + 2 * weight);
    }

    int sum = dp[node][0];
    dp[node][1] = sum;
    for(auto child : adj[node]){
        int childNode = child.first, weight = child.second;
        if(childNode == par) continue;
        dp[node][1] = min(dp[node][1], sum + dp[childNode][1] - dp[childNode][0] - weight);
    }
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin>>n;
    for(int i = 1;i<=n - 1;i++){
        int a, b, w; cin>>a>>b>>w;
        adj[a].push_back(make_pair(b, w));
        adj[b].push_back(make_pair(a, w));
    }

    dfs(1, 0);

    cout<<min(dp[1][0], dp[1][1]);

}
