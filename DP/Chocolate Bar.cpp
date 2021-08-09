#include "bits/stdc++.h"
#define int long long

using namespace std;

int dp[31][31][51];

int solve(int rowSize, int colSize, int reqdPieces){
    if(rowSize * colSize == reqdPieces || reqdPieces == 0) return 0;
    int &ans = dp[rowSize][colSize][reqdPieces];
    if(ans != -1) return ans;
    ans = INT_MAX;
    /*for vertical cut*/
    for(int cut = 1;cut<colSize;cut++){
        int newPieces = (rowSize * cut <= reqdPieces ? rowSize * cut : reqdPieces);
        ans = min(ans, rowSize * rowSize + solve(rowSize, cut, newPieces) + solve(rowSize, colSize - cut, reqdPieces - newPieces));
    }
    /*for horizontal cut*/
    for(int cut = 1;cut<rowSize;cut++){
        int newPieces = (colSize * cut <= reqdPieces ? colSize * cut : reqdPieces);
        ans = min(ans, colSize * colSize + solve(cut, colSize, newPieces) + solve(rowSize - cut, colSize, reqdPieces - newPieces));
    }
    return ans;
}    

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    memset(dp, -1, sizeof(dp));
    int t; cin>>t;
    while(t--){
        int a, b, c; cin>>a>>b>>c;
        cout<<solve(a, b, c)<<"\n";
    }
    return 0;
}
