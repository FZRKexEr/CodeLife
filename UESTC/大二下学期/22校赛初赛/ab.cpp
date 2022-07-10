//
//  ab.cpp
//  2022-05-04 17:55
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
struct Gray {
  vector<int> a; 
  Gray(int k) {
    a.resize(1ll << k, 0);
    for (int i = 1; i < (1ll << k); i++) {
      if (i & 1) a[i] = a[i - 1] ^ 1;
      else a[i] = a[i - 1] ^ (1 << (__builtin_ctzll(a[i - 1]) + 1));
    }
  }
};


int max_gray(int i) {
  int limit = 0;
  for (int j = 0; j < 60; j++) {
    if ((i >> j) & 1) limit = j; 
  }
  if ((1ll << limit) != i) limit++;
  Gray g(limit);
  vector<int> b = g.a;
  b.insert(b.end(), g.a.begin(), g.a.end());

  int res = 0x3f3f3f3f; 
  
  for (int j = 0; j < (1ll << limit); j++) {
    int maxn = 0;
    for (int k = 0; k < i; k++) {
      maxn = max(maxn, b[j + k]); 
    }
    res = min(res, maxn);
  }
  return res;
}

signed main() {
//  freopen("out.txt", "w", stdout);
  ios::sync_with_stdio(false); 
  cin.tie(0);

  int z = 0; cin >> z;
  while (z--) {
    int a, b; cin >> a >> b;
    int max_a = max_gray(a);
    int max_b = max_gray(b);
    int limit_a;
    for (int i = 0; i < 40; i++) {
      if ((1ll << i) & max_a) {
        limit_a = i;
      }
    }
    int limit_b;
    for (int i = 0; i < 40; i++) {
      if ((1ll << i) & max_b) {
        limit_b = i;
      }
    }
    int res1 = (max_a << (limit_b + 1)) | max_b; 
    int res2 = (max_b << (limit_a + 1)) | max_a;
    cout << min(res1, res2) << endl;
  }
  return 0;
}
