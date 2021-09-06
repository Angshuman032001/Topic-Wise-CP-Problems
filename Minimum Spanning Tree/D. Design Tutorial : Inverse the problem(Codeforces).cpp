// https://codeforces.com/contest/472/problem/D

#include "bits/stdc++.h"
#define int long long

using namespace std;

const int MAXN = 20, N = 2001;

vector<pair<int,int>>adj[N];
bool visited[N];
int parent[N], level[N], LCA[N][MAXN], weight[N];
 
void dfs(int node, int par, int lvl, int wt = 0){
    level[node] = lvl;
    LCA[node][0] = par;
    parent[node] = par;
    weight[node] = wt;
    for(auto child : adj[node]){
        if(child.first != par) 
            dfs(child.first, node, lvl + 1, wt + child.second);
    }
}
 
void init(int n){
    for(int j = 1;j<MAXN;j++){
        for(int i = 1;i<=n;i++){
            if(LCA[i][j-1] != -1){
                LCA[i][j] = LCA[LCA[i][j-1]][j-1];
            }
        }
    }
}
 
int getLCA(int a , int b){
    if(level[a] > level[b])
    swap(a , b);
    int d = level[b] - level[a];
    int f = 0;
    while(d){
        if(d & 1)
        b = LCA[b][f];
        d >>= 1;
        f++;
    }
    if(a == b)
    return a;
    for(int j=MAXN-1;j>=0;j--)
        if(LCA[a][j] != -1 && (LCA[a][j] != LCA[b][j]))
        a = LCA[a][j] , b = LCA[b][j];
    
    return LCA[a][0];
}

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

struct edge{
    int from, to, weight;
    edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
    bool operator<(const edge &b){
        return weight < b.weight;
    }
};

int getDistance(int u, int v){
    int lca = getLCA(u, v);
    int dist = weight[u] + weight[v] - 2 * weight[lca];
    return dist;
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin>>n;  
    std::vector<edge> v;
    std::vector<std::vector<int>> grid(n + 1, std::vector<int>(n + 1));
    bool ok = true;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=n;j++){
            int weight; cin>>weight;
            grid[i][j] = weight;
            if(i == j && weight != 0) ok = false;
            if(i != j && weight == 0) ok = false;
            if(j > i) v.push_back(edge(i, j, weight));
        }
    }

    sort(v.begin(), v.end());
    UF dsu;
    dsu.init(n + 1);

    for(auto &e : v){
        if(dsu.sameSet(e.from, e.to)) continue;
        dsu.join(e.from, e.to);
        adj[e.from].push_back(make_pair(e.to, e.weight));
        adj[e.to].push_back(make_pair(e.from, e.weight));
    }

    memset(LCA, -1, sizeof(LCA));
    dfs(1, 1, 0);
    init(n);

    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=n;j++){
            if(i == j) continue;
            if(grid[i][j] != getDistance(i, j)){
                ok = false;
            }
        }
    }

    cout<<(ok ? "YES\n" : "NO\n");

}
