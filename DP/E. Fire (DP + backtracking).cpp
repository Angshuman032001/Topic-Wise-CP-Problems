// https://codeforces.com/contest/864/problem/E


// its always optimal to take items which burn out sooner, so sort the items by their d value
#include "bits/stdc++.h"

using namespace std;

struct item{
    int savingTime, destroyTime, value, index;
    item(int savingTime, int destroyTime, int value, int index) : savingTime(savingTime), destroyTime(destroyTime), value(value), index(index) {}
    bool operator<(const item &b){
        return destroyTime < b.destroyTime;
    }
};

int n; 
vector<item>v;
vector<int>ans;
int maximumValue;
int dp[101][3001];

int solve(int index, int time){
    if(index == n) return 0;
    int &ans = dp[index][time];
    if(ans != -1) return ans;
    ans = INT_MIN;
    if(time + v[index].savingTime < v[index].destroyTime){
        ans = max(ans, solve(index + 1, time));
        ans = max(ans, v[index].value + solve(index + 1, time + v[index].savingTime));
    }
    else ans = max(ans, solve(index + 1, time));
    return ans;
}

void backtrack(int index, int time, int currentValue){
    if(index == n) return;
    if(v[index].savingTime + time < v[index].destroyTime){
        if(currentValue == (v[index].value + solve(index + 1, time + v[index].savingTime))){
            ans.push_back(v[index].index);
            backtrack(index + 1, time + v[index].savingTime, currentValue - v[index].value);
        }
        else backtrack(index + 1, time, currentValue);
    }
    else backtrack(index + 1, time, currentValue);
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin>>n;
    for(int i = 0;i<n;i++){
        int t, d, p; cin>>t>>d>>p;
        v.push_back(item(t, d, p, i + 1));
    }

    sort(v.begin(), v.end());
    memset(dp, -1, sizeof(dp));

    maximumValue = solve(0, 0);
    backtrack(0, 0, maximumValue);
    cout<<maximumValue<<"\n";
    cout<<ans.size()<<"\n";
    for(auto &x : ans) cout<<x<<" ";

}
