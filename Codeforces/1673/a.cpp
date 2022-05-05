//
//  a.cpp
//  2022-04-30 22:28
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z;  
  while (z--) {
    string s; cin >> s;
    int sum = 0;
    for (int i = 0; i < (int) s.length(); i++) {
      sum += s[i] - 'a' + 1;
    }
    if ((int) s.length() % 2) {
      int res = max(sum - (s[0] - 'a' + 1) * 2, sum - (s.back() - 'a' + 1) * 2);
      if (res > 0) {
        cout << "Alice " << res << endl;
      } else {
        cout << "Bob " << -res << endl;
      }
    } else {
      cout << "Alice " << sum << endl;
    }
  }
  return 0;
}
