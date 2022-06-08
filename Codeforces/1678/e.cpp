//
//  e.cpp
//  2022-05-09 01:43
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

struct DSU {
  vector<int> f, dep, sz;   
  DSU(int n) : f(n + 1), dep(n + 1, 0), sz(n + 1, 1) { iota(f.begin(), f.end(), 0); }

  inline int find(int x) {
    while (x != f[x]) x = f[x] = f[f[x]];
    return x;
  }

  inline bool merge(int x, int y) {
    x = find(x), y = find(y); 

    if (x == y) return false;
    if (dep[x] > dep[y]) swap(x, y);
    if (dep[x] == dep[y]) dep[y]++;

    f[x] = y;    
    sz[y] += sz[x];
    return true;
  }
};

signed main() {
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z; 
  while (z--) {
    int n; cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
      cin >> b[i]; 
    }
    DSU T(n);
    for (int i = 1; i <= n; i++) {
      T.merge(a[i], b[i]);
    }
    vector<int> vis(n + 1, 0);
    int ans = 0;
    vector<int> c;
    for (int i = 1; i <= n; i++) {
      if (vis[T.find(i)]) continue; 
      vis[T.find(i)] = 1;
      c.push_back(T.sz[T.find(i)]); 
    }
    int tot = 1;
    for (int i = 0; i < (int) c.size(); i++) {
      if (c[i] & 1) c[i]--;
    }
    for (int i = 0; i < (int) c.size(); i++) {
      int res = n - (tot + c[i] / 2 - 1) + 1 - tot;
      res += (c[i] - 1) * (n - tot + 1 - tot + n - tot + 1 - tot - (c[i] - 2)) / 2;
      ans += res;
      tot = tot + c[i] / 2;
    }
    cout << ans << endl;
  }
  return 0;
}
