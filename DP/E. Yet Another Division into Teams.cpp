// https://codeforces.com/contest/1256/problem/E

#include "bits/stdc++.h"
#define int long long

using namespace std;

const int inf = 1e18;

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

 	int n; cin>>n;
 	std::vector<pair<int,int>> v;
 	v.push_back(make_pair(0, 0));
 	for(int i = 1;i<=n;i++){
 		int skill; cin>>skill;
 		v.push_back(make_pair(skill, i));
 	}

 	sort(v.begin(), v.end());

 	std::vector<int> dp(n + 1, inf);

 	dp[0] = 0;
 	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>pq;
 	pq.push(make_pair(-v[1].first + dp[0], 1));
 	vector<int>prevValues(n + 1, -1);
 	prevValues[1] = 0;

 	for(int i = 3;i<=n;i++){
 		auto f = pq.top();
 		auto p = f;
 		if(f.second == i - 1){
 			pq.pop();
 			p = pq.top();
 		}
 		dp[i] = p.first + v[i].first;
 		prevValues[i] = p.second;
 		if(p != f) pq.push(f);
 		pq.push(make_pair(dp[i - 1] - v[i].first, i));
 	}

 	cout<<dp[n]<<" ";
 	vector<int>team(n + 1, -1);
 	int currentTeam = 1, index = n;
 	while(index != 0) {
 		int prevIndex = prevValues[index];
 		for(int j = prevIndex;j<=index;j++) team[v[j].second] = currentTeam;
 		currentTeam++;
 		index = prevIndex - 1;
 	}

 	cout<<*max_element(team.begin() + 1, team.end())<<"\n";
 	for(int i = 1;i<=n;i++) cout<<team[i]<<" ";

}
