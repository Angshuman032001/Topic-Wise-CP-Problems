// https://www.codechef.com/problems/SHADES

#include "bits/stdc++.h"
#define int long long

using namespace std;

const int N = 2e5+10;

std::vector<int> adj[N];
int tin[N], tout[N], ETT[2*N], level[N], arr[N];
int timer = 1;

void dfs(int node , int par, int lvl = 0){
    level[node] = lvl;
    tin[node] = timer;
    ETT[timer] = node;
    timer++;

    for(int child : adj[node]){
        if(child != par)
            dfs(child , node, lvl + 1);
    }
    
    tout[node] = timer;
    ETT[timer] = node;
    timer++;
}

template<class T>struct SegmentTreeLazy{
    int n, N;
    std::vector<T>tree,lazy;

    /*unit is for query and NOP is for updates*/

    const int NOP = 0; //change according to problem
    const int unit = 0;//change according to problem
    
    void init(int _n){
        n = _n;
        N = 4*_n;
        tree.resize(N);
        lazy.resize(N);
    }

    //change operation carefully
    void operation(int &a, int b, int len){
        if(b != NOP) a = len - a;
    }

    //change merge carefully
    int merge(int a, int b){
        return a + b;
    }

    void _build(int i, int l, int r){
        if(l == r){
            tree[i] = arr[ETT[l]];
            return;
        }
        int mid = (l + r)/2;
        _build(2 * i, l, mid);
        _build(2 * i + 1, mid + 1, r);
        tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
        return;
    }

    void propagate(int i, int l, int r){
        //cant propagte from leaf node
        if(l != r){
            int mid = (l + r)/2;
            operation(tree[2*i],lazy[i], mid - l + 1);
            operation(tree[2*i+1],lazy[i], r - mid);
            lazy[2 * i] ^= lazy[i];
            lazy[2 * i + 1] ^= lazy[i];
            lazy[i]=NOP;
        }
    }

    void _update(int i, int l, int r, int rx, int ry, int val){
        propagate(i,l,r);
        if(rx<=l and r<=ry){
            operation(tree[i],val, r - l + 1);
            lazy[i] = 1;
            return;
        }
        else if(r<rx or l>ry) return;
        else{
            int mid = l + (r - l)/2;
            _update(2*i, l, mid, rx, ry, val);
            _update(2*i+1, mid+1, r, rx, ry, val);
            tree[i] = merge(tree[2*i],tree[2*i+1]);
        }
    }

    T _query(int i, int l, int r, int rx, int ry){
        propagate(i,l,r);
        if(rx<=l and r<=ry) return tree[i];
        else if(r<rx || l>ry) return unit;//change unit according to problem
        else{
            int m = l+(r-l)/2;
            return merge(_query(2*i, l, m, rx, ry), _query(2*i+1, m+1, r, rx, ry));
        }
    }

    T query(int l, int r){ return _query(1, 1, n, l, r); }
    void update(int l, int r, T val){ _update(1, 1, n, l, r, val); }
    void build(){ _build(1, 1, n);  }
};

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin>>n;
    for(int i = 1;i<=n - 1;i++){
        int a, b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }   

    for(int i = 1;i<=n;i++) arr[i] = 1;

    dfs(1, 0);

    SegmentTreeLazy<int>seg;
    seg.init(timer - 1);
    seg.build();
    
    int q; cin>>q;
    while(q--){
        int type; cin>>type;
        if(type == 1){
            int u, v; cin>>u>>v;
            if(level[u] > level[v]) swap(u, v);
            int blackInSubtreeOfU = seg.query(tin[u], tout[u])/2;
            int blackInSubtreeOfV = seg.query(tin[v], tout[v])/2;
            int totalBlack = seg.query(tin[1], tout[1])/2;
            totalBlack -= blackInSubtreeOfU;
            blackInSubtreeOfU -= blackInSubtreeOfV;
            blackInSubtreeOfU += totalBlack;
            cout<<blackInSubtreeOfU * blackInSubtreeOfV<<"\n";
        }
        else{
            int u; cin>>u;
            seg.update(tin[u], tout[u], 1);
        }
    }

}
