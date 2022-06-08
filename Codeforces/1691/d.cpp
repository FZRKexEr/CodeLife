//
//  d.cpp
//  2022-05-31 23:02
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
  vector<int> f, dep, size;   
  DSU(int n) : f(n + 1), dep(n + 1, 0), size(n + 1, 1) { iota(f.begin(), f.end(), 0); }

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
    size[y] += size[x];
    return true;
  }
};

signed main() {
  file();
  int z; cin >> z;
  while (z--) {
    int n; cin >> n;
    DSU T(n); 
    set<array<int, 3>> a;  
    vector<array<int, 3>> input(n + 1); 
    for (int i = 1; i <= n; i++) {
      int c, l, r;
      cin >> c >> l >> r;
      input[i] = {c, l, r};
      if (c) a.insert({l, -i, 1}), a.insert({r, i, 1}); 
      else a.insert({l, -i, 0}), a.insert({r, i, 0});
    }
    
    auto it = a.begin();
    set<array<int, 2>> colo[2];

    while (it != a.end()) {
      int ord = abs((*it)[1]);
      if ((*it)[1] > 0) { 
        colo[(*it)[2]].erase({input[ord][2], ord});
      } else {
        int op = (*it)[2] ^ 1;
        for (auto &jt : colo[op]) {
          T.merge(ord, jt[1]);           
        }
        auto jt = colo[op].end();
        if (jt != colo[op].begin()) {
          jt--;
          auto backup = *jt;
          colo[op].clear();
          colo[op].insert(backup);
        }
        colo[(*it)[2]].insert({input[ord][2], ord});
      }
      it++;
    }
    map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
      cnt[T.find(i)]++;  
    }
    cout << cnt.size() << endl;
  }
  return 0;
}
