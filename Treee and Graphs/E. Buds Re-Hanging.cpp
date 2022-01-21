//https://codeforces.com/contest/1566/problem/E

#include "bits/stdc++.h"
#define int long long

using namespace std;

enum Type {
    BUD, LEAF, ROOT
};

void solve(){
 
    int n; cin>>n;
    std::vector<std::vector<int>> adj(n + 1);
    std::vector<Type> typeOfNode(n + 1);
    for(int i = 1;i<=n - 1;i++){
        int a, b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    typeOfNode[1] = ROOT;

    function<void(int,int)>dfs = [&](int node, int par)->void{
        bool isLeaf = true;
        for(auto &child : adj[node]){
            if(child == par) continue;
            dfs(child, node);
            if(typeOfNode[child] == LEAF) isLeaf = false;
        }
        if(node != 1){
            if(isLeaf) typeOfNode[node] = LEAF;
            else typeOfNode[node] = BUD;
        }
    };

    dfs(1, 0);

    int totalBuds = 0;
    bool rootHasLeaf = false;
    for(auto &child : adj[1]) rootHasLeaf = rootHasLeaf || typeOfNode[child] == LEAF;

    for(int i = 2;i<=n;i++) totalBuds += (typeOfNode[i] == BUD);

    cout<<n - 2 * totalBuds - rootHasLeaf<<"\n";

}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; 
    cin>>t;
    while(t--){
        solve();
    }      

}
