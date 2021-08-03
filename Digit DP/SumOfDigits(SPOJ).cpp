#include "bits/stdc++.h"
#define int long long
#define sz(x) (int)x.size()

using namespace std;

int dp[11][2][100];
std::vector<int> number;

int solve(int index, int flag, int sum){
    if(index == sz(number)) return sum;
    int &ans = dp[index][flag][sum];
    if(ans != -1) return ans;
    int limit;
    if(flag) limit = 9;
    else limit = number[index];

    ans = 0;
    for(int digit = 0;digit<=limit;digit++){
        int newFlag = flag;
        if(flag == 0 && digit < limit) newFlag = 1;
        ans = (ans + (solve(index + 1, newFlag, sum + digit)));
    }
    return ans;
}

int solve(int value){
    number.clear();
    int temp = value;

    memset(dp, -1, sizeof(dp));

    while(temp){
        number.push_back(temp%10);
        temp /= 10;
    }

    reverse(number.begin(), number.end());

    return solve(0, 0, 0);
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int a, b; 
    while(true){
        cin>>a>>b;
        if(a == -1 && b == -1) break;
        cout<<solve(b) - solve(a - 1)<<"\n";
    }
    return 0;
}
