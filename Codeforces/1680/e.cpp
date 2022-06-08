//
//  e.cpp
//  2022-05-13 23:23
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
  int z; cin >> z;
  while (z--) {
    int n; cin >> n;
    array<string, 2> s; cin >> s[0] >> s[1];
    vector<int> dp[2];
    dp[0].resize(n + 1, 0);
    dp[1].resize(n + 1, 0);

    int st = 0;
    while (s[0][st] == '.' && s[1][st] == '.') st++;

    if (s[0][st] == '*' && s[1][st] == '*') {
      dp[1][st] = dp[0][st] = 1;
    } else {
      if (s[0][st] == '*') {
        dp[0][st] = 0;
        dp[1][st] = 1;
      } 
      if (s[1][st] == '*') {
        dp[1][st] = 0;
        dp[0][st] = 1;
      }
    }

    for (int i = st + 1; i < n; i++) {
      if (s[1][i] == '*' && s[0][i] == '*') {
        dp[0][i] = min(2 + dp[0][i - 1], 2 + dp[1][i - 1]);
        dp[1][i] = min(2 + dp[0][i - 1], 2 + dp[1][i - 1]);
      } else if (s[1][i] == '*') {
        dp[0][i] = min(2 + dp[0][i - 1], 2 + dp[1][i - 1]);
        dp[1][i] = min(2 + dp[0][i - 1], 1 + dp[1][i - 1]);
      } else if (s[0][i] == '*') {
        dp[0][i] = min(1 + dp[0][i - 1], 2 + dp[1][i - 1]);
        dp[1][i] = min(2 + dp[0][i - 1], 2 + dp[1][i - 1]);
      } else {
        dp[0][i] = min(1 + dp[0][i - 1], 2 + dp[1][i - 1]); 
        dp[1][i] = min(2 + dp[0][i - 1], 1 + dp[1][i - 1]);
      }
    }
    int ans = 0x3f3f3f3f;
    for (int i = n - 1; i >= 0; i--) {
      if (s[0][i] == '*' || s[1][i] == '*') {
        ans = min(dp[0][i], dp[1][i]);
        break;
      }
    }
    assert(ans != 0x3f3f3f3f);
    cout << ans << endl;;
  }
  
  return 0;
}
