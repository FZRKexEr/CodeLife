//
//  d.cpp
//  2022-05-23 23:31
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

int ans = 0x3f3f3f3f;
int flag = true;
int cnt = 0;
void dfs(int n, int x, int res) {
  string s = to_string(x);
  if (res >= ans) return;
  int upper = 0, temp = x; 

  while ((int) to_string(temp).length() != n) {
    upper++;
    temp *= 9;
  }
  if (res + upper >= ans) return;

  if ((int) s.length() == n) {
    ans = min(ans, res);
    return;
  }

  vector<int> a(s.length());
  for (int i = 0; i < (int) s.length(); i++) a[i] = s[i] - '0';
  sort(a.begin(), a.end());

  a.erase(unique(a.begin(), a.end()), a.end());
  if (a.back() == 0 || a.back() == 1) {
    return;
  }

  for (int i = (int) a.size() - 1; i >= 0; i--) {
    cnt++;
    if (a[i] == 1) break;
    if (a[i] == 0) break;
    dfs(n, x * a[i], res + 1); 
  }
}

signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, x;  
  cin >> n >> x;
  if (x == 1) {
    if (n == 1) cout << 0;
    else cout << -1;
  } else {
    dfs(n, x, 0);
    if (ans == 0x3f3f3f3f) cout << -1 << endl;
    cout << ans << endl;
  }
   
  return 0;
}
