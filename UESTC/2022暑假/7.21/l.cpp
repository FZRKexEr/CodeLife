//
//  l.cpp
//  2022-07-21 12:05
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
#define int __int128

// 用线段辅助理解
// ------------
// --------------------

// gcd 性质：
// 1. gcd(a, b) 是 ax + by 能得到的最小的正整数
// 2. 在 ax + by = c 中，如果 c 不是 gcd(a, b) 的倍数，则无解
// 3. gcd(a, b) = gcd(b, a % b)

// 功能说明：
// ax + by = c
// 1. 求出 x > 0, y > 0 解的数量
// 2. 求出 x > 0, y > 0 解中 x 的最大值，y 的最大值
//
// 注意:
// 1. g = -1 说明无解
// 2. dx, dy 大于 0
// 3. 必须用 long long，值域极限是 max(a, b) * c

struct GCD {
  int a, b, c, g;
  int x, y, dx, dy; // dx 和 dy 是一次移动最小的距离，dx, dy > 0

  void exgcd(int a, int b, int &d, int &x, int &y) {
    if (!b) {
      d = a; x = 1; y = 0;
    } else {
      exgcd(b, a % b, d, y, x); y -= x * (a / b); // 注意括号！
    }
  }

  int abs(int x) {
    if (x < 0) return -1 * x;
    return x;
  }

  GCD(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {
    exgcd(a, b, g, x, y);
    if (c % g != 0) {
      g = -1;
      dx = dy = 0;
    } else {
      x *= c / g;
      y *= c / g;
      dx = abs(b / g);
      dy = abs(a / g);
    }
  }
  
  // 从 s 移动到超过 t 每次移动 d，需要的次数
  // s, t, d 可正可负 d 不能为 0
  int cnt(int s, int t, int d) {
    if (d < 0) d *= -1, swap(s, t);
    if (s < t) {
      if ((t - s) % d == 0) return (t - s) / d;
      return (t - s) / d + 1;
    } else {
      if ((t - s) % d == 0) return (t - s) / d;
      return (t - s) / d - 1;
    }
  }
    
  // 把 x 移动到最小正整数
  void move_x() {
    if (x > 0) {
      int cntx = cnt(x, 0, -dx);
      cntx--;
      x -= cntx * dx;
      y += cntx * dy;
    } else {
      int cntx = cnt(x, 1, dx);
      x += cntx * dx;
      y -= cntx * dy; 
    }
  }

  // 把 y 移动到最小正整数
  void move_y() {
    if (y > 0) {
      int cnty = cnt(y, 0, -dy);
      cnty--;
      y -= cnty * dy;
      x += cnty * dx;
    } else {
      int cnty = cnt(y, 1, dy);
      y += cnty * dy;
      x -= cnty * dx;
    }
  }
  
  // x > 0 并且 y > 0 的解的数量
  int count() { 
    move_x();   
    if (y <= 0) return 0; 
    int cnty = cnt(y, 0, -dy); 
    return cnty;
  }
};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int z; cin >> z;

  auto solve = [&](int x) {
    if (x < 0) return (array<int, 2>) {-1, -1};  
    if (x == 0) return (array<int, 2>) {0, 0};
    
    GCD T(365, 7, x); 

    if (T.g == -1) return  (array<int, 2>) {-1, -1}; 
    if (x % 365 == 0) return (array<int, 2>) {x / 365, 0};
    T.move_y();
    if (T.x >= 0 && T.y >= 0) return array<int, 2> {T.x, T.y};    
    return (array<int, 2>) {-1, -1}; 
  };

  while (z--) {
    int n; cin >> n;
    int ans = 0x3f3f3f3f3f3f3f3fll;
    for (int i = 0; i <= 11; i++) {
      array<int, 2> res = solve(n - i * 31);
      if (res[0] != -1) ans = min(res[0] + res[1] + i, ans);
    }

//    cout << 0x3f3f3f3f3f3f3f3fll << endl;
    if (ans == 0x3f3f3f3f3f3f3f3fll) cout << -1 << endl;
    else cout << ans << endl;
  }

  return 0;
}
