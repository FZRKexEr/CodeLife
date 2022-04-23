//
//  d.cpp
//  2022-04-22 23:23
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define LOCAL
using namespace std;

#ifdef ONLINE_JUDGE
#ifndef LOCAL_TEST
#pragma GCC optimize("O3","unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif
#endif

vector<string> vec_splitter(string s) {
	s += ',';
  vector<string> res;
	while(!s.empty()) {
    res.push_back(s.substr(0, s.find(',')));
		s = s.substr(s.find(',') + 1);
	}
	return res;
}

void debug_out(
vector<string> __attribute__ ((unused)) args,
__attribute__ ((unused)) int idx, 
__attribute__ ((unused)) int LINE_NUM) { cerr << endl; } 
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T) {
	if(idx > 0) cerr << ", "; else cerr << "Line(" << LINE_NUM << ") ";
  stringstream ss; ss << H;
  cerr << args[idx] << " = " << ss.str();
	debug_out(args, idx + 1, LINE_NUM, T...);
}


#ifdef LOCAL
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) 2022
#endif

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
  int z; cin >> z; 
  while (z--) {
    int n, x; cin >> n >> x;
    vector<int> a(n);
    int base = 0;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      if (i) {
        base += abs(a[i] - a[i - 1]);
      }
    }
    int ans = 1e18;
    for (int i = 1; i < n; i++) {
      int res = base;
      res -= abs(a[i] - a[i - 1]);       
      res += min(abs(a[i] - 1) + abs(a[i - 1] - x), abs(a[i] - x) + abs(a[i - 1] - 1)) + x - 1;
      ans = min(res, ans);
    }
    ans = min(ans, abs(a[0] - 1) + x - 1 + base);
    ans = min(ans, abs(a[0] - x) + x - 1 + base);
    ans = min(ans, abs(a[n - 1] - x) + x - 1 + base);
    ans = min(ans, abs(a[n - 1] - 1) + x - 1 + base);

    vector<array<int, 2>> res1 = {{abs(x - a[n - 1]), n}, {abs(x - a[0]), 0}}, res2 = {{abs(1 - a[n - 1]), n}, {abs(1 - a[0]), 0}};
    for (int i = 1; i < n; i++) {
      res1.push_back({-abs(a[i] - a[i - 1]) + abs(a[i - 1] - x) + abs(a[i] - x), i});
      res2.push_back({-abs(a[i] - a[i - 1]) + abs(a[i - 1] - 1) + abs(a[i] - 1), i});
    }
    sort(res1.begin(), res1.end());
    sort(res2.begin(), res2.end());
    if (res1[0][1] != res2[0][1]) ans = min(ans, base + res1[0][0] + res2[0][0]);
    else {
      if (x != 1) {
        ans = min(ans, base + res1[0][0] + res2[1][0]);
        ans = min(ans, base + res1[1][0] + res2[0][0]);
      } else {
        ans = min(ans, base + res1[0][0]);
      }
    }
    cout << ans << endl;
  }
  return 0;
}
