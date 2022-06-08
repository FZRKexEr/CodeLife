//
//  dd.cpp
//  2022-05-26 03:31
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
  freopen("out.txt", "w", stdout);
#endif
}

signed main() {
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z; 
  while (z--) {
    int a, b, c, d; cin >> a >> b >> c >> d;
    string s; cin >> s;
    vector<int> arr; 
    for (int i = 0; i < a; i++) arr.push_back(1);
    for (int i = 0; i < b; i++) arr.push_back(2);
    for (int i = 0; i < c; i++) arr.push_back(3);
    for (int i = 0; i < d; i++) arr.push_back(4);
    vector<int> p(arr.size()); 
    iota(p.begin(), p.end(), 0);   
    int flag = 0;
    do {
      string t; 
      for (int i = 0; i < (int) p.size(); i++) {
        if (arr[p[i]] == 1) t+="A";
        if (arr[p[i]] == 2) t+="B";
        if (arr[p[i]] == 3) t+="AB";
        if (arr[p[i]] == 4) t+="BA";
      }
      if (t == s) {
        cout << "YES" << endl;
        flag = 1;
        break;
      }
    } while (next_permutation(p.begin(), p.end()));
    if (!flag) cout << "NO" << endl;
  }
   
  return 0;
}
