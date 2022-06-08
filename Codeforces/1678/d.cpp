//
//  d.cpp
//  2022-05-09 00:01
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
    int n, m; cin >> n >> m; 
    string s; cin >> s;
    vector<int> a(n * m), c;
    for (int i = 0; i < n * m; i++) a[i] = s[i] - '0';
    c = a;
    for (int i = 1; i < n * m; i++) a[i] += a[i - 1]; 

    vector<int> rol(n * m, 0), col(m * n, 0);

    for (int i = 0; i < m; i++) {
      if (a[i]) rol[i] = 1;
    }

    for (int i = m; i < n * m; i++) {
      if (a[i] - a[i - m]) rol[i] = rol[i - m] + 1;
      else rol[i] = rol[i - m];
    }

    queue<int> que;
    for (int i = 0; i < m; i++) que.push(0);
    
    for (int i = 0; i < n * m; i++) {
      if (i) col[i] = col[i - 1];
      int val = que.front(); que.pop(); 
      if (val == 0 && c[i] == 1) col[i]++;
      que.push(val | c[i]);
      col[i] = min(col[i], m);
    }
    
    for (int i = 0; i < n * m; i++) cout << col[i] + rol[i] << " ";
    cout << endl;
  }
   
  return 0;
}