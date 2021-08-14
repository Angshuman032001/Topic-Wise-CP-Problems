//https://codeforces.com/contest/1027/submission/125781178

#include "bits/stdc++.h"

using namespace std;

const int N = 2e5 + 1;
std::vector<int> adj[N];
std::vector<int> parent(N, -1);
std::vector<bool> visited(N, false);
std::vector<int> color(N, 0);
int cycleStart, cycleEnd;

struct UF {
    int N;
    std::vector<int> e;
    void init(int n){
        e.assign(n,-1);
    }
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};

bool dfs(int node){
	color[node] = 1;
	for(auto child : adj[node]){
		if(color[child] == 0){
			parent[child] = node;
			if(dfs(child)) return true;
		}
		else if(color[child] == 1){
			cycleEnd = node;
			cycleStart = child;
			return true;
		}
	}
	color[node] = 2;
	return false;
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

 	int n; cin>>n;
 	std::vector<int> cost(n + 1), a(n + 1);

 	UF dsu;
 	dsu.init(n + 1);
 	
 	for(int i = 1;i<=n;i++) cin>>cost[i];
 	for(int i = 1;i<=n;i++) cin>>a[i];

 	for(int i = 1;i<=n;i++){
 		int curr = i;
 		while(!visited[curr]){
 			int node = a[curr];
 			adj[curr].push_back(node);
 			dsu.join(curr, node);
 			visited[curr] = true;
 			curr = node;
 		}
 	}

 	for(int i = 1;i<=n;i++){
 		visited[i] = false;
 	}

 	int ans = 0;
 	for(int i = 1;i<=n;i++){
 		if(color[i] != 0 || visited[dsu.find(i)]) continue;
 		if(dfs(i)){
 			visited[dsu.find(i)] = true;
 			int mnValue = INT_MAX;
 			std::vector<int> cycle;
 			for(int j = cycleEnd; j != cycleStart; j = parent[j]){
 				mnValue = min(mnValue, cost[j]);
 				visited[j] = true;
 			}
 			mnValue = min(mnValue, cost[cycleStart]);
 			visited[cycleStart] = true;
 			ans += mnValue;
 		}
 	}

 	cout<<ans;

}
