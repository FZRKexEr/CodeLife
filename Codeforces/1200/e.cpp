//
//  e.cpp
//  2022-05-17 20:30
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

random_device rd; 
mt19937 seed(rd());
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
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


// 说明:
// 1. 没有在纯 int 环境测试，所以最好开 #define int long long
// 2. 注意调用函数是 1 indexed，只有 string 是 0 indexed
// 3. 初始化O(n), 查询子串 hash O(1), 添加长度为 len 的字符串 O(len) 
// 4. 不能初始化一个空串
// 
// 5. 不排除模板出错的可能性。

struct Hash {
  const array<int, 2> MOD = {127657753, 987654319};
  const array<int, 2> P = {137, 277};

  int n;
  string s; // 0 - indexed
  vector<array<int, 2>> hs; // 1 - indexed
  vector<array<int, 2>> pw; // 0 - indexed

  Hash(string _s) {
    assert(_s.length());
    n = _s.length(); 
    s = _s; 
    hs.resize(n + 1);
    pw.resize(n + 1);
    
    pw[0] = {1, 1};
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < 2; j++) {
        pw[i][j] = 1ll * pw[i - 1][j] * P[j] % MOD[j];
      }
    }
    hs.resize(n + 1, {0, 0}); 
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 2; j++) {
        hs[i + 1][j] = (hs[i][j] * P[j] % MOD[j] + s[i]) % MOD[j];
      }
    }
  }

  void add(string _s) {
    int old_n = n;
    n += _s.length(); 
    s += _s;
    hs.resize(n + 1);
    pw.resize(n + 1);
    for (int i = old_n + 1; i <= n; i++) {
      for (int j = 0; j < 2; j++) {
        pw[i][j] = 1ll * pw[i - 1][j] * P[j] % MOD[j];
      }
    }
    hs.resize(n + 1, {0, 0}); 
    for (int i = old_n; i < n; i++) {
      for (int j = 0; j < 2; j++) {
        hs[i + 1][j] = (hs[i][j] * P[j] % MOD[j] + s[i]) % MOD[j];
      }
    }
  }

  array<int, 2> get_hash(int l, int r) { // 1 - indexed
    assert(1 <= l && l <= r && r <= n); 
    array<int, 2> ans;
    for (int i = 0; i < 2; i++) {
      ans[i] = (hs[r][i] - 1ll * hs[l - 1][i] * pw[r - l + 1][i] % MOD[i] + MOD[i]) % MOD[i];
    }
    return ans;
  }
};


signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n; cin >> n;  
  
  string ans; cin >> ans;
  Hash h_a(ans);

  for (int i = 2; i <= n; i++) {
    string s; cin >> s;
    Hash h_s(s);
    int res = min(s.length(), ans.length()); 
    while (res) {
      if (h_a.get_hash((int) ans.length() - res + 1, (int) ans.length()) == h_s.get_hash(1, res)) break;
      res--;
    }
    s.erase(s.begin(), s.begin() + res);
    ans += s;
    h_a.add(s); 
  }
  cout << ans;
   
  return 0;
}
