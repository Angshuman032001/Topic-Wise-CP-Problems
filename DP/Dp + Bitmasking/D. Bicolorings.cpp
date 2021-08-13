//https://codeforces.com/contest/1051/problem/D

#include "bits/stdc++.h"
#define int long long

using namespace std;

const int mod = 998244353;

inline int add(int x,int y){
    x+=y;
    if (x>=mod) return x-mod;
    return x;
}

inline int sub(int x,int y){
    x-=y;
    if (x<0) return x+mod;
    return x;
}

inline int mul(int x,int y){
    return (x%mod*1ll*y%mod)%mod;
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

 	int n, K; cin>>n>>K;   
 	int dp[n + 1][K + 3][4];
 	memset(dp, 0, sizeof(dp));

 	for(int mask = 0;mask<4;mask++){
 		dp[0][0][mask] = 1;
 		int setBitCount = __builtin_popcount(mask);
 		int components = ((setBitCount == 0 || setBitCount == 2) ? 1 : 2);
 		dp[1][components][mask] = 1;
 	}


 	for(int i = 2;i<=n;i++){
 		for(int k = 1;k<=K;k++){
 			for(int currMask = 0;currMask<4;currMask++){
 				for(int prevMask = 0;prevMask<4;prevMask++){
 					int value = prevMask ^ currMask;
 					value = __builtin_popcount(value);
 					if(value == 2){
 						if((currMask == 0 && prevMask == 3) || (currMask == 3 && prevMask == 0)) 
 							dp[i][k][currMask] = add(dp[i][k][currMask], dp[i - 1][k - 1][prevMask]);
 						else{
 							if(k - 2 >= 0)
 								dp[i][k][currMask] = add(dp[i][k][currMask], dp[i - 1][k - 2][prevMask]);
 						}
 					}
 					else if(value == 0) 
 						dp[i][k][currMask] = add(dp[i][k][currMask], dp[i - 1][k][prevMask]);
 					else{
 						if(currMask == 0 || currMask == 3) dp[i][k][currMask] = add(dp[i][k][currMask], dp[i - 1][k][prevMask]);
 						else dp[i][k][currMask] = add(dp[i][k][currMask], dp[i - 1][k - 1][prevMask]);
 					}
 				}
 			}
 		}
 	}

 	int ans = 0;
 	for(int mask = 0;mask<4;mask++){
 		ans = add(ans, dp[n][K][mask]);
 	}

 	cout<<ans;

}
