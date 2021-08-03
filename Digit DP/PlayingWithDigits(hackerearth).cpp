//https://www.hackerearth.com/problem/algorithm/playing-with-digits-4e25844f/
// for k <= 4000 do normal digit dp 
//for k > 4000 do a brute force and check only the multiples of k if the sum of digits is prime

#include "bits/stdc++.h"
#define int long long
#define sz(x) (int)x.size()

using namespace std;

std::vector<bool> isPrime;
std::vector<int> sFactor,primes;
 
void sieve(int n) {
    isPrime.assign(n+1,true);
    sFactor.assign(n+1,0);
    isPrime[0]=isPrime[1]=false;
    primes={};
    for(int i=2;i<=n;i++) {
        if(isPrime[i]) {
            sFactor[i]=i;
            primes.push_back(i);
            for(int j=i*i;j<=n;j+=i)
            if(isPrime[j]) {
                isPrime[j]=false;
                sFactor[j]=i;
            }
        }
    }
}

bool check(int value){
    int sum = 0;
    while(value){
        sum += value%10;
        value /= 10;
    }
    return isPrime[sum];
}

int a, b, k;
int dp[11][2][100][4000];
std::vector<int> v;

int solve(int index, int flag, int sum, int rem){
    if(index == sz(v)){
        return (isPrime[sum] && rem == 0);
    }
    int &ans = dp[index][flag][sum][rem];
    if(ans != -1) return ans;
    ans = 0;
    int limit = (flag == 0 ? v[index] : 9);
    for(int digit = 0;digit<=limit;digit++){
        int newFlag = ((digit < limit && flag == 0) ? 1 : flag);
        ans += solve(index + 1, newFlag, sum + digit, (10 * rem + digit)%k);
    }
    return ans;
}

int solve(int value){
    v.clear();
    memset(dp, -1, sizeof(dp));
    while(value){
        v.push_back(value%10);
        value /= 10;
    }
    reverse(v.begin(), v.end());
    return solve(0, 0, 0, 0);
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    sieve(100);

    cin>>a>>b>>k;
    if(k <= 4000) cout<<solve(b) - solve(a - 1);
    else{
        int start = (a/k) * k;
        if(start < a) start += k;
        int ans = 0;
        for(int i = start;i<=b;i+=k){
            if(check(i)) ans++;
        }
        cout<<ans;
    }
}
