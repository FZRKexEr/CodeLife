//
//  b.cpp
//  2022-05-06 22:52
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
    string s; cin >> s;
    int k; cin >> k;
    vector<int> has(300, 0); 
    for (int i = 1; i <= k; i++) {
      char c; cin >> c;
      has[c] = 1;
    }
    vector<int> a(n, 0), pos;
    for (int i = 0; i < n; i++) {
      a[i] = has[s[i]];
      if (a[i]) pos.push_back(i);
    }
    if (pos.size() == 0) {
      cout << 0 << endl;
      continue;
    }
    int l = 0, r = n;
    while (l <= r) {
      int mid = (l + r) / 2;
      int all = 0, tot = -1;
      for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
          all++;
          continue;
        }
        tot++;
        if (tot == (int) pos.size() - 1) break;
        int life = min(pos[tot + 1] - pos[tot], mid);
        all = max(0ll, all - life);
        all++;
      }
      if (all > mid) l = mid + 1;
      else r = mid - 1;
    }
    cout << l << endl;
  }
   
  return 0;
}
