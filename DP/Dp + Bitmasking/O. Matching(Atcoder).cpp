// https://atcoder.jp/contests/dp/tasks/dp_o

#include "bits/stdc++.h"
#define int long long

using namespace std;

const int mod = 1e9 + 7, N = 22;

int n, grid[N][N], dp[N][(1 << 22)];

int add(int a, int b){
    a += b;
    if(a > mod) a -= mod;
    return a;
}

#define deb(...) cerr << "[" << #__VA_ARGS__ << "] : [", DBG(__VA_ARGS__)
void DBG() { cerr << "]\n";}
template<typename T, typename ...Args> void DBG(T first, Args... args)
{cerr << first; if(sizeof...(args))cerr<<", "; DBG(args...); }


int solve(int index, int mask){
    if(index == n){
        return (__builtin_popcountll(mask) == n);
    }
    int &ans = dp[index][mask];
    if(ans != -1){
        return ans;
    }

    ans = 0;
    for(int j = 0;j<n;j++){
        if(grid[index][j] == 1){
            if((mask & (1ll << j)) == 0){
                int tempMask = mask;
                tempMask |= (1ll << j);
                ans = add(ans, solve(index + 1, tempMask));
            }
        }
    }
    return ans;
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin>>n;
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            cin>>grid[i][j];
        }
    }
    memset(dp, -1, sizeof(dp));
    cout<<solve(0, 0);

}
