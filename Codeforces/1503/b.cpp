//
//  b.cpp
//  2022-05-25 13:58
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
  map<int, map<int, int>> mp;
  // x + y = 2  1 x + y = 1 3
  vector<array<int, 2>> p_1, p_3; 
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if ((i + j) % 2 == 0) p_1.push_back({i, j}); 
      else p_3.push_back({i, j});
    }
  }

  auto output = [&] (array<int, 2> a, int b) {
    cout << b << " " << a[0] << " " << a[1] << endl;
    cout.flush();
    return;
  };

  for (int i = 1; i <= n * n; i++) {
    int x; cin >> x;
    if (x == 2) {
      if ((int) p_1.size()) {
        output(p_1.back(), 1);
        p_1.pop_back();
      } else {
        assert((int) p_3.size());
        output(p_3.back(), 3);
        p_3.pop_back();
      }
    } else if (x == 1) {
      if ((int) p_3.size()) {
        output(p_3.back(), 3);
        p_3.pop_back();
      } else {
        output(p_1.back(), 2);  
        p_1.pop_back();
      }
    } else if (x == 3) {
      if ((int) p_1.size()) {
        output(p_1.back(), 1);
        p_1.pop_back();
      } else {
        output(p_3.back(), 2);
        p_3.pop_back();
      }
    }
  }
   
  return 0;
}
