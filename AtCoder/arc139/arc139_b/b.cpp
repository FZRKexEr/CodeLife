//
//  b.cpp
//  2022-04-24 21:09
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
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z; 
  while (z--) {
    int n; cin >> n;
    int a, b; cin >> a >> b;
    vector<int> c(3); 
    for (auto &it : c) cin >> it;
    if (a > b) swap(a, b), swap(c[1], c[2]);
    
    int limit = sqrt(n);
    if (b >= limit) {
      int ans = 1000000000000000000ll;
      for (int i = 0; i * b <= n; i++) {
        int res = c[2] * i;
        int re = n - i * b;
        if (c[1] > c[0] * a) {
          res += c[0] * re;
        } else {
          int cnt = re / a;  
          res += cnt * c[1] + (re - cnt * a) * c[0];
        }
        ans = min(ans, res);
      }
      cout << ans << endl;
    } else {
      if (c[0] * a < c[1] && c[0] * b < c[2]) {
        cout << c[0] * n << endl;
      } else {
        if ((c[1] * b) > (c[2] * a)) {
          swap(a, b);
          swap(c[1], c[2]);
        }  
        int ans = 0;
        assert(a <= sqrt(1e9));
        if (n > 1e6) {
          int cnt = (n - 1e6) / a; 
          assert(n - a * cnt >= 1e6);
          while (n - a * cnt > 1e6) cnt++;
          ans += cnt * c[1]; 
          n -= a * cnt;
          assert(n >= 1);
        }
        vector<int> f(n + 1, 1000000000000000000ll); 
        f[0] = 0;
        for (int i = 1; i <= n; i++) {
          f[i] = min(f[i - 1] + c[0], f[i]);
          if (i >= a) f[i] = min(f[i - a] + c[1], f[i]);
          if (i >= b) f[i] = min(f[i - b] + c[2], f[i]);
        }
        // OK
        ans += f[n];
        cout << ans << endl;
      }
    }
  }
   
  return 0;
}
