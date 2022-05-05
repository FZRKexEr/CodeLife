//
//  b.cpp
//  2022-04-30 22:46
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z; 
  while (z--) {
    string s; cin  >> s;
    vector<int> a((int) s.length()); 
    for (int i = 0; i < (int) s.length(); i++) {
      a[i] = s[i] - 'a';
    }
    vector<vector<int>> cnt(a.size(), vector<int> (26, 0));
    vector<int> vis(26, 0);
    for (int i = 0; i < (int) a.size(); i++) {
      if (i) cnt[i] = cnt[i - 1];
      cnt[i][a[i]]++;
      vis[a[i]]++;
    }
    vector<int> last(26, -1);
    int flag = true;
    for (int i = 0; i < (int) a.size(); i++) {
      if (last[a[i]] == -1) last[a[i]] = i;
      else {
        for (int j = 0; j < 26; j++) {
          if (vis[j] == 0) continue;
          if (cnt[i][j] - cnt[last[a[i]]][j] == 0) flag = false;
        }
        last[a[i]] = i;
      }
    }
    if (flag) cout << "Yes" << endl;
    else cout << "no" << endl;
  }
   
  return 0;
}
