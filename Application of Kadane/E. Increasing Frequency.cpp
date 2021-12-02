//https://codeforces.com/contest/1082/problem/E

/*

Approach: 

1. First Observation: We can change only 1 number to c.
2. Second Observation: When we select a subarray [l, r] and a number d which we will transform to 
                       c our final ans is countOfC(1, n) + countOfNumber(l, r) - countOfC(l, r);
                       Here countOfC(1, n) is constant. So to maximize the final ans we need to maximize the value of
                       countOfNumber(l, r) - countOfC(l, r)
3. Thir Observation: Now we can turn this problem into kadane's algo, if we fix a number d that will change to c
                     between any two consecutive d's if there are any c present that will not contribute to the final ans
                     so remove their contribution and add 1 as the d will now change to c. Finally find the maximum subarray sum that
                     of all d's possible

Final ans will be countOfC(1, n) + maxSumArraySum

*/

#include "bits/stdc++.h"

using namespace std;

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, c; cin>>n>>c;
    vector<int>v(n), freq_c(n);
    for(int i = 0;i<n;i++){
        cin>>v[i];
        freq_c[i] = ((v[i] == c) + (i - 1 >=0 ? freq_c[i - 1] : 0));
    }

    int mx = *max_element(v.begin(), v.end());
    vector<int>prevIndex(mx + 1, -1);
    vector<vector<int>>segments(mx + 1);

    auto getCountOfC = [&](int start, int end)->int{    
        return freq_c[end] - (start - 1 >= 0 ? freq_c[start - 1] : 0);
    };

    auto maxSubarraySum = [&](int value)->int{
        int currSum = 0, mxSum = INT_MIN;
        for(int x : segments[value]){
            currSum += x;
            mxSum = max(mxSum, currSum);
            currSum = max(currSum, 0);
        }
        return mxSum;
    };

    for(int i = 0;i<n;i++){
        segments[v[i]].push_back(-getCountOfC(prevIndex[v[i]] + 1, i));
        segments[v[i]].push_back(1);
        prevIndex[v[i]] = i;
    }

    int ans = 0;
    for(int i = 1;i<=mx;i++){
        if(i == c) continue;
        ans = max(ans, maxSubarraySum(i));
    }

    ans = freq_c[n - 1] + ans;
    cout<<ans;

}

