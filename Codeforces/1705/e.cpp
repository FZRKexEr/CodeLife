//
//  e.cpp
//  2022-07-15 22:25
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

// 先build！先build！先build！
// 修改：区间加法
// 查询：区间和，最大值，最小值
// 修改模板顺序：
// 0. 如果是单点修改，可以删除 lazy 数组 和 push_down, 也可以不删
// 1. Info 结构体
// 2. build 函数
// 3. merge 函数
// 4. add 函数
// 5. push_down 函数 
// modify 和 query 不需要修改！

struct Segment_Tree {
  
  #define tl tree[pos].l 
  #define tr tree[pos].r 
  #define tv tree[pos].val
  struct Info {
    long long sum; 
  };

  struct Tree {
    int l, r; 
    Info val;
  };  
  vector<Tree> tree;
  vector<long long> lazy;

  Segment_Tree(int n) {
    tree.resize(n * 4 + 10);  
    lazy.resize(n * 4 + 10);
  }

  // 合并两个儿子
  Info merge(Info a, Info b) {
    Info res;
    res.sum = a.sum + b.sum;
    return res;
  }

  void build(int pos, int l, int r, vector<int> &arr) {
    tl = l; tr = r;    
    lazy[pos] = 0ll;

    int m = l + (r - l) / 2;
    if (l == r) {
      tv.sum = arr[l]; 
      return;
    } 
    build(pos << 1, l, m, arr);
    build(pos << 1 | 1, m + 1, r, arr);
    tv = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  }

  // 对树上一个位置进行修改
  void add(int pos, long long val) {
    lazy[pos] += val;
    tv.sum += (tr - tl + 1) * val;
  }

  // 传递懒人标记
  void push_down(int pos) {
    if (lazy[pos] == 0) return; 
    add(pos << 1, lazy[pos]); 
    add(pos << 1 | 1, lazy[pos]);
    lazy[pos] = 0;
  } 

  void modify(int pos, int l, int r, long long val) {
    if (tl >= l && tr <= r) {
      add(pos, val);
      return;
    }  
    push_down(pos);
    int m = tl + (tr - tl) / 2;
    if (l <= m) modify(pos << 1, l, r, val);
    if (r > m) modify(pos << 1 | 1, l, r, val);
    tv = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  } 

  Info query(int pos, int l, int r) {
    if (tl >= l && tr <= r) {
      return tv;
    }   
    push_down(pos);
    int m = tl + (tr - tl) / 2;
    Info res;

    if (l <= m && r > m) {
      res = merge(query(pos << 1, l, r), query(pos << 1 | 1, l , r));
    } else if (l > m) {
      res = query(pos << 1 | 1, l, r);
    } else if (r <= m) {
      res = query(pos << 1, l, r);
    }

    tv = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
    return res;
  }
  #undef tl
  #undef tr
  #undef tv
};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int n, q;    
  cin >> n >> q;

  Segment_Tree T(2e5 + 20);  

  const int limit = 2e5 + 20;

  auto add = [&] (int x) {
    if (T.query(1, x, x).sum == 0) {
      T.modify(1, x, x, 1);
      return;
    }
    int l = x, r = limit; 
    while (l <= r) {
      int mid = (l + r) / 2;
      if (T.query(1, x, mid).sum != (mid - x + 1)) r = mid - 1;  
      else l = mid + 1;
    }
    T.modify(1, l, l, 1); 
    if (x <= l - 1)
      T.modify(1, x, l - 1, -1);
  };
  
  auto sub = [&] (int x) {
    if (T.query(1, x, x).sum == 1) {
      T.modify(1, x, x, -1);
      return;
    }
    int l = x, r = limit; 
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (T.query(1, x, mid).sum != 0) r = mid - 1; 
      else l = mid + 1;
    }
    T.modify(1, l, l, -1);
    if (x <= l - 1)
      T.modify(1, x, l - 1, 1);
  };
  

  vector<int> a(n + 1);
  vector<int> cnt(2e5 + 100, 0);
  
  for (int i = 1; i <= n; i++) {
    cin >> a[i];  
    cnt[a[i]]++;
  }

  
  for (int i = 1; i <= 2e5 + 20; i++) {
    cnt[i + 1] += cnt[i] / 2;
    cnt[i] %= 2;
  }

  T.build(1, 1, 2e5 + 20, cnt);


  for (int i = 1; i <= q; i++) {
    int pos, val; cin >> pos >> val;

    sub(a[pos]);
    a[pos] = val;
    add(a[pos]);

    int l = 1, r = limit;  
    while (l <= r) {
      int mid = (l + r) >> 1;  
      if (T.query(1, mid, r).sum != 0) l = mid + 1;
      else r = mid - 1;
    }
    cout << r << endl;
  }

  return 0;
}
