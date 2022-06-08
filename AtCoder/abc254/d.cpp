//
//  d.cpp
//  2022-06-04 20:15
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

signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n; cin >> n; 
  vector<int> is(n + 1, 0), prime; 
  vector<vector<int>> fac(n + 1);
  for (int i = 2; i <= n; i++) {
    if (is[i] == 0) {
      prime.push_back(i); 
      fac[i].push_back(i);
      for (int j = 2; j * i <= n; j++) {
        is[j * i] = 1;
        int val = j * i;
        int cnt = 0;
        while (val % i == 0) cnt ^= 1, val /= i;
        if (cnt) fac[j * i].push_back(i);
      }
    }
  }
  vector<int> cnt(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    int val = 1;     
    for (auto &it : fac[i]) val *= it;
    cnt[val]++;
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += cnt[i] * cnt[i]; 
  }
  cout << ans;
   
  return 0;
}
