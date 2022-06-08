//
//  e.cpp
//  2022-05-17 14:42
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

int power(int a, int b) {
  if (b >= 62) return 1000000000000000000ll + 2ll;
  if (b < 0) return 1; 
  return 1ll << b;
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
  auto get = [&] (int i, int j) {
    return power(2, i - j - 1);
  };
  
  int z; cin >> z;
  while (z--) {
    int n, k; cin >> n >> k;
    vector<int> ans(n + 1);
    int p = 1;
    int ff = 0;
    while (p <= n) {
      int flag = 1;
      for (int i = 1; i <= n - p + 1; i++) {
        if (get(n - p + 1, i) >= k) {
          for (int j = p; j <= p + i - 1; j++) {
            ans[j] = i - (j - p) + p - 1;
          }
          p = p + i;
          flag = 0;
          break;
        } else {
          k -= get(n - p + 1, i);
        }
      }
      if (flag) {
        ff = 1;
        break;
      }
    }
    if (ff) cout << -1; 
    else for (int i = 1; i <= n; i++) cout << ans[i] << " "; 
    cout << endl;
  }
  return 0;
}
