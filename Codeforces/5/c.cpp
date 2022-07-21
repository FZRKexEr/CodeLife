//
//  c.cpp
//  2022-07-21 20:03
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
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  string s; cin >> s; 
  int n = s.length(); 
  
  vector<int> left, minleft(n, n);
  int ans1 = 0, ans2 = 1;
  
  for (int i = 0; i < n; i++) {
    if (s[i] == '(') left.push_back(i);    
    else {
      if (!left.empty()) {
        if (left.back() >= 1 && s[left.back() - 1] == ')' && minleft[left.back() - 1] != n)
          minleft[i] = minleft[left.back() - 1];
        else 
          minleft[i] = left.back();
        if (i - minleft[i] + 1 > ans1) {
          ans1 = i - minleft[i] + 1;
          ans2 = 1;
        } else if (i - minleft[i] + 1 == ans1) ans2++;
        left.pop_back();
      } 
    }
  }
  cout << ans1 << " " << ans2;

  return 0;
}
