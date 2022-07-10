//
//  a.cpp
//  2022-04-26 23:18
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define LOCAL
using namespace std;

signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n; cin >> n; 
  vector<vector<int>> G(n + 1);
  for (int i = 1; i <= n; i++) {
    int v; cin >> v;
    G[i].push_back(v);
  }
  int flag = false;
  for (int i = 1; i <= n; i++) {
    int vvv = G[G[G[i][0]][0]][0];
    if (vvv == i) {
      flag = true;
    }
  }
  if (flag) cout << "YES";
  else cout << "NO";
   
  return 0;
}
