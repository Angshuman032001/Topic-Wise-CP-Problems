// https://codeforces.com/contest/474/problem/E
#include "bits/stdc++.h"
#define int long long

using namespace std;

const int inf = 1e18;

struct node{
    int dpValue = -inf, index = -1, actualIndex = -1;
};

node ID;

template <class T> struct SegTree {
    int n; vector <T> tree;
    T merge(T a, T b) { 
        if(a.dpValue == b.dpValue){
            if(a.actualIndex < b.actualIndex) return a;
            else return b;
        }
        else if(a.dpValue > b.dpValue) return a;
        else return b;
    } 
    SegTree(int _n) { n = _n; tree.assign(4 * n, ID); }

    node makeNode(int value, int index, int actualIndex){
        node res;
        res.dpValue = value;
        res.index = index;
        res.actualIndex = actualIndex;
        return res;
    }

    void _update(int i, int l, int r, int idx, int val, int actualIndex) {
        if(l == r) {
            tree[i] = makeNode(val, l, actualIndex);
            return;
        }
        int mid = (l + r) / 2;
        if(mid < idx) _update(2 * i + 1, mid + 1, r, idx, val, actualIndex);
        else _update(2 * i, l, mid, idx, val, actualIndex);
        tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }

    T _query(int i, int l, int r, int rx, int ry) {
        if(r < rx || ry < l) return ID;
        if(rx <= l && r <= ry) return tree[i];
        int mid = (l + r) / 2;
        return merge(_query(2 * i, l, mid, rx, ry), _query(2 * i + 1, mid + 1, r, rx, ry));
    }

    T query(int l, int r) { return _query(1, 1, n, l, r); }

    void update(int idx, int val, int actualIndex) { _update(1, 1, n, idx, val, actualIndex); }
};

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, d; cin>>n>>d;
    std::vector<int> v(n), dp(n), parent(n, -1);
    map<int,int>m;
    for(auto &x : v){
        cin>>x;
        m[x] = 0;
        m[x - d] = 0;
        m[x + d] = 0;
    }

    int id = 1;
    for(auto &it : m) it.second = id++;
    SegTree<node>seg(id);

    dp[n - 1] = 1;
    seg.update(m[v[n - 1]], dp[n - 1], n - 1);

    int startIndex = -1, maxDpValue = -1;

    for(int i = n - 2;i>=0;i--){
        int upperValue = m[v[i] + d], lowerValue = m[v[i] - d];
        node lowerMax = seg.query(1, lowerValue), upperMax = seg.query(upperValue, id - 1);
        int value = max(max(upperMax.dpValue, lowerMax.dpValue), 0ll);
        if(upperMax.dpValue >= lowerMax.dpValue){
            parent[i] = upperMax.actualIndex;
        }
        else{
            parent[i] = lowerMax.actualIndex;
        }
        dp[i] = value + 1;
        seg.update(m[v[i]], dp[i], i);
        if(maxDpValue < dp[i]) {
            maxDpValue = dp[i];
            startIndex = i;
        }
    }

    cout<<maxDpValue<<"\n";
    while(startIndex != -1){
        cout<<startIndex + 1<<" ";
        startIndex = parent[startIndex];
    }

}
