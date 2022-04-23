//
//  c.cpp
//  2022-04-23 14:09
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
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    sort(a.begin(), a.end());
    vector<int> sum(n);
    sum[0] = a[0];
    for (int i = 1; i < n; i++) {
      sum[i] = sum[i - 1] + a[i];
    }
    int ans = 0, res = 0, day = 0;
    while (res < n && sum[res] <= x) res++;
    res--; 
    if (res == -1) {
      cout << 0 << endl;
      continue;
    }
    assert(sum[res] <= x);
    int s = sum[res]; 
    // 1 2 2 
    while (res >= 0) {
//      debug(res, day);
      int add = x - s + 1;
      int dayadd;
      if (add % (res + 1) == 0) dayadd = add / (res + 1);
      else dayadd = add / (res + 1) + 1;

      add = dayadd * (res + 1);
      day += dayadd; 
      ans += dayadd * (res + 1);
      assert(add);
      s += add;

      while (s > x && res >= 0) {
        s -= (a[res] + day);
        res--;
      }
    }
    cout << ans << endl;
  }
   
  return 0;
}
