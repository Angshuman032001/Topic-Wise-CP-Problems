//https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/practice-problems/algorithm/complete-journey-bf38d697/

#include "bits/stdc++.h"
#define int long long
#define sz(x) (int)x.size()

using namespace std;

const int MAX_WEIGHT = 1e5 + 1;

struct UF {
    int N;
    std::vector<int> e;
    void init(int n){
        e.assign(n,-1);
    }
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin>>n;

    UF dsu;
    dsu.init(n + 1);

    std::vector<std::vector<int>> indices(MAX_WEIGHT);
    for(int i = 1;i<=n;i++){
        int weight; cin>>weight;
        indices[weight].push_back(i);
    }

    int ans = 0;

    for(int wt = MAX_WEIGHT - 1;wt>=1;wt--){
        for(int i = 1;i<sz(indices[wt]);i++){
            if(dsu.join(indices[wt][i], indices[wt][i - 1])) ans += wt;
        }
        vector<int>multiplesIndices;
        for(int mul_wt = wt;mul_wt<MAX_WEIGHT;mul_wt += wt){
            if(sz(indices[mul_wt])) multiplesIndices.push_back(indices[mul_wt][0]);
        }
        for(int i = 1;i<sz(multiplesIndices);i++){
            if(dsu.join(multiplesIndices[i], multiplesIndices[i - 1])) ans += wt;
        }
    }
 
    cout<<ans;
}
