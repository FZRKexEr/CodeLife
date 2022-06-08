//
//  d.cpp
//  2022-05-17 13:52
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
  //freopen("out.txt", "w", stdout);
#endif
}

signed main() {
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z; 
  while (z--) {
    int n; cin >> n;
    string s[3]; 
    cin >> s[0] >> s[1] >> s[2];
    array<int, 2> cnt[3];
    for (int i = 0; i < 3; i++) cnt[i][0] = cnt[i][1] = 0;
    vector<int> ord_0, ord_1;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < n * 2; j++) {
        if (s[i][j] == '0') cnt[i][0]++; 
        else cnt[i][1]++;
      }
      if (cnt[i][0] >= cnt[i][1]) ord_0.push_back(i);
      if (cnt[i][1] >= cnt[i][0]) ord_1.push_back(i);
    }
    if ((int) ord_0.size() >= 2) {
      //debug(ord_0[0], ord_0[1]);
      int tot = 0;
      int limit = max(cnt[ord_0[0]][0], cnt[ord_0[1]][0]);
      vector<int> ans(limit + 2, 0);
      for (int i = 0; i < n * 2; i++) {
        if (s[ord_0[0]][i] == '0') tot++;
        else ans[tot]++;
      }
      tot = 0;
      for (int i = 0; i < n * 2; i++) {
        if (s[ord_0[1]][i] == '0') tot++;
        else ans[tot]++;
      }
      for (int i = 0; i <= limit; i++) {
        if (i != 0) cout << 0;
        for (int j = 0; j < ans[i]; j++) cout << 1;
      }
      cout << endl;
    } else {
      int tot = 0;
      int limit = max(cnt[ord_1[0]][1], cnt[ord_1[1]][1]);
      vector<int> ans(limit + 2, 0);
      for (int i = 0; i < n * 2; i++) {
        if (s[ord_1[0]][i] == '1') tot++;
        else ans[tot]++;
      }
      tot = 0;
      for (int i = 0; i < n * 2; i++) {
        if (s[ord_1[1]][i] == '1') tot++;
        else ans[tot]++;
      }
      for (int i = 0; i <= limit; i++) {
        if (i) cout << 1;
        for (int j = 0; j < ans[i]; j++) cout << 0;
      }
      cout << endl;
    }
  }
  
  return 0;
}
