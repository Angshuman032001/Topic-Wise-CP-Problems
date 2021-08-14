//for each edges that is not a part of MST, check if the heaviest edge in the path from [from, to] is equal to edge weight
//https://codeforces.com/contest/1108/problem/F

#include "bits/stdc++.h"
#define int long long

using namespace std;

struct edge{
    int from, to, weight, index;
    edge(int from, int to, int weight, int index){
        this->from = from;
        this->to = to;
        this->weight = weight;
        this->index = index;
    }
    bool operator<(const edge &e){
        return weight < e.weight;
    }
};

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


const int N = 2e5 + 1, MAXN = 20;
std::vector<pair<int,int>> adj[N];
int LCA[N][MAXN], maxWeight[N][MAXN], level[N];

void dfs(int node, int par, int lvl, int wt){
    level[node] = lvl;  
    LCA[node][0] = par;
    maxWeight[node][0] = wt;
    for(auto child : adj[node]){
        if(child.first != par) dfs(child.first, node, lvl + 1, child.second);
    }
}

void init(int n){
    for(int j = 1;j<MAXN;j++){
        for(int i = 1;i<=n;i++){
            if(LCA[i][j-1] != -1){
                LCA[i][j] = LCA[LCA[i][j-1]][j-1];
                maxWeight[i][j] = max(maxWeight[i][j - 1], maxWeight[LCA[i][j - 1]][j - 1]);
            }
        }
    }
}

int getHeaviestEdge(int a, int b){
    int heaviestEdge = 0;
    if(level[a] > level[b])
    swap(a , b);
    for(int i = 19;i>=0;i--){
        if((level[b] - level[a]) >= (1ll<<i)){
            heaviestEdge = max(heaviestEdge, maxWeight[b][i]);
            b = LCA[b][i];
        }
    }

    if(a == b){
        return heaviestEdge;
    }

    int k = ceil((double)log2(level[a]));
    while(k >= 0){
        if(LCA[a][k] != LCA[b][k]){
            heaviestEdge = max(heaviestEdge, maxWeight[a][k]);
            heaviestEdge = max(heaviestEdge, maxWeight[b][k]);
            a = LCA[a][k], b = LCA[b][k];
        }
        k--;
    }
    heaviestEdge = max(heaviestEdge, maxWeight[a][0]);
    heaviestEdge = max(heaviestEdge, maxWeight[b][0]);
    return heaviestEdge;
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m; cin>>n>>m;   
    std::vector<edge> v, givenEdges;
    for(int i = 1;i<=m;i++){
        int a, b, w; cin>>a>>b>>w;
        v.push_back(edge(a, b, w, i));
        givenEdges.push_back(edge(a, b, w, i));
    }

    sort(v.begin(), v.end());

    UF dsu;
    dsu.init(n + 1);

    std::vector<bool> MSTIndices(m + 1);

    int cost = 0;

    for(auto x : v){
        auto [from, to, weight, index] = x;
        if(dsu.sameSet(from, to)) continue;
        MSTIndices[index] = true;
        adj[from].push_back(make_pair(to, weight));
        adj[to].push_back(make_pair(from, weight));
        cost += weight;
        dsu.join(from, to);
    }

    memset(LCA, -1, sizeof(LCA));
    dfs(1, 0, 0, 0);
    init(n);

    int moves = 0;
    for(int i = 1;i<=m;i++){
        if(MSTIndices[i]) continue;
        else{
            int heaviestEdge = getHeaviestEdge(givenEdges[i - 1].from, givenEdges[i - 1].to);
         	int givenWeight = givenEdges[i - 1].weight;
         	if(heaviestEdge == givenWeight) moves++;
        }
    }

    cout<<moves;

    return 0;

}
