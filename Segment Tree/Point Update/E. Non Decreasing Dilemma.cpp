// https://codeforces.com/contest/1567/problem/E

// Neal's stream : https://www.youtube.com/watch?v=wyzfPsvR7Us

#include "bits/stdc++.h"
#define int long long

using namespace std;

const int N = 2e5 + 1;

int arr[N];

class node
{
public:
    int first, last, count, length, prefixCount, suffixCount;
    node(): first(-1), last(-1), length(0), count(0), prefixCount(0), suffixCount(0) {}
};

node ID;

template <class T> struct SegTree {
    int n; vector <T> tree;
 
    SegTree(int _n) { n = _n; tree.assign(4 * n, ID); }

    T merge(T curr, T other){
        T res = curr;
        if(res.last <= other.first) res.count += curr.suffixCount * other.prefixCount;
        if(res.prefixCount == res.length && res.last <= other.first) res.prefixCount += other.prefixCount;
        if(other.suffixCount == other.length && res.last <= other.first) res.suffixCount += other.length;
        else res.suffixCount = other.suffixCount;
        res.count += other.count;
        res.length += other.length;
        res.last = other.last;
        return res;
    }

    T makeNode(int value){
        T res;
        res.first = res.last = value;
        res.count = res.length = res.prefixCount = res.suffixCount = 1;
        return res;
    }

    void build(int i, int l, int r){
        if(l == r){
            tree[i] = makeNode(arr[l]);
            return;
        }
        int mid = (l + r)/2;
        build(2 * i, l, mid);
        build(2 * i + 1, mid + 1, r);
        tree[i] = merge(tree[2*i],tree[2*i+1]);
    }

    void _update(int i, int l, int r, int idx, int val) {
        if(l == r) {
            tree[i] = makeNode(val);
            return;
        }
        int mid = (l + r) / 2;
        if(mid < idx) _update(2 * i + 1, mid + 1, r, idx, val);
        else _update(2 * i, l, mid, idx, val);
        tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }

    T _query(int i, int l, int r, int rx, int ry) {
        if(r < rx || ry < l) return ID;
        if(rx <= l && r <= ry) return tree[i];
        int mid = (l + r) / 2;
        return merge(_query(2 * i, l, mid, rx, ry), _query(2 * i + 1, mid + 1, r, rx, ry));
    }

    T query(int l, int r) { return _query(1, 1, n, l, r); }

    void update(int idx, int val) { _update(1, 1, n, idx, val); }
};


int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, q; cin>>n>>q;

    for(int i = 1;i<=n;i++) cin>>arr[i];

    SegTree<node>seg(n);
    seg.build(1, 1, n);

    while(q--){
        int type; cin>>type;
        if(type == 1){
            int x, y; cin>>x>>y;
            seg.update(x, y);
        }
        else{
            int l, r; cin>>l>>r;
            cout<<seg.query(l, r).count<<"\n";
        }
    }   

    return 0;

}
