//
//  sj.cpp
//  2022-05-26 03:37
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
  //freopen("in.txt", "r", stdin);
   freopen("in.txt", "w", stdout);
#endif
}

signed main() {
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z = 100; 
  cout << z << endl;
  uniform_int_distribution<long long> U(0, 5); // 1 - 1e9
  for (int i = 1; i <= z; i++) {
    int c = U(seed);
    uniform_int_distribution<long long> V(0, 5 - c); // 1 - 1e9
    int d = V(seed); 
    uniform_int_distribution<long long> vv(0, 10 - (c + d) * 2); // 1 - 1e9
    int a = vv(seed); 
    int b = 10 - (c + d) * 2 - a;
    cout << a << " " << b << " " << c << " " << d << endl;
    vector<int> arr; 
    for (int i = 0; i < a; i++) arr.push_back(1);
    for (int i = 0; i < b; i++) arr.push_back(2);
    for (int i = 0; i < c; i++) arr.push_back(3);
    for (int i = 0; i < d; i++) arr.push_back(4);
    vector<int> p(arr.size()); 
    iota(p.begin(), p.end(), 0);   
    assert(p.size());

    uniform_int_distribution<long long> vvv(0, (int) p.size() - 1); // 1 - 1e9
    for (int j = 1; j <= 100; j++) swap(p[vvv(seed)], p[vvv(seed)]); 

    string t; 
      for (int j = 0; j < (int) p.size(); j++) {
        if (arr[p[j]] == 1) t+="A";
        if (arr[p[j]] == 2) t+="B";
        if (arr[p[j]] == 3) t+="AB";
        if (arr[p[j]] == 4) t+="BA";
      }
      for (int j = 0; j < 5; j++) {
        swap(t[U(seed)], t[U(seed)]);
      }
    cout << t << endl;    
  }
   
  return 0;
}
