#include "bits/stdc++.h"
#define int long long
#define sz(x) (int)x.size()

using namespace std;

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

 	int n, m; cin>>n>>m;
 	std::vector<std::vector<bool>> graph(n + 1, std::vector<bool>(n + 1));
 	for(int i = 1;i<=m;i++){
 		int a, b; cin>>a>>b;
 		--a, --b;
 		graph[a][b] = true;
 		graph[b][a] = true;
 	}

 	std::vector<bool> goodMask(1<<n);
 	std::vector<int>dp(1<<n, INT_MAX);

 	for(int mask = 1;mask<(1<<n);mask++){
 		std::vector<int> vertices;
 		for(int i = 0;i<n;i++){
 			if(mask & (1<<i)) vertices.push_back(i);
 		}
 		bool isGoodMask = true;
 		for(int i = 0;i<sz(vertices);i++){
 			for(int j = i + 1;j<sz(vertices);j++){
 				if(!graph[vertices[i]][vertices[j]]){
 					isGoodMask = false;
 					break;
 				}
 			}
 		}
 		goodMask[mask] = isGoodMask;
 	}

 	dp[0] = 0;
 	for(int mask = 1;mask<(1<<n);mask++){
 		if(goodMask[mask]) dp[mask] = 1;
 		for(int submask = mask;submask;submask = (submask - 1) & mask){
 			dp[mask] = min(dp[mask], dp[submask] + dp[mask ^ submask]);
 		}
 	}

 	cout<<dp[(1<<n) - 1];
}
