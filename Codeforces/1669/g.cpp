//
//  g.cpp
//  2022-04-21 23:09
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
    int n, m; cin >> n >> m;
    vector<vector<int>> d(n + 1, vector<int> (m)); 
    for (int i = 0; i < n; i++) {
      string s; cin >> s; 
      for (int j = 0; j < (int) s.length(); j++) {
        if (s[j] == '.') d[i][j] = 0;
        if (s[j] == '*') d[i][j] = 1;
        if (s[j] == 'o') d[i][j] = 2;
      }
    }
    for (int j = 0; j < m; j++) d[n][j] = 2;
    for (int i = 0; i < m; i++) {
      int cnt = 0, last = -1;
      for (int j = 0; j <= n; j++) {
        if (d[j][i] == 2) {
          for (int k = last + 1; k < j; k++) {
            d[k][i] = 0;
          }
          for (int k = j - cnt; k < j; k++) {
            d[k][i] = 1;
          }
          cnt = 0;
          last = j;
        } else if (d[j][i]){
          cnt++;
        }
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (d[i][j] == 0) cout << ".";
        if (d[i][j] == 1) cout << "*";
        if (d[i][j] == 2) cout << "o";
      }
      cout << endl;
    }
    cout << endl;
  }
   
  return 0;
}
