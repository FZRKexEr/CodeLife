//
//  a.cpp
//  2022-04-24 20:07
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int __int128
#define endl '\n'
#define LOCAL
using namespace std;

random_device rd; // 使用硬件熵源的随机数生成器
mt19937 seed(rd());
uniform_int_distribution<long long> U(1, 1000000000ll); // 1 - 1e9

const int MOD = 1e9 + 7;
int power(int a, int b) {
  assert(b >= 0);
  int base = a, ans = 1;
  while (b) {
    if (b & 1) ans = ans * base % MOD;
    base = base * base % MOD;
    b >>= 1;
  }
  return ans;
}

void file() {
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
#endif
}

signed main() {
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  long long n; cin >> n; 
  vector<long long> t(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> t[i]; 
  }

  function<bool(int, int)> sol = [&] (int x, int pos) {
    if (pos == 1) return true; 
    int l = 0, r = 1ll << (61 - t[pos - 1]);
    while (l <= r) {
      int mid = (l + r) >> 1;
      int val = (mid << (t[pos - 1] + 1)) + (1ll << t[pos - 1]);
      if (val >= x) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    if (r == -1) return false;
    int val = (r << (t[pos - 1] + 1)) + (1ll << t[pos - 1]);
    assert(val < x);
    if (sol(val, pos - 1)) return true;
    return false;
  };

  int limit = 61 - t[n];
  int l = 0, r = 1ll << limit;

  while (l <= r) {
    int mid = (l + r) >> 1;
    int val = (mid << (t[n] + 1)) + (1ll << t[n]);
    if (sol(val, n)) r = mid - 1;
    else l = mid + 1;
  } 
  long long ans = (long long) (((l << (t[n] + 1)) + (1ll << t[n])));
  cout << ans << endl;
  assert(ans >= 1);
  
  return 0;
}
