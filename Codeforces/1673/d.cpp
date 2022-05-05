//
//  d.cpp
//  2022-04-30 23:22
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

int lca(int a, int b) {
  return a / gcd(a, b) * b;
}

signed main() {
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z; 
  while (z--) {
    int fb, db, n; cin >> fb >> db >> n;
    int fc, dc, m; cin >> fc >> dc >> m;
    if (dc % db) {
      cout << 0 << endl;
      continue;
    }
    auto getlr = [&] (int st, int ed, int f, int d) {
      if ((st - f) % d || (ed - f) % d) return make_pair(-MOD * 3, -MOD * 3); 
      return make_pair((st - f) / d + 1, (ed - f) / d + 1);
    };
    pair<int, int> lr = getlr(fc, fc + (m - 1) * dc, fb, db); 
    if (lr.first == lr.second && lr.first == -MOD * 3) {
      cout << 0 << endl;
      continue;
    }
    if (lr.first < 1 || lr.second > n) {
      cout << 0 << endl;
      continue;
    }

    if (fb > fc - dc || (fb + (n - 1) * db < fc + (m) * dc)) {
      cout << -1 << endl;
      continue;
    }
    int limit = sqrt(dc);
    auto calc = [&] (int d) {
      int st = fc - dc;
      int ed = fc + (m) * dc;
      pair<int, int> lr2 = getlr(st, ed, fc, d);
      pair<int, int> lr1 = getlr(fc, fc + (m - 1) * dc, fc, d); 
      lr2.first++;
      lr2.second--;
      assert(lr2.second >= lr2.first);
      int l = (lr1.first - lr2.first + 1 + MOD) % MOD;
      int r = (lr2.second - lr1.second + 1 + MOD) % MOD;
      return 1ll * l * r % MOD;
    };
    int ans = calc(dc);    
    if (db == dc) {
      (ans += calc(1)) %= MOD;
    }
    for (int i = 2; i <= limit; i++) {
      if (dc % i) continue;
      int a = i, b = dc / i; 
      if (lca(a, db) == dc) (ans += calc(a)) %= MOD; 
      if (b != a && lca(b, db) == dc) (ans += calc(b)) %= MOD;
    }
    cout << ans << endl;
  }
   
  return 0;
}
