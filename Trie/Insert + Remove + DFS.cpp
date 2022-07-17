// https://www.hackerearth.com/practice/data-structures/advanced-data-structures/trie-keyword-tree/practice-problems/algorithm/prefix-queries-3-2c111491/
#include "bits/stdc++.h"
#define int long long

using namespace std;

struct TrieNode {
    TrieNode *bit[2];
    int cnt;
    TrieNode() {
        bit[0] = bit[1] = NULL;
        cnt = 0;
    }
};

void add(int x, TrieNode *root) {
    TrieNode* cur = root;
    for(int i = 61; i >= 0; i --) {
        int b = ((x >> i) & 1ll);
        if(!cur->bit[b]) cur->bit[b] = new TrieNode();
        cur->cnt++;
        cur = cur->bit[b];
    }
    cur->cnt ++;
}

void remove(int x, TrieNode *root) {
    TrieNode *cur = root;
    for(int i = 61; i >= 0; i--) {
        int b = (x >> i) & 1ll;
        TrieNode *temp = cur->bit[b];
        if(cur->bit[b]->cnt - 1 == 0) cur->bit[b] = NULL;
        cur->cnt --;
        if(cur && cur->cnt == 0) free(cur);
        cur = temp;
    }
}

int query(int x, TrieNode *root) {
    TrieNode *cur = root;
    int ans = 0;
    for(int i = 61; i >= 0; i--) {
        int b = (x >> i) & 1;
        if(cur->bit[b] != NULL && cur->bit[b]->cnt > 0) {
            cur = cur->bit[b];
            ans++;
        }
        else {
            break;
        }
    }
    return ans;
}


void solve(){
 
    int n; cin>>n;
    std::vector<int> nodeValue(n + 1);
    std::vector<std::vector<int>> adj(n + 1);
    
    TrieNode *root = new TrieNode();

    for(int i = 1;i<=n;i++) cin>>nodeValue[i];

    for(int i = 1;i<=n - 1;i++){
        int u, v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int q; cin>>q;

    std::vector<std::vector<pair<int,int>>> nodeQuery(n + 1);
    for(int i = 1;i<=q;i++){
        int value, node; cin>>value>>node;
        nodeQuery[node].push_back({value, i});
    }

    std::vector<int> ans(q + 1);

    function<void(int,int)>dfs = [&](int node, int par)->void{
        add(nodeValue[node], root);
        for(auto &[value, index] : nodeQuery[node]){
            ans[index] = query(value, root);
        }
        for(auto &child : adj[node]){
            if(child != par) dfs(child, node);
        }
        remove(nodeValue[node], root);
    };

    dfs(1, 0);

    for(int i = 1;i<=q;i++) cout<<ans[i]<<" ";
    cout<<"\n";
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; 
    cin>>t;

    while(t--){
        solve();
    }      

}
