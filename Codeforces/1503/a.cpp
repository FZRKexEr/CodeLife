//
//  a.cpp
//  2022-05-25 13:49
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
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z; 
  while (z--) {
    int n; cin >> n;
    string s; cin >> s;
    int cnt_1 = 0, cnt_0 = 0;
    for (int i = 0; i < (int) s.length(); i++) {
      if (s[i] == '1') {
        cnt_1++; 
      } else {
        cnt_0++;
      }
    }
    if (cnt_1 % 2 || cnt_0 % 2) {
      cout << "NO" << endl;
    } else {
      vector<int> a(n, 0), b(n, 0);
      int tot = 1;
      int o = 1;
      for (int i = 0; i < (int) s.length(); i++) {
        if (s[i] == '1') {
          if (tot <= cnt_1 / 2) {
            a[i] = 1;  
            b[i] = 1;
            tot++;
          } else {
            a[i] = -1;
            b[i] = -1;
          }
        } else {
          if (o) {
            a[i] = 1;
            b[i] = -1;
          } else {
            a[i] = -1;
            b[i] = 1;
          }
          o ^= 1;
        }
      }
      int sum = 0, flag = 1;  
      for (int i = 0; i < n; i++) {
        sum += a[i]; 
        if (sum < 0) flag = false;
      }

      assert(sum == 0);
      for (int i = 0; i < n; i++) {
        sum += b[i];
        if (sum < 0) flag = false;
      }
      assert(sum == 0);
      if (flag) {
        cout << "YES" << endl;
        for (int i = 0; i < n; i++) {
          if (a[i] == 1) cout << "("; 
          else cout << ")";
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
          if (b[i] == 1) cout << "("; 
          else cout << ")";
        }
        cout << endl;
      } else {
        cout << "NO" << endl;
      }
    }
  }
   
  return 0;
}
