//
//  c.cpp
//  2022-07-04 13:58
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define LOCAL
using namespace std;

signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  

  int n; cin >> n;   
  int ans = 0; 
  
  auto sg = [&] (int x) {
    if (x % 8 == 0) return x - 1;
    if (x % 8 == 7) return x + 1;
    return x;
  };

  for (int i = 1; i <= n; i++) {
    int val; cin >> val;
    ans ^= sg(val);     
  }
  if (ans) cout << "First";
  else cout << "Second";

  return 0;
}
