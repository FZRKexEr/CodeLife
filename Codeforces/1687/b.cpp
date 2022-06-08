//
//  b.cpp
//  2022-06-07 16:55
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
  int n, m; cin >> n >> m; 
  vector<array<int, 2>> edges(m);

  auto ask = [&] (string &s) {
    cout << "? " << s << endl;
    cout.flush();
    int res; cin >> res;
    return res;
  };

  for (int i = 0; i < m; i++) {
    string s(m, '0');
    s[i] = '1';
    edges[i] = {ask(s), i};
  }
  sort(edges.begin(), edges.end()); 
  string s(m, '0');
  int ans = 0;
  for (int i = 0; i < m; i++) {
    s[edges[i][1]] = '1';
    if (ask(s) == ans + edges[i][0]) {
      ans += edges[i][0];       
    } else {
      s[edges[i][1]] = '0';
    }
  }
  cout << "! " << ans << endl; 
  cout.flush();
  return 0;
}
