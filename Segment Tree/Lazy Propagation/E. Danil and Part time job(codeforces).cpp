#include "bits/stdc++.h"
#define int long long

using namespace std;

const int N = 2e5 + 1;
std::vector<int>adj[N], tin(N, 0), tout(N, 0), state(N, 0), ETT(3 * N, 0);

int timer = 1;

void flattenTree(int node, int par){
	tin[node] = timer;
	ETT[timer] = node;
	timer++;
	for(auto child : adj[node]){
		if(child != par) flattenTree(child, node);
	}
	tout[node] = timer;
	ETT[timer] = node;
	timer++;
}

int arr[N];

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

    void propagate(int i, int l, int r){
        //cant propagte from leaf node
        if(l != r){
        	int mid = (l + r)/2;
        	operation(tree[2*i], lazy[i], mid - l + 1);
        	operation(tree[2*i + 1], lazy[i], r - mid);
        	lazy[2 * i] ^= lazy[i];
        	lazy[2 * i + 1] ^= lazy[i];
            lazy[i]=NOP;
        }
    }

    void _build(int i, int l, int r){
    	if(l == r){
    		tree[i] = state[ETT[l]];
    		return;
    	}
    	int mid = (l + r)/2;
    	_build(2 * i, l, mid);
    	_build(2 * i + 1, mid + 1, r);
    	tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    	return;
    }

    void _update(int i, int l, int r, int rx, int ry, int val){
        propagate(i,l,r);
        if(rx<=l and r<=ry){
            operation(tree[i], val, r - l + 1);
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
    void build(){ _build(1, 1, n); }

};

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

 	int n; cin>>n;
 	for(int i = 2;i<=n;i++){
 		int par; cin>>par;
 		adj[par].push_back(i);
 		adj[i].push_back(par);
 	}

 	for(int i = 1;i<=n;i++) cin>>state[i];
 	timer = 1;
 	flattenTree(1, 0);

 	SegmentTreeLazy<int>seg;
 	seg.init(timer - 1);
 	seg.build();

 	int q; cin>>q;
 	while(q--){
 		string type; cin>>type;
 		int node; cin>>node;
 		if(type == "get") cout<<seg.query(tin[node], tout[node])/2<<"\n";
 		else seg.update(tin[node], tout[node], 1);
 	}
 	return 0;
}
