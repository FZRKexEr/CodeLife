//
//  f.cpp
//  2022-07-10 18:57
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long

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
struct Mobius {
  vector<int> is, prinum, miu, sum;
  int inv2, inv6;

  Mobius(int n) : is(n + 1, 0), miu(n + 1, 1), sum(n + 1, 0) {

    inv2 = power(2, MOD - 2);
    inv6 = power(6, MOD - 2);

    prinum.reserve(n + 1);
    for (int i = 2; i <= n; i++) {
      if (!is[i]) prinum.push_back(i), miu[i] = -1;  
      for (auto &it : prinum) {
        if (it * i > n) break;
        is[it * i] = 1;
        if (i % it == 0) {
          miu[it * i] = 0;
          break;
        } else {
          miu[it * i] = -1 * miu[i];
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      sum[i] = (sum[i - 1] + miu[i] * i * i % MOD + MOD) % MOD;
    }
  }

  int g(int n, int m, int k) {
    n /= k, m /= k; 
    int ans = 0; 
    int limit = min(n, m);

    auto f = [&](int x) {
      return (1 + x) * x % MOD * inv2 % MOD;
    };

    for (int d = 1, nxt; d <= limit; d = nxt) {
      nxt = min(n / (n / d), m / (m / d)) + 1;
      int l = d, r = nxt - 1;
      ans = (ans + f(n / d) * f(m / d) % MOD * (sum[r] - sum[l - 1] + MOD) % MOD + MOD) % MOD;
    }
    return ans;
  }
  
};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int n, m, a; cin >> n >> m >> a;   

  int limit = min(n, m);
  
  Mobius T(limit); 
  int ans = 0;
  for (int d = 1, nxt; d <= min(limit, a); d = nxt) {
    nxt = min({n / (n / d), m / (m / d), a}) + 1; 
    int l = d, r = nxt - 1;
    ans += ((l + r) * (r - l + 1) % MOD * T.inv2) % MOD * T.g(n, m, d) % MOD; 
    ans %= MOD;
  }
  cout << ans;
  
  return 0;
}
