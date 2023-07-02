//
// Created by iv.kem on 3/7/23.
//
#include <bits/stdc++.h>
#define int long long

using namespace std;

vector <vector <int> > g;
vector <int> used;
vector <bool> prize;
bool ans = 1;
// for (int i = 0; i < g.size(); ++i)

void dfs(int u){
    used[u] = 1;

    for(auto v : g[u]){
        if(used[v] == 0)
            dfs(v);
        else
            if(used[v] == 1) {
                ans = 0;
                used[v] = 2;
                return;
            }
    }
    used[u] = 2;
    return;
}

void solve(){
    int n;
    cin >> n;
    g.resize(n);
    used.resize(n);
    for (int i = 0; i < n; ++i){
        int u;
        cin >> u;
        used[i] = 0;
        if(used[u] == -1)
            continue;
        u--;
        g[i].push_back(u);
        if(u == i){
            ans = 0;
        }
    }
    if(!ans){
        cout << "NO" << "\n";
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (used[i] == 0)
            dfs(i);
    }
    if(!ans)
        cout << "NO" << "\n";
    else
        cout << "YES" << "\n";
    return;
}
signed main(){
    solve();
    return 0;
}