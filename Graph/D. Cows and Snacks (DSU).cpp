//https://codeforces.com/contest/1209/problem/D

#include "bits/stdc++.h"

using namespace std;

struct UF {
    int N;
    std::vector<int> e;
    int cnt;
    void init(int n){
        e.assign(n + 1,-1);
        cnt = n;
    }
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        cnt--;
        return true;
    }
};

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, k; cin>>n>>k;
    
    UF dsu;
    dsu.init(n);
    int ans = 0;
    for(int i = 1;i<=k;i++){
        int a, b; cin>>a>>b;
        dsu.join(a, b);
    }

    vector<bool>visited(n + 1, false);
    int totalSatisfied = 0;
    for(int i = 1;i<=n;i++){
        if(visited[dsu.find(i)]) continue;
        totalSatisfied += (dsu.size(i) - 1);
        visited[dsu.find(i)] = true;
    }

    cout<<k - totalSatisfied;

}
