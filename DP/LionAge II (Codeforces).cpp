#include "bits/stdc++.h"
#define int long long

using namespace std;

int grid[26][26], dp[101][101][26];
string s;
int k, n; 

int solve(int index, int rem, int prevCharIndex){
    if(index == s.length()) return 0;
    int &ans = dp[index][rem][prevCharIndex];
    if(ans != -1) return ans;
    ans = INT_MIN;
    ans = max(ans, grid[prevCharIndex][s[index] - 'a'] + solve(index + 1, rem, (s[index] - 'a')));
    for(int j = 0;j<26;j++){
        if(rem == 0 || j == (s[index] - 'a')) continue;
        ans = max(ans, grid[prevCharIndex][j] + solve(index + 1, rem - 1, j));
    }
    return ans;
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin>>s>>k>>n;

    memset(dp, -1, sizeof(dp));
    memset(grid, 0, sizeof(grid));

    for(int i = 1;i<=n;i++){
        char a, b; cin>>a>>b;
        int cost; cin>>cost;
        grid[a - 'a'][b - 'a'] = cost;
    }

    int ans = solve(1, k, s[0] - 'a');
    for(int i = 0;i<26;i++){
        if(k == 0 || i == (s[0] - 'a')) continue;
        ans = max(ans, solve(1, k - 1, i));
    }

    cout<<ans<<"\n";

}
