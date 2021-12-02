/*

If we dividie the complete array into segments of length 1 then we are effectively not 
deducting any value from the sum

lets say we take any length subarray from c <= x <= 2 * c - 1, then the floor(x/c) will be 1
which means we deduct the minimum value of the subarray from the sum

let's say if we want to take a length of 2 * c so as to deduct the 2nd minimum from the sum, 
then its easy to observe that we can take a c length subarray such that this 2nd minimum 
becomes the minimum element of that subarray

Thus it can be concluded that its optimal to take subarray of length c and 1

Thus we can use dp to find the maximum sum of value that should be deducted from the total sum.
dp[i] denotes the maximum sum we can deduct from the suffix of i i.e [i.....n]

To find the minimum in a range we can use SparseTable to get the answer

*/

#include "bits/stdc++.h"
#define int long long

using namespace std;

const int MAX = 1e5 + 10;
int n, a[MAX];
template <class T> struct SparseTable {
    int n, logn;
    vector <int> log; vector <vector <T>> dp;
    SparseTable(int _n) {
        n = _n; logn = ceil(log2(n)) + 1;
        log.assign(n + 1, 0); dp.assign(logn, vector <T> (n, 0));
    }
    T comb(T a, T b) { return min(a, b); }
    void build() {
        log[1] = 0;
        for(int i = 0; i <= n; i ++) {
            if(i > 1) log[i] = log[i / 2] + 1;
            if(i < n) dp[0][i] = a[i];
        }
        for(int j = 1; j < logn; j ++) {
            for(int i = 0; i + (1 << j) <= n; i ++) {
                dp[j][i] = comb(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    T query(int l, int r) {
        int ln = log[r - l + 1];
        return comb(dp[ln][l], dp[ln][r - (1 << ln) + 1]);
    }
};

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int c; cin>>n>>c;
    for(int i = 0;i<n;i++) cin>>a[i];
    int sum = accumulate(a, a + n, 0ll);

    SparseTable<int>sp(n);
    sp.build();
    vector<int>dp(n + 1, 0);
    for(int i = n - 1;i>=0;i--){
        dp[i] = dp[i + 1];
        if(i + c <= n){
            dp[i] = max(dp[i], dp[i + c] + sp.query(i, i + c - 1));
        }
    }

    cout<<sum - dp[0];

}
