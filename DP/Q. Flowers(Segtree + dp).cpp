//https://atcoder.jp/contests/dp/tasks/dp_q

#include "bits/stdc++.h"
#define int long long

using namespace std;

const int N = 2e5 + 1;

template <class T> struct SegTree {
    int n; vector <T> tree;
    const T unit = 0; //default value

    T merge(T a, T b) { return max(a, b); } //any associative function

    SegTree(int _n) { n = _n; tree.assign(4 * n, unit); }

    void _update(int i, int l, int r, int idx, T val) {
        if(l == r) {
            tree[i] = val;
            return;
        }
        int mid = (l + r) / 2;
        if(mid < idx) _update(2 * i + 1, mid + 1, r, idx, val);
        else _update(2 * i, l, mid, idx, val);
        tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }

    T _query(int i, int l, int r, int rx, int ry) {
        if(r < rx || ry < l) return unit;
        if(rx <= l && r <= ry) return tree[i];
        int mid = (l + r) / 2;
        return merge(_query(2 * i, l, mid, rx, ry), _query(2 * i + 1, mid + 1, r, rx, ry));
    }

    T query(int l, int r) { return _query(1, 1, n, l, r); }

    void update(int idx, T val) { _update(1, 1, n, idx, val); }
};


int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin>>n;
    std::vector<int> height(n + 1), value(n + 1), dp(N);
    for(int i = 1;i<=n;i++) cin>>height[i];
    for(int i = 1;i<=n;i++) cin>>value[i];

    dp[height[1]] = value[1];
    SegTree<int>seg(N);
    seg.update(height[1], value[1]);
    int ans = value[1];
    for(int i = 2;i<=n;i++){
        dp[height[i]] = value[i];
        dp[height[i]] = max(dp[height[i]], value[i] + seg.query(1, height[i] - 1));
        seg.update(height[i], dp[height[i]]);
        ans = max(ans, dp[height[i]]);
    }
    cout<<ans;
}
