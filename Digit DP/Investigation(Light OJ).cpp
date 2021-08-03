/*https://vjudge.net/problem/LightOJ-1068*/

// sum greater than 81 is not possible for the range [1, 1<<30]
// dp states are (index, flag, sum, remainder)
// index denotes the currIndex where we are with repsect to the number 
// flag denotes whether in the past we have taken a digit smaller than the corresponding digit of the given number. If flag is 1 we can take any digit between 0 - 9
// sum denotes the current sum of digits till now. Max value of sum can be upto 81
// remainder denotes the remainder of the number formed upon dividing by k


#include "bits/stdc++.h"
#define int long long
#define sz(x) (int)x.size()

using namespace std;

std::vector<int> number;
const int N = 90;
int dp[11][2][N][N];
int a, b, k; 

int solve(int index, int flag, int sum, int remainder){
    if(index == sz(number)){
        return (sum > 0 && sum%k == 0 && remainder == 0);
    }
    int &ans = dp[index][flag][sum][remainder];
    if(ans != -1) return ans;
    ans = 0;

    int limit;

    if(flag) limit = 9;
    else limit = number[index];

    for(int digit = 0;digit<=limit;digit++){
        int newFlag = flag;
        if(flag == 0 && digit < limit) newFlag = 1;
        ans += solve(index + 1, newFlag, sum + digit, (10*remainder + digit)%k);
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
    int ans = solve(0, 0, 0, 0);
    return ans;
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; cin>>t;
    for(int _t = 1;_t<=t;_t++){
        cout<<"Case "<<_t<<": ";
        cin>>a>>b>>k;
        if(k <= 81)
            cout<<solve(b) - solve(a - 1)<<"\n";
        else cout<<0<<"\n";
    }
    return 0;
}
