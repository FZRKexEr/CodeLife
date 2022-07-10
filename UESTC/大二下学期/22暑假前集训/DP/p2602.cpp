//
//  p2602.cpp
//  2022-05-09 22:01
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define LOCAL
using namespace std;

const int N = 20;
int vis[N][2][2];
vector<int> f[N][2][2];

vector<int> dfs(const string &s, int pos = 0, int lead0 = 1, int limit = 1) {
  if (vis[pos][lead0][limit]) 
    return f[pos][lead0][limit];

  vis[pos][lead0][limit] = 1;

  vector<int> res(10, 0);
  if (pos == (int) s.length() - 1) {
    int up = limit ? s[pos] - '0' : 9;
    for (int i = 0; i <= up; i++) res[i]++;
    return f[pos][lead0][limit] = res;
  }
  int up = limit ? s[pos] - '0' : 9; 
  for (int i = 0; i <= up; i++) {
    vector<int> nxt = dfs(s, pos + 1, i == 0 && lead0, limit && i == up);
    for (int j = 0; j <= 9; j++) res[j] += nxt[j];
    int add = 0;
    for (int j = pos + 1; j < (int) s.length(); j++) {
      add *= 10;
      if (limit && i == up) add += s[j] - '0';
      else add += 9;
    }
    add++; 
    if (i || !lead0) res[i] += add;
  }
  return f[pos][lead0][limit] = res;
}

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int a, b; cin >> a >> b; 

  memset(vis, 0, sizeof(vis));
  vector<int> ans1 = dfs(to_string(a - 1));  

  memset(vis, 0, sizeof(vis));
  vector<int> ans2 = dfs(to_string(b));

  for (int i = 0; i <= 9; i++) {
    cout << ans2[i] - ans1[i] << " ";
  }

  return 0;
}
