// https://codeforces.com/contest/1484/problem/E

/*

let dp[i] denote the maximum beauty we can get uptil ith index
let j be the left smaller index of i, 

the current subsegment be (l, i]

Now we have two kind of choices for the current subsegment, either take the left boundary <= j or > j
if we take the left boundary <= j, then we will be adding dp[j] to our answer, 
if we take the left boundary greater than j then we need to find the range max of [j, i) and add beauty[i] 
as in the range (j, i) all the heights are greater than ith building

*/

#include "bits/stdc++.h"
#define int long long

const int inf = 1e18;

using namespace std;

template <class T> struct SegTree {
    int n; vector <T> tree;
    const T unit = -inf;

    T merge(T a, T b) { return max(a, b); }
    
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
    std::vector<int> height(n + 1), beauty(n + 1), dp(n + 1, -inf), left_smaller(n + 1);
    std::vector<pair<int,int>> st;

    for(int i = 1;i<=n;i++) cin>>height[i];
    for(int i = 1;i<=n;i++) cin>>beauty[i];

    /* for every index i find the greatest index j such that height[j] < height[i] */
    for(int i = 1;i<=n;i++){
        while(!st.empty() and st.back().first > height[i]) st.pop_back();
        if(st.empty()) left_smaller[i] = -1;
        else left_smaller[i] = st.back().second;
        st.push_back({height[i],i});
    }
    
    dp[0] = 0, dp[1] = beauty[1];

    SegTree<int>seg(n);
    seg.update(1, dp[1]);

    /*

    dp[i] = max(max dpj(leftSmall[i] <= j < i) + beauty[i], dp[leftSmall[i]])
    the first part is when the ith building is not in the same photo as the leftSmall buildding
    The second part corresponds to the case when building i is in the same photo as leftSmall

    */

    for(int i = 2;i<=n;i++){
        int prevSmall = left_smaller[i];
        if(prevSmall == -1){
            dp[i] = max(seg.query(1, i - 1) + beauty[i], beauty[i]);
        }
        else{
            dp[i] = max(dp[prevSmall], seg.query(prevSmall, i - 1) + beauty[i]);
        }
        seg.update(i, dp[i]);
    }

    cout<<dp[n];

}
