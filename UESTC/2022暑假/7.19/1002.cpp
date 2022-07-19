//
//  1002.cpp
//  2022-07-19 14:30
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


// Dijkstra 最短路，最短路计数
// 能处理 0 - n , 重边和自环不影响
// 注意根据数据范围替换 INF MOD
// 直接在 main 里面声明

const int INF = 0x3f3f3f3f;

struct Dijkstra {
  struct Edge {
    int w, v;

    Edge(int a, int b) : w(a), v(b) {}
    bool operator < (const Edge &oth) const {
      if (w != oth.w) return w < oth.w;
      return v < oth.v;
    }
  };
  
  vector<vector<Edge>> G; 
  vector<int> d;
  
  Dijkstra(int n) : G(n + 1), d(n + 1, INF) {}

  void add(int u, int v, int w) {  // 有向边
    G[u].push_back({w, v}); // (距离, 序号) w 在前!
  }
  
  void solve(int s) {
    d[s] = 0;
    set<Edge> que; // (距离, 序号) 

    for (int i = 0; i < (int)d.size(); i++) {
      que.insert({d[i], i}); // (距离, 序号) 
    }
    
    while (que.empty() == false) {
      int x = que.begin()->v;
      que.erase(que.begin());

      for (auto &it : G[x]) {
        int v = it.v, w = it.w;

        if (d[v] > d[x] + w) {
          que.erase({d[v], v}); // (距离, 序号) 
          d[v] = d[x] + w;
          que.insert({d[v], v});
        }
      }
    }
  }
};

signed main() {
  //file(); 
  ios::sync_with_stdio(false);
  cin.tie(0);

  int z; cin >> z;
  while (z--) {
    int n, m, k;
    cin >> n >> m >> k;
    array<int, 2> s, t;
    cin >> s[0] >> s[1] >> t[0] >> t[1];
    vector<array<int, 4>> wall(k);

    for (int i = 0; i < k; i++) {
      cin >> wall[i][0] >> wall[i][1] >> wall[i][2] >> wall[i][3];
    }

    auto pos = [&] (int x, int y) {
      return (x - 1) * m + y;
    };

    auto add = [&] (vector<vector<int>> &ban, int o) {
      if (wall[o][0] == wall[o][2]) {
        int x = wall[o][0];
        if (x == 0 || x == n) return;
        int l = min(wall[o][1], wall[o][3]);
        int r = max(wall[o][1], wall[o][3]);
        for (int y = l + 1; y <= r; y++) {
          if (x + 1 <= n) {
            ban[pos(x, y)][1] += 1;
            ban[pos(x + 1, y)][3] += 1;
          }
        }
      } else {
        int y = wall[o][1];
        if (y == 0 || y == m) return;
        int l = min(wall[o][0], wall[o][2]);
        int r = max(wall[o][0], wall[o][2]);
        for (int x = l + 1; x <= r; x++) {
          if (y + 1 <= m) {
            ban[pos(x, y)][0] += 1;
            ban[pos(x, y + 1)][2] += 1;
          }
        }
      }
    };

    vector<vector<int>> ban(n * m + 1, vector<int> (4, 0));
    for (int i = 0; i < k; i++) add(ban, i);     

    Dijkstra T(n * m + 1);

    int tx[] = {0, 1, 0, -1}, ty[] = {1, 0, -1, 0};
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        for (int o = 0; o < 4; o++) {
          int nx = i + tx[o];
          int ny = j + ty[o];
          if (nx < 1 || nx > n) continue; 
          if (ny < 1 || ny > m) continue;
          T.add(pos(i, j), pos(nx, ny), ban[pos(i, j)][o]);
        }
      }
    }
    T.solve(pos(s[0] + 1, s[1] + 1));
    cout << T.d[pos(t[0] + 1, t[1] + 1)] << endl;
  }

  return 0;
}
