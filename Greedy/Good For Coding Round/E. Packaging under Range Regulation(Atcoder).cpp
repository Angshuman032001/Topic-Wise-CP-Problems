// The idea is to assign the left most point possible to the interval with least end point.


#include "bits/stdc++.h"

using namespace std;

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        std::vector<pair<int,int>> v(n);
        for(auto &x : v) cin>>x.first>>x.second;
        sort(v.begin(), v.end());
        multiset<int>m;
        int index = 0, count = 0, currLeft = 0;
        while(!m.empty() || index < n){
            if(m.empty()) currLeft = v[index].first;
            while(index < n && v[index].first <= currLeft){
                m.insert(v[index++].second);
            }
            while(!m.empty() && (*m.begin()) < currLeft) m.erase(m.begin());
            if(!m.empty()){
                count++;
                currLeft++;
                m.erase(m.begin());
            }
        }
        cout<<(count == n ? "YES\n" : "NO\n");
    }      
    return 0;
}
