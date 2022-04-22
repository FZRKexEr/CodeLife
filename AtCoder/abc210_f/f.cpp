//
//  f.cpp
//  2022-04-22 01:21
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


// 暴搜 + 随机化
// 最坏复杂度 O(nm), 随机化后很难被卡（怀疑甚至不能被卡）。
// 在随机数据下效率非常优秀。
// 下标从1开始。

struct TwoSAT{
  vector<vector<int>> G;
  vector<bool> vis;
  stack<int> stk;
  int n;

  TwoSAT(int _n) : G(_n * 2 + 2), vis(_n * 2 + 2, 0) { n = _n; }
 
  void addor(int a, int at, int b, int bt) {
    a += a + at;
    b += b + bt;
    G[a ^ 1].push_back(b); // !a -> b
    G[b ^ 1].push_back(a); // !b -> a
  }

  void addxor(int a, int at, int b, int bt) {
    a += a + at;
    b += b + bt;
    G[a].push_back(b ^ 1);
    G[b].push_back(a ^ 1);
  }

  bool dfs(int pos) {
    if (vis[pos ^ 1]) return false;
    if (vis[pos]) return true;
    vis[pos] = 1;
    stk.push(pos);
    for (auto &v : G[pos]) {
      if (!dfs(v)) return false;
    }
    return true;
  }

  bool sol() {
    random_device rd;
    mt19937 seed(rd());
    vector<int> ord(n + 1);
    iota(ord.begin(), ord.end(), 0);
    shuffle(ord.begin() + 1, ord.end(), seed); // 随机选点 dfs
    
    for (int i = 1; i <= n; i++) {
      int it = ord[i];
      if (!vis[it * 2 + 1] && !vis[it * 2]) {
        while (!stk.empty()) stk.pop();
        if (!dfs(it * 2)) {
          while (!stk.empty()) {
            vis[stk.top()] = 0;
            stk.pop();
          }
          if (!dfs(it * 2 + 1)) return false;
        }
      }
    }
    return true;
  }
};


vector<vector<int>> prime(int n) {
  vector<vector<int>> res(n + 1);
  for (int i = 2; i <= n; i++) {
    if ((int) res[i].size() == 0) {
      res[i].push_back(i);
      for (int j = 2; j * i <= n; j++) {
        res[j * i].push_back(i);
      }
    }
  }
  return res;
}

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n; cin >> n;  
  vector<vector<int>> res = prime(2e6);
  vector<array<int, 2>> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i][0] >> a[i][1];
  }
  
  TwoSAT T(n); 
  vector<vector<array<int, 2>>> pos;
  pos.resize(2e6 + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= 1; j++) {
      for (auto &it : res[a[i][j]]) {
        for (auto &jt : pos[it]) {
          T.addxor(i, j, jt[0], jt[1]); 
        }
      }
    }
    for (int j = 0; j <= 1; j++) {
      for (auto &it : res[a[i][j]]) {
        pos[it].push_back({i, j});
      }
    }
  }
  
   
  if (T.sol()) cout << "Yes" << endl;
  else cout << "No" << endl;
  return 0;
}
