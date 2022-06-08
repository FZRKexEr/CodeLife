//
//  windy数.cpp
//  2022-05-10 00:36
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

const int N = 12;
int f[N][N][2][2];
int dfs(const string &s, int pre, int pos = 0, int lead0 = 1, int limit = 1) {
  auto &it = f[pre][pos][lead0][limit];
  if (it != -1) return it;
  int up = limit ? s[pos] - '0' : 9;
  it = 0;
  if (pos == (int) s.length() - 1) {
    for (int i = 0; i <= up; i++) {
      if (abs(i - pre) >= 2 || (lead0 && pre == 0)) {
        it++;
      }
    }
    return it;
  }
  for (int i = 0; i <= up; i++) {
    if (abs(i - pre) >= 2 || (lead0 && pre == 0)) {
      it += dfs(s, i, pos + 1, i == 0 && lead0, i == up && limit);
    }
  }
  return it;
}

signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int a, b; cin >> a >> b; 

  auto sol = [&](int x) {
    memset(f, -1, sizeof(f)); 
    int ans = dfs(to_string(x), 0); 
    return ans;
  };

  cout << sol(b) - sol(a - 1);
  
  return 0;
}
