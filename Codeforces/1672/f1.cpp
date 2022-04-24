//
//  f1.cpp
//  2022-04-23 23:14
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
//  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z;  
  while (z--) {
    int n; cin >> n;
    vector<int> a(n + 1);

    vector<vector<int>> belong(n + 1);
    vector<array<int, 2>> cnt(n + 1);
    for (int i = 1; i <= n; i++) {
      cnt[i][0] = 0;
      cnt[i][1] = i;
    }
     
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      belong[a[i]].push_back(i); 
      cnt[a[i]][0]++;
    }
    sort(cnt.begin() + 1, cnt.end());
    int st = 0;
    for (int i = 1; i <= n; i++) {
      if (cnt[i][0] != 0) {
        st = i;
        break;
      }
    }
    vector<int> ans(n + 1, 0);
    for (int i = st; i < n; i++) {
      int color = cnt[i][1];
      assert((int) belong[cnt[i + 1][1]].size() >= cnt[i][0]);
      for (int j = 0; j < cnt[i][0]; j++) {
        ans[belong[cnt[i + 1][1]][j]] = color; 
      }
      auto be = belong[cnt[i + 1][1]].begin();
      belong[cnt[i + 1][1]].erase(be, be + cnt[i][0]);
//      debug(belong[cnt[i + 1][1]].size());
    }

    int color = cnt[n][1];
    for (int i = st; i <= n; i++) {
      for (int j = 0; j < (int) belong[cnt[i][1]].size(); j++) {
        ans[belong[cnt[i][1]][j]] = color;
      }
    }
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << " ";
    }
    cout << endl;
  }
   
  return 0;
}
