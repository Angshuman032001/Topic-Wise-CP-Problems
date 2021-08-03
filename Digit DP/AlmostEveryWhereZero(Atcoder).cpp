#include "bits/stdc++.h"
#define int long long
#define sz(x) (int)x.size()

using namespace std;

int dp[110][2][4];
int k; 
string n;
std::vector<int> v;

void precompute(){
    for(char c : n){
        v.push_back(c - '0');
    }
}

int solve(int index, int flag, int cnt){
    if(cnt > k) return 0;
    if(index == sz(v)) return (cnt == k);
    int &ans = dp[index][flag][cnt];
    if(ans != -1) return ans;

    ans = 0;

    int limit;
    if(flag) limit = 9;
    else limit = v[index];

    for(int digit = 0;digit<=limit;digit++){
        int newFlag = flag;
        if(digit < limit && flag == 0) newFlag = 1;
        if(digit == 0) ans += solve(index + 1, newFlag, cnt);
        else ans += solve(index + 1, newFlag, cnt + 1);
    }

    return ans;

}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin>>n>>k;
    precompute();
    memset(dp, -1, sizeof(dp));
    cout<<solve(0, 0, 0);
}
