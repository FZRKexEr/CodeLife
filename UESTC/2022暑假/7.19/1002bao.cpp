//
//  1002.cpp
//  2022-07-19 12:55
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
  vector<int> f, dep;
  DSU(int n) : f(n + 1), dep(n + 1, 0) { iota(f.begin(), f.end(), 0); }

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
    return true;
  }
};


signed main() {
 // freopen("in.txt", "r", stdin);
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

    vector<array<int, 2>> sta;

    for (int i = 0; i < (1ll << k); i++) {
      int cnt = 0;
      for (int j = 0; j < k; j++) {
        if (i >> j & 1) cnt++;
      }
      sta.push_back({cnt, i});
    }

    sort(sta.begin(), sta.end());

    for (int it = (int) sta.size() - 1; it >= 0; it--) {
      int i = sta[it][1];  
      vector<vector<int>> ban(n * m + 1, vector<int>(4, 0)), vis(n + 1, vector<int>(m + 1, 0));
      int res = 0;
      for (int j = 0; j < k; j++) {
        if (i >> j & 1) add(ban, j); // 15 * 15
        else res++;
      }
      queue<array<int, 2>> que; que.push({s[0] + 1, s[1] + 1});
      int tx[] = {0, 1, 0, -1}, ty[] = {1, 0, -1, 0};
      while (!que.empty()) {
        array<int, 2> jt = que.front(); que.pop();
        int x = jt[0];
        int y = jt[1];
        for (int o = 0; o < 4; o++) {
          int nx = x + tx[o];
          int ny = y + ty[o];
          if (nx < 1 || nx > n) continue;
          if (ny < 1 || ny > m) continue;
          if (ban[pos(x, y)][o]) continue;
          if (vis[nx][ny]) continue;
          vis[nx][ny] = 1;
          que.push({nx, ny});
        }
      }
      if (vis[t[0] + 1][t[1] + 1]) {
        cout << res << endl;
        break;
      }
    }
  }

  return 0;
}
