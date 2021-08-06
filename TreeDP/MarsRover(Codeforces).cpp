#include "bits/stdc++.h"
#define int long long

using namespace std;

const int N = 1e6 + 1;

std::vector<int> parent(N);
std::vector<int> originalValue(N);
std::vector<int> value(N);
int dp[N][2];
std::vector<int>adj[N];
std::vector<string> operation(N);

void dfs(int node, int par){
	if(operation[node] == "IN"){
		originalValue[node] = value[node];
		return;
	}
	for(auto child : adj[node]){
		dfs(child, node);
	}
	if(operation[node] == "NOT"){
		originalValue[node] = !originalValue[adj[node][0]];
	}
	else{
		if(operation[node] == "AND") originalValue[node] = originalValue[adj[node][0]] & originalValue[adj[node][1]];
		else if(operation[node] == "OR") originalValue[node] = originalValue[adj[node][0]] | originalValue[adj[node][1]];
		else if(operation[node] == "XOR") originalValue[node] = originalValue[adj[node][0]] ^ originalValue[adj[node][1]];
	}
}

int calc(int node, int value){
	if(node == 1) return value;
	if(dp[node][value] != -1) return dp[node][value];
	int &ans = dp[node][value];
	ans = 0;
	int par = parent[node];
	int newParValue = 0;
	if(operation[par] == "NOT") newParValue = !value;
	if(operation[par] == "AND") newParValue = (adj[par][0] == node ? value : originalValue[adj[par][0]]) & (adj[par][1] == node ? value : originalValue[adj[par][1]]);
	if(operation[par] == "OR") newParValue = (adj[par][0] == node ? value : originalValue[adj[par][0]]) | (adj[par][1] == node ? value : originalValue[adj[par][1]]);
	if(operation[par] == "XOR") newParValue = (adj[par][0] == node ? value : originalValue[adj[par][0]]) ^ (adj[par][1] == node ? value : originalValue[adj[par][1]]);
	return ans = calc(par, newParValue);
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

 	int n; cin>>n;
 	for(int i = 1;i<=n;i++){
 		string s; cin>>s;
 		operation[i] = s;
 		if(s == "IN") cin>>value[i];
 		else if(s == "NOT"){
 			int child; cin>>child;
 			adj[i].push_back(child);
 			parent[child] = i;
 		}
 		else{
 			for(int j = 0;j<2;j++){
 				int child; cin>>child;
 				adj[i].push_back(child);
 				parent[child] = i;
 			}
 		}
 	}

 	dfs(1, 0);
 	memset(dp, -1, sizeof(dp));

 	for(int i = 1;i<=n;i++){
 		if(operation[i] == "IN") cout<<calc(i, !originalValue[i]);
 	}

}
