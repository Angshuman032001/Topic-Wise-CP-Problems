// https://www.codechef.com/START12B/problems/TREEMIN


#include "bits/stdc++.h"
#define int long long
#define sz(x) (int)x.size()

using namespace std;

const int inf = 1e18;

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

 	int t; cin>>t;
 	while(t--){
 		int n, k; cin>>n>>k;
 		std::vector<int> values(n + 1), dp(n + 1);
 		std::vector<std::vector<int>> adj(n + 1);
 		for(int i = 1;i<=n;i++){
 			cin>>values[i];
 		}
 		for(int i = 1;i<=n - 1;i++){
 			int a, b; cin>>a>>b;
 			adj[a].push_back(b);
 			adj[b].push_back(a);
 		}

 		function<void(int,int,int)>dfs = [&](int node, int par, int lvl)->void{
 			for(auto child : adj[node]){
 				if(child == par) continue;
 				dfs(child, node, lvl + 1);
 			}
 			if(sz(adj[node]) == 1 && node != 1){
 				dp[node] = values[node];
 				return;
 			}
 			bool first = true;
 			for(auto child : adj[node]){
 				if(child == par) continue;
 				if(first){
 					dp[node] = dp[child] + values[node];
 					first = false;
 				}
 				dp[node] = (lvl%2 == 1 ? max(dp[node], dp[child] + values[node]) : min(dp[node], dp[child] + values[node]));
 			}
 		};

 		dfs(1, 0, 0);

 		cout<<dp[1]<<"\n";

 	}
 	return 0;
}
