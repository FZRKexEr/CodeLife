//
//  d.cpp
//  2022-05-23 19:48
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
//  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z; 
  while (z--) {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> odd;
    for (int i = 0; i < (int) s.length(); i++) {
      if (s[i] == '1') odd.push_back(i); 
    }
    if ((int) odd.size() % 2 == 1) cout << "NO" << endl;
    else if ((int) odd.size() < 2) cout << "NO" << endl;
    else {
      if ((int) odd.size() == n) {
        if (n % 2) cout << "NO" << endl; 
        else {
          cout << "YES" << endl;
          for (int i = 2; i <= n; i++) {
            cout << 1 << " " << i << endl;
          }
        }
      } else {
        cout << "YES" << endl;
        int root = 0; 
        while (s[root] == '1') root++;
        int p = (root + 1) % n;
        vector<int> que;
        vector<array<int, 2>> ans;
        while (p != root) {
          que.push_back(p);
          if (s[p] == '1') {
            ans.push_back({root + 1, que[0] + 1});
            for (int i = 1; i < (int) que.size(); i++) {
              ans.push_back({que[i - 1] + 1, que[i] + 1});
            }
            que.clear();
          }
          p++;
          p %= n;
        } 
        if ((int) que.size() != 0) {
          reverse(que.begin(), que.end());
          que.push_back(ans.back()[1] - 1);
          int last = ans.back()[0] - 1;
          ans.pop_back();
          ans.push_back({last + 1, que[0] + 1});
          for (int i = 1; i < (int) que.size(); i++) {
            ans.push_back({que[i - 1] + 1, que[i] + 1});
          }
          que.clear();
        }
        for (auto &it : ans) {
          cout << it[0] << " " << it[1] << endl;
        }
      }
    }
  }
  return 0;
}
  
