//using dp to check if ans exists, and if it exists using recursion to print the ans
#include "bits/stdc++.h"

using namespace std;

int dp[1001][1001 + 1001];
int n, k;
string s; 

int solve(int index, int sum){
    if(index >= n){
        return max(sum, -sum) == k;
    }
    if(max(sum, -sum) == k){
        return 0;
    }
    int &ans = dp[index][sum + n];
    if(ans != -1) return ans;
    ans = 0;
    if(s[index] == '?'){
        for(int i = -1;i<=1;i++){
            if(solve(index + 1, sum + i)){
                ans = 1;
            }
        }
    }
    else{
        ans = solve(index + 1, sum + (s[index] == 'W' ? 1 : (s[index] == 'L' ? -1 : 0)));
    }
    return ans;
}

void go(int index, int sum){
    if(index >= n) return;
    if(s[index] == '?'){
        string sample = "LDW";
        for(int i = -1;i<=1;i++){
            if(solve(index + 1, sum + i)){
                cout<<sample[i + 1];
                go(index + 1, sum + i);
                return;
            }
        }
    }
    else{
        cout<<s[index];
        go(index + 1, sum + (s[index] == 'W' ? 1 : (s[index] == 'L' ? -1 : 0)));
    }
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    memset(dp, -1, sizeof(dp));

    cin>>n>>k;
    cin>>s;

    if(!solve(0, 0)){
        cout<<"NO\n";
    }
    else{
        go(0, 0);
    }

}
