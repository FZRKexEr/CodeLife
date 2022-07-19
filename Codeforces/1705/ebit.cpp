//
//  ebit.cpp
//  2022-07-16 00:58
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long

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


// 树状数组
// 1. 支持 区间add，区间查询 sum
// 2. 不要用 modify 和 query (避免误用)
// 3. 用 add 函数和 get_sum 函数 修改和查询
// 4. 下标必须从1开始
// 5. 复杂度 O(nlogn)

struct BIT {
  vector<array<long long, 2>> tree; 
  int limit;

  BIT(int n) : tree(n + 1, {0ll, 0ll}), limit(n) {}

  inline int lowbit(int x) {
    return x & (-x);
  }

  void modify(int x, long long v1) {
    assert(x >= 1);
    long long v2 = v1 * x;
    while (x <= limit) {
      tree[x][0] += v1;
      tree[x][1] += v2;
      x += lowbit(x);
    }
  }

  long long query(int x) {
    assert(x >= 0);
    long long ans = 0ll;
    int backup = x;
    while (x) {
      ans -= tree[x][1];
      ans += 1ll * (backup + 1) * tree[x][0];
      x -= lowbit(x);
    }
    return ans;
  }

  void add(int l, int r, long long val) {
    modify(l, val);
    modify(r + 1, -val);
  }

  long long get_sum(int l, int r) {
    return query(r) - query(l - 1);
  }
};


signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int n, q;    
  cin >> n >> q;

  BIT T(2e5 + 20);  

  const int limit = 2e5 + 20;

  auto add = [&] (int x) {
    if (T.get_sum(x, x) == 0) {
      T.add(x, x, 1);
      return;
    }
    int l = x, r = limit; 
    while (l <= r) {
      int mid = (l + r) / 2;
      if (T.get_sum(x, mid) != (mid - x + 1)) r = mid - 1;  
      else l = mid + 1;
    }
    T.add(l, l, 1); 
    if (x <= l - 1)
      T.add(x, l - 1, -1);
  };
  
  auto sub = [&] (int x) {
    if (T.get_sum(x, x) == 1) {
      T.add(x, x, -1);
      return;
    }
    int l = x, r = limit; 
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (T.get_sum(x, mid) != 0) r = mid - 1; 
      else l = mid + 1;
    }
    T.add(l, l, -1);
    if (x <= l - 1)
      T.add(x, l - 1, 1);
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

  for (int i = 1; i <= 2e5 + 20; i++) {
    T.add(i, i, cnt[i]);
  }


  for (int i = 1; i <= q; i++) {
    int pos, val; cin >> pos >> val;

    sub(a[pos]);
    a[pos] = val;
    add(a[pos]);

    int l = 1, r = limit;  
    while (l <= r) {
      int mid = (l + r) >> 1;  
      if (T.get_sum(mid, r) != 0) l = mid + 1;
      else r = mid - 1;
    }
    cout << r << endl;
  }

  return 0;
}
