#include <bits/stdc++.h>
#define int long long
using namespace std;

struct Mobius {
  vector<int> is, prinum, miu;
  vector<int> cnt;
  vector<vector<int>> belong;
  int ans;

  Mobius(int n) : is(n + 1, 0), miu(n + 1, 1) {
    ans = 0;
    cnt.resize(n + 1, 0);
    belong.resize(n + 1);
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
      for (int j = i; j <= n; j += i) {
        belong[j].push_back(i);
      }
    }
  }

  void update(int val, int o) {
    for (auto &it : belong[val]) {
      ans -= cnt[it] * cnt[it] * miu[it];
      cnt[it] += o;
      ans += cnt[it] * cnt[it] * miu[it];
    }
  }
};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  
  int n, q; cin >> n >> q;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i]; 
  }

  Mobius T(5e5 + 10);

  vector<int> has(n + 1, 0);
  int cnt_1 = 0;

  for (int i = 1; i <= q; i++) {
    int id; cin >> id; 
    if (has[id]) {
      T.update(a[id], -1);
      if (a[id] == 1) cnt_1--;
    } else {
      T.update(a[id], 1);
      if (a[id] == 1) cnt_1++;
    }
    has[id] ^= 1;
    cout << (T.ans - cnt_1) / 2 << endl;
  }

  return 0;
}
