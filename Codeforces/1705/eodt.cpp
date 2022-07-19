//
//  eodt.cpp
//  2022-07-16 00:22
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


// 珂朵莉树
// 1. 记住 split 返回包含x的右半区间
// 2. split 的 x 只能在初始化的范围内

struct ODT {
  struct Node {
    int l, r;
    mutable int val;
    Node(const int &a, const int &b, const int &c) : l(a), r(b), val(c) {}
    bool operator < (const Node & oth) const { return l < oth.l; }
  };

  set<Node> odt;

  ODT(int l, int r, int val) {
    odt.insert({l, r, val}); 
  }

  // 把包含 x 的区间 split 成[l, x) [x, r], 返回 [x, r]
  auto split(int x) { 
    auto it = --odt.upper_bound((Node) {x, 0, 0});
    if (it->l == x) return it;
    int l = it->l, r = it -> r, val = it->val;
    odt.erase(it);
    odt.insert((Node) {l, x - 1, val});
    return odt.insert((Node) {x, r, val}).first;
  }

  // split 必须先右后左, 因为 split 右端点可能会让已经 split 的左端点失效
  void assign(int l, int r, int val) {
    auto itr = split(r + 1);  
    auto itl = split(l);
    odt.erase(itl, itr);
    odt.insert((Node) {l, r, val});
  }

  void add(int x) {
    auto it = split(x);    
    while (it->val == 1) it++;
    int l = it->l;
    if (x <= l - 1) assign(x, l - 1, 0); 
    assign(l, l, 1);
  }

  void sub(int x) {
    auto it = split(x);    
    while (it->val == 0) it++;
    int l = it->l;
    if (x <= l - 1) assign(x, l - 1, 1); 
    assign(l, l, 0);
  }

  int query() {
    auto it = odt.end();
    it--;
    int limit = it->r;
    while (it->val == 0) {
      it--;
    }
    assign(it->r + 1, limit, 0);
    return it->r;
  }
};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int n, q; cin >> n >> q; 
  
  vector<int> a(n + 1);   
  for (int i = 1; i <= n; i++) {
    cin >> a[i];  
  }

  ODT T(0, 2e5 + 100, 0);

  for (int i = 1; i <= n; i++) {
    T.add(a[i]);
  }

  for (int i = 1; i <= q; i++) {
    int pos, val; cin >> pos >> val;
    T.sub(a[pos]); 
    a[pos] = val;
    T.add(a[pos]);
    cout << T.query() << endl; 
  } 

  return 0;
}
