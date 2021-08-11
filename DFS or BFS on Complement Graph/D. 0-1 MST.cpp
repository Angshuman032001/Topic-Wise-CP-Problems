//finding the number of connected components in compliment graph
// https://codeforces.com/contest/1243/problem/D

#include "bits/stdc++.h"

using namespace std;

const int N = 1e5 + 1;

set<int>adj[N];
set<int>unvisited;

int componentSize = 0, components = 0;

void dfs(int node){
	componentSize++;
	unvisited.erase(node);
	std::vector<int>next;
	for(auto  &it : unvisited){
		if(adj[node].find(it) == adj[node].end()) 
			next.push_back(it);
	}
	for(auto &it : next) unvisited.erase(it);
	for(auto &it : next){
		dfs(it);
	}
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

 	int n, m; cin>>n>>m;   
 	for(int i = 1;i<=m;i++){
 		int a, b; cin>>a>>b;
 		adj[a].insert(b);
 		adj[b].insert(a);
 	}
 	for(int i = 1;i<=n;i++) unvisited.insert(i);

 	for(int i = 1;i<=n;i++){
 		if(unvisited.find(i) != unvisited.end()){
 			components++;
 			componentSize = 0;
 			dfs(i);
 		}
 	}

 	cout<<components - 1<<"\n";

}
