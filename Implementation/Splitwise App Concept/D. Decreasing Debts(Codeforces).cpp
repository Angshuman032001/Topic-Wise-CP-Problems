#include "bits/stdc++.h"
#define int long long

using namespace std;

const int N = 1e5 + 1;

struct transaction{
    int giver, receiver, money;
    transaction(int a, int b, int d) : giver(a), receiver(b), money(d) {}
};

std::vector<int> netAmount(N);

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m; cin>>n>>m;   
    for(int i = 1;i<=m;i++){
        int a, b, d; cin>>a>>b>>d;
        netAmount[a] -= d;
        netAmount[b] += d;
    }

    priority_queue<pair<int,int>>receive;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>give;

    for(int i = 1;i<=n;i++){
        if(netAmount[i] < 0) give.push(make_pair(abs(netAmount[i]), i));
        else if(netAmount[i] > 0) receive.push(make_pair(netAmount[i], i));
    }

    std::vector<transaction> v;

    while(!receive.empty() && !give.empty()){
        auto giverInfo = give.top(), receiverInfo = receive.top();
        give.pop();
        receive.pop();
        int giveAmt = giverInfo.first, receiveAmt = receiverInfo.first;
        if(giveAmt == receiveAmt){
            v.push_back(transaction(giverInfo.second, receiverInfo.second, giveAmt));
        }
        else if(giveAmt > receiveAmt){
            v.push_back(transaction(giverInfo.second, receiverInfo.second, receiveAmt));
            giverInfo.first -= receiveAmt;
            give.push(giverInfo);
        }
        else{
            v.push_back(transaction(giverInfo.second, receiverInfo.second, giveAmt));
            receiverInfo.first -= giveAmt;
            receive.push(receiverInfo);
        }
    }


    cout<<v.size()<<"\n";
    for(auto x : v){
        cout<<x.giver<<" "<<x.receiver<<" "<<x.money<<"\n";
    }

}
