//
//  a.cpp
//  2022-07-11 19:46
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long

const int N = 202;
int f[4][4][N][N][2];
array<int, 5> pre[4][4][N][N][2];

int dfs(int a, int b, int c, int d, int o) {
  if (c < 0 || d < 0) return 0;
  if (a < 0 || b < 0) return 0;
  if (f[a][b][c][d][o] != -1) return f[a][b][c][d][o];
  auto &t = f[a][b][c][d][o];
  auto &p = pre[a][b][c][d][o];
  t = 0;
  int limit = (a + b <= 4) ? 25 : 15;
  for (int i = 0; i <= limit - 2; i++) {
    if (dfs(a - 1, b, c - limit, d - i, 0) && (a > b || o == 0)) {
      t = 1;
      p = {a - 1, b, c - limit, d - i, 0};
    }
    if (dfs(a, b - 1, c - i, d - limit, 0) && (a < b || o == 0)) {
      t = 1;
      p = {a, b - 1, c - i, d - limit, 0};
    }
  }
  for (int i = limit; i <= 200; i++) {
    if (dfs(a - 1, b, c - i, d - (i - 2), 0) && (a > b || o == 0)) {
      t = 1;
      p = {a - 1, b, c - i, d - (i - 2), 0};
    }
    if (dfs(a, b - 1, c - (i - 2), d - i, 0) && (a < b || o == 0)) {
      t = 1;
      p = {a, b - 1, c - (i - 2), d - i, 0};
    }
  }
  return t;
}

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  memset(f, -1, sizeof(f));  
  f[0][0][0][0][0] = 1;

  function<vector<array<int, 2>>(array<int, 5>)> output = [&] (array<int, 5> sta) {
    auto [a, b, c, d, o] = sta;
    vector<array<int, 2>> ans;
    if (a == 0 && b == 0 && c == 0 && d == 0) return ans;
    ans = output(pre[a][b][c][d][o]);  
    ans.push_back({c - pre[a][b][c][d][o][2], d - pre[a][b][c][d][o][3]}); 
    return ans;
  };

  int z; cin >> z;
  while (z--) {
    int a, b; cin >> a >> b;
    if (dfs(3, 0, a, b, 1)) {
      cout << "3:0" << endl;
      auto ans = output({3, 0, a, b, 1});
      sort(ans.begin(), ans.end());
      for (int i = 0; i < (int) ans.size(); i++) {
        cout << ans[i][0] << ":" << ans[i][1] << " ";
      }
      cout << endl;
    } else if (dfs(3, 1, a, b, 1)) {
      cout << "3:1" << endl;
      auto ans = output({3, 1, a, b, 1});
      for (int i = 0; i < 4; i++) {
        if (ans[i][0] < ans[i][1]) {
          swap(ans[i], ans[0]);
          break;
        }
      }
      for (int i = 0; i < (int) ans.size(); i++) {
        cout << ans[i][0] << ":" << ans[i][1] << " ";
      }
      cout << endl;
    } else if (dfs(3, 2, a, b, 1)) {
      cout << "3:2" << endl;
      auto ans = output({3, 2, a, b, 1});
      for (int i = 0; i < 5; i++) {
        if (ans[i][0] < ans[i][1]) {
          swap(ans[2], ans[i]);
          break;
        }
      }
      for (int i = 0; i < (int) ans.size(); i++) {
        cout << ans[i][0] << ":" << ans[i][1] << " ";
      }
      cout << endl;
    } else if (dfs(2, 3, a, b, 1)) {
      cout << "2:3" << endl;
      auto ans = output({2, 3, a, b, 1});
      for (int i = 0; i < 5; i++) {
        if (ans[i][0] > ans[i][1]) {
          swap(ans[i], ans[2]);
          break;
        }
      }
      for (int i = 0; i < (int) ans.size(); i++) {
        cout << ans[i][0] << ":" << ans[i][1] << " ";
      }
      cout << endl;
    } else if (dfs(1, 3, a, b, 1)) {
      cout << "1:3" << endl;
      auto ans = output({1, 3, a, b, 1});
      for (int i = 0; i < 4; i++) {
        if (ans[i][0] > ans[i][1]) {
          swap(ans[i], ans[0]);
          break;
        }
      }
      for (int i = 0; i < (int) ans.size(); i++) {
        cout << ans[i][0] << ":" << ans[i][1] << " ";
      }
      cout << endl;
    } else if (dfs(0, 3, a, b, 1)) {
      cout << "0:3" << endl;
      auto ans = output({0, 3, a, b, 1});
      sort(ans.begin(), ans.end());
      reverse(ans.begin(), ans.end());
      for (int i = 0; i < (int) ans.size(); i++) {
        cout << ans[i][0] << ":" << ans[i][1] << " ";
      }
      cout << endl;
    } else cout << "Impossible" << endl;
  }

  return 0;
}
