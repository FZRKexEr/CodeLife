//
//  loj137.cpp
//  2022-07-19 23:30
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif


// 快速读入输出
// 1. From tourist 
// 2. 唯一的修改, 增加 #define endl '\n'
// 3. 支持 __int128
// 4. 其他用法 cin cout 一样

#define endl '\n'
static struct FastInput {
  static constexpr int BUF_SIZE = 1 << 20;
  char buf[BUF_SIZE];
  size_t chars_read = 0;
  size_t buf_pos = 0;
  FILE *in = stdin;
  char cur = 0;

  inline char get_char() {
    if (buf_pos >= chars_read) {
      chars_read = fread(buf, 1, BUF_SIZE, in);
      buf_pos = 0;
      buf[0] = (chars_read == 0 ? -1 : buf[0]);
    }
    return cur = buf[buf_pos++];
  }
 
  inline void tie(int) {}

  inline explicit operator bool() {
    return cur != -1;
  }

  inline static bool is_blank(char c) {
    return c <= ' ';
  }

  inline bool skip_blanks() {
    while (is_blank(cur) && cur != -1) {
      get_char();
    }
    return cur != -1;
  }
 
  inline FastInput& operator>>(char& c) {
    skip_blanks();
    c = cur;
    return *this;
  }
  
  inline FastInput& operator>>(string& s) {
    if (skip_blanks()) {
      s.clear();
      do {
        s += cur;
      } while (!is_blank(get_char()));
    }
    return *this;
  }
 
  template <typename T>
  inline FastInput& read_integer(T& n) {
    // unsafe, doesn't check that characters are actually digits
    n = 0;
    if (skip_blanks()) {
      int sign = +1;
      if (cur == '-') {
        sign = -1;
        get_char();
      }
      do {
        n += n + (n << 3) + cur - '0';
      } while (!is_blank(get_char()));
      n *= sign;
    }
    return *this;
  }

  template <typename T>
  inline typename enable_if<is_integral<T>::value, FastInput&>::type operator>>(T& n) {
    return read_integer(n);
  }
  
  #if !defined(_WIN32) || defined(_WIN64)
  inline FastInput& operator>>(__int128& n) {
    return read_integer(n);
  }
  #endif

  template <typename T>
  inline typename enable_if<is_floating_point<T>::value, FastInput&>::type operator>>(T& n) {
    // not sure if really fast, for compatibility only
    n = 0;
    if (skip_blanks()) {
      string s;
      (*this) >> s;
      sscanf(s.c_str(), "%lf", &n);
    }
    return *this;
  }
} fast_input;

#define cin fast_input

static struct FastOutput {
  static constexpr int BUF_SIZE = 1 << 20;
  char buf[BUF_SIZE];
  size_t buf_pos = 0;
  static constexpr int TMP_SIZE = 1 << 20;
  char tmp[TMP_SIZE];
  FILE *out = stdout;

  inline void put_char(char c) {
    buf[buf_pos++] = c;
    if (buf_pos == BUF_SIZE) {
      fwrite(buf, 1, buf_pos, out);
      buf_pos = 0;
    }
  }

  ~FastOutput() {
    fwrite(buf, 1, buf_pos, out);
  }

  inline FastOutput& operator<<(char c) {
    put_char(c);
    return *this;
  }

  inline FastOutput& operator<<(const char* s) {
    while (*s) {
      put_char(*s++);
    }
    return *this;
  }
 
  inline FastOutput& operator<<(const string& s) {
    for (int i = 0; i < (int) s.size(); i++) {
      put_char(s[i]);
    }
    return *this;
  }
 
  template <typename T>
  inline char* integer_to_string(T n) {
    // beware of TMP_SIZE
    char* p = tmp + TMP_SIZE - 1;
    if (n == 0) {
      *--p = '0';
    } else {
      bool is_negative = false;
      if (n < 0) {
        is_negative = true;
        n = -n;
      }
      while (n > 0) {
        *--p = (char) ('0' + n % 10);
        n /= 10;
      }
      if (is_negative) {
        *--p = '-';
      }
    }
    return p;
  }

  template <typename T>
  inline typename enable_if<is_integral<T>::value, char*>::type stringify(T n) {
    return integer_to_string(n);
  }

  #if !defined(_WIN32) || defined(_WIN64)
  inline char* stringify(__int128 n) {
    return integer_to_string(n);
  }
  #endif

  template <typename T>
  inline typename enable_if<is_floating_point<T>::value, char*>::type stringify(T n) {
    sprintf(tmp, "%.17f", n);
    return tmp;
  }

  template <typename T>
  inline FastOutput& operator<<(const T& n) {
    auto p = stringify(n);
    for (; *p != 0; p++) {
      put_char(*p);
    }
    return *this;
  }
} fast_output;

#define cout fast_output

struct Bottleneck {
  
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

  // LCA·改
  // 求出 lca 的同时求出两点路径上的边权最大值。
  // p[i][j][0] 是边权(最大值)
  // G[i][j][0] 是边权
  struct LCA {
    vector<vector<array<int, 2>>> G, p;
    vector<int> d;
    int n, s; 
  
    LCA(int _n, int _s) : G(_n + 1), d(_n + 1, 1), n(_n), s(_s) {
      p.resize(_n + 1);
      int level = 0;
      while ((1 << level) <= _n) level++;
      for (int i = 0; i <= _n; i++) {
        p[i].resize(level + 1);
      }
    }
  
    int flag = false;
  
    void add(int u, int v, int w) {
      G[u].push_back({w, v});
      G[v].push_back({w, u});
    }
    
    void dfs(int pos, int fa) {
      p[pos][0][1] = fa;
      for (auto &[w, v] : G[pos]) {
        if (v == fa) continue;
        d[v] = d[pos] + 1;
        p[v][0][0] = w;
        dfs(v, pos);
      }
    }
  
    void init() {
      flag = true; 
      dfs(s, s); 
      for (int level = 1; (1 << level) <= n; level++) {
        for (int i = 1; i <= n; i++) {
          p[i][level][1] = p[p[i][level - 1][1]][level - 1][1];
          p[i][level][0] = max(p[i][level - 1][0], p[p[i][level - 1][1]][level - 1][0]);
        }
      }
    }
    // 返回 [0] 最大边权 [1] lca ，如果最大边权不存在，返回0
    array<int, 2> lca(int a, int b) {
      assert(flag);
      if (d[a] < d[b]) swap(a, b); 
      int i, j;
      for (i = 0; (1 << i) <= d[a]; i++);  
      i--; 
      int max_edge = 0;
      
      for (j = i; j >= 0; j--) {
        if (d[a] - (1 << j) >= d[b]) {
          max_edge = max(max_edge, p[a][j][0]);
          a = p[a][j][1];
        }
      }
      if (a == b) return {max_edge, b}; 
      for (j = i; j >= 0; j--) {
        if (p[a][j][1] != p[b][j][1]) {
          max_edge = max(max_edge, p[a][j][0]);
          max_edge = max(max_edge, p[b][j][0]);
          a = p[a][j][1];
          b = p[b][j][1];
        }
      }
      max_edge = max(max_edge, p[a][0][0]);
      max_edge = max(max_edge, p[b][0][0]);
      return {max_edge, p[a][0][1]};
    }
  };

  vector<array<int, 3>> edges;
  DSU T1;
  LCA T2; 

  Bottleneck(int n): T1(n), T2(n, 1) {}
  
  void add(int u, int v, int w) {
    edges.push_back({w, u, v});
  }

  void build() {
    sort(edges.begin(), edges.end());
    for(auto &[w, u, v] : edges) {
      if (T1.merge(u, v)) {
        T2.add(u, v, w);
      }
    }
    T2.init(); 
  }

  int query(int a, int b) {
    if (T1.find(a) != T1.find(b)) return 0;
    return T2.lca(a, b)[0]; 
  }
};

int a, b, c, p;

inline int rnd(){ return a=(a*b+c)%p;}


signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int n, m; cin >> n >> m;

  Bottleneck T(n);

  for (int i = 1; i <= m; i++) {
    int u, v, w; cin >> u >> v >> w;
    T.add(u, v, w);  
  }

  T.build();

  int q; cin >> q; 
  cin >> a >> b >> c >> p;

  int all = 0;
  const int MOD = 1e9 + 7;
  for (int i = 1; i <= q; i++) {
    int u=rnd()%n+1,v=rnd()%n+1;
    if (u == v) continue;
    else (all += T.query(u, v)) %= MOD;
  }

  cout << all;

  return 0;
}
