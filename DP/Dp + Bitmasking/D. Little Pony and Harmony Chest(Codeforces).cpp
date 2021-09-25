// https://codeforces.com/contest/454/problem/D

#include "bits/stdc++.h"

using namespace std;

const int N = 101;

int dp[N][(1ll << 17)], a[N], primesMask[N], isPrime[N];
int n, primes = 0;

int solve(int index, int mask){
    if(index == n + 1) return 0;
    int &ans = dp[index][mask];
    if(ans != -1) return ans;
    ans = abs(a[index] - 1) + solve(index + 1, mask);
    for(int j = 2;j<=60;j++){
        if(!(mask & primesMask[j])){
            ans = min(ans, abs(a[index] - j) + solve(index + 1, mask | primesMask[j]));
        }
    }
    return ans;
}

void path(int index, int mask){
    if(index == n + 1) return;
    int ans = solve(index, mask);
    if(ans == abs(a[index] - 1) + solve(index + 1, mask)){
        cout<<"1 ";
        path(index + 1, mask);
        return;
    }
    else{
        for(int j = 2;j<=60;j++){
            if(!(mask & primesMask[j])){
                if(ans == abs(a[index] - j) + solve(index + 1, mask | primesMask[j])){
                    cout<<j<<" ";
                    path(index + 1, mask | primesMask[j]);
                    return;
                }
            }
        }
    }
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin>>n;
    for(int i = 1;i<=n;i++) cin>>a[i];

    memset(isPrime, 1, sizeof(isPrime));
    memset(dp, -1, sizeof(dp));
    isPrime[0] = isPrime[1] = 0;

    for(int i = 2;i<=60;i++){
        if(isPrime[i]){
            for(int j = 1;i * j<=60;j++){
                isPrime[i * j] = 0;
                primesMask[i * j] |= (1ll << primes);
            }
            primes++;
        }
    }

    solve(1, 0);
    path(1, 0);

}
