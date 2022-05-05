//
//  b.cpp
//  2022-04-27 19:01
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
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, k; cin >> n >> k; 
  vector<array<int, 2>> a(n * n + 1);
  vector<vector<int>> val(n + 1, vector<int> (n + 1));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> val[i][j];
      a[val[i][j]] = {i, j};
    }
  }
   
  vector<int> dp(n * n + 1, -1);
  set<int> add, sub;
  add.insert(a[n * n][0] + a[n * n][1]);
  sub.insert(a[n * n][0] - a[n * n][1]);
  dp[n * n] = 1; 

  for (int i = n * n - 1; i >= 1; i--) {
    array<int, 2> p = a[i];  
    int dis = 0;
    auto ita = add.end(); ita--;
    auto itb = sub.end(); itb--;
    dis = max(dis, abs(*ita - p[0] - p[1]));
    dis = max(dis, abs(*itb - p[0] + p[1]));
    ita = add.begin();
    dis = max(dis, abs(*ita - p[0] - p[1]));
    itb = sub.begin();
    dis = max(dis, abs(*itb - p[0] + p[1]));
    if (dis > k) dp[i] = 0;
    else {
      int padd = p[0] + p[1];
      int psub = p[0] - p[1];
      add.insert(padd);
      sub.insert(psub);
      dp[i] = 1;
    }
  }
  
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (dp[val[i][j]]) {
        cout << "M";
      } else {
        cout << "G";
      }
    }
    cout << endl;
  }
  
  return 0;
}
