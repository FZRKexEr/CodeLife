//
//  check.cpp
//  2022-07-11 17:20
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long

signed main() {
  freopen("out2.txt", "r", stdin);
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n; cin >> n; 
  for (int i = 1; i <= n; i++) {
    string s; cin >> s;
    if (s == "Impossible") continue;
    int win = s[0] - '0', lose = s[2] - '0';
    int cntw = 0, cntl = 0;
    int flag = true;
    for (int i = 1; i <= win + lose; i++) {
      cin >> s;
      if (s[0] > s[2]) cntw++;
      else if (s[0] < s[2]) cntl++;
      
      if (cntw == 3 && i != win + lose) flag = false;
//      if (s[0] - '0' > s[2] - '0' && s[0] - s[2] < 2) flag = false;
//      if (s[0] - '0' < s[2] - '0' && s[2] - s[0] < 2) flag = false;
//      if (abs(s[0] - s[2]) != 2 && (max(s[0], s[2]) - '0' != 25 && i <= 4)) flag = false; 
//      if (abs(s[0] - s[2]) != 2 && (max(s[0], s[2]) - '0' != 15 && i == 5)) flag = false; 
    }
    if (cntw != win || cntl != lose) flag = false;
    
    if (!flag) cout << i << endl;
  }

  return 0;
}
