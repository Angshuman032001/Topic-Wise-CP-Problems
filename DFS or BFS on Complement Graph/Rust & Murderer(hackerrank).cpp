#include "bits/stdc++.h"

using namespace std;

const int N = 2e5 + 1;

set<int>adj[N];
set<int>unvisited;
std::vector<int> dist(N);

int componentSize = 0, components = 0;

void dfs(int node, int level = 0){
	dist[node] = level;
	unvisited.erase(node);
	std::vector<int>next;
	for(auto  &it : unvisited){
		if(adj[node].find(it) == adj[node].end()) 
			next.push_back(it);
	}
	for(auto &it : next) unvisited.erase(it);
	for(auto &it : next){
		dfs(it, level + 1);
	}
}

void init(int n){
	for(int i = 0;i<=n;i++) adj[i].clear(), dist[i] = 0;
	unvisited.clear();
}

void solve(){
	int n, m; cin>>n>>m;   
	init(n);
	for(int i = 1;i<=m;i++){
 		int a, b; cin>>a>>b;
 		adj[a].insert(b);
 		adj[b].insert(a);
 	}
 	for(int i = 1;i<=n;i++) unvisited.insert(i);

 	int start; cin>>start;

 	dfs(start);

 	for(int i = 1;i<=n;i++) if(i != start) cout<<dist[i]<<" ";
 	cout<<"\n";
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

 	int t; cin>>t;
 	while(t--){
 		solve();
 	}

}
