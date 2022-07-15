//
//  c.cpp
//  2022-07-14 00:21
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

const long long INF = 0x3f3f3f3f3f3f3f3f;
struct Segment_Tree {

  struct Info {
    long long sum, maxn, minn; 
    Info () { sum = 0, maxn = 0, minn = 0; }
  };

  struct Tree {
    int ls, rs; // 左儿子，右儿子 编号
    int l, r; // 左边界，右边界
    Info dat;
    Tree(int a, int b, int c, int d) : ls(a), rs(b), l(c), r(d) {} 
  };

  vector<Tree> tree; 

  Segment_Tree(int l, int r) {
    tree.push_back({-1, -1, l, r});
  }

  int insert(int l, int r) {
    tree.push_back({-1, -1, l, r});
    return (int) tree.size() - 1;
  }
 
  Info merge(Info a, Info b) {
    Info res;
    res.sum = a.sum + b.sum;
    res.maxn = max(a.maxn, b.maxn);
    res.minn = min(a.minn, b.minn);
    return res;
  }

  void add(int pos, int val) {
    tree[pos].dat.sum += val;
    tree[pos].dat.maxn += val;
    tree[pos].dat.minn += val;
  }

  void push_up(int pos) {
    tree[pos].dat.sum = 0; 
    tree[pos].dat.maxn = -INF;
    tree[pos].dat.minn = INF;
    if (tree[pos].ls != -1) tree[pos].dat = merge(tree[pos].dat, tree[tree[pos].ls].dat);
    if (tree[pos].rs != -1) tree[pos].dat = merge(tree[pos].dat, tree[tree[pos].rs].dat);
  }

  void modify(int pos, int goal, int val) {
    if (tree[pos].l == tree[pos].r) {
      add(pos, val);
      return;
    }
    int mid = (tree[pos].l + tree[pos].r) >> 1;
    if (goal <= mid) {
      if (tree[pos].ls == -1) tree[pos].ls = insert(tree[pos].l, mid);
      modify(tree[pos].ls, goal, val);
    } else {
      if (tree[pos].rs == -1) tree[pos].rs = insert(mid + 1, tree[pos].r);
      modify(tree[pos].rs, goal, val);
    }
    push_up(pos);
  }

  Info query(int pos, int l, int r) {
    if (tree[pos].l >= l && tree[pos].r <= r) {
      return tree[pos].dat;
    }
    int mid = (tree[pos].l + tree[pos].r) >> 1;
    Info res; res.maxn = -INF, res.minn = INF; //注意初始值

    if (l <= mid && tree[pos].ls != -1) {
      res = merge(res, query(tree[pos].ls, l, r));
    }
    if (r >= mid + 1 && tree[pos].rs != -1) {
      res = merge(res, query(tree[pos].rs, l, r));
    }
    push_up(pos);
    return res;
  }
};

struct BIT {
  vector<int> tree;
  int limit;
  BIT (int n) : tree(n + 1, 0), limit(n) {}

  inline int lowbit(int x) { return x & (-x); }

  void modify(int x, int val) { // 单点修改
    assert(x >= 1);
    while (x <= limit) {
      tree[x] = max(val, tree[x]);     
      x += lowbit(x);
    }
  }

  void init(int x) {
    assert(x >= 1);
    while (x <= limit) {
      tree[x] = 0;
      x += lowbit(x);
    }
  }

  int query(int x) {
    assert(x >= 0);
    int ans = 0;
    while (x) {
      ans = max(tree[x], ans);
      x -= lowbit(x);
    }
    return ans;
  }
};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int z; cin >> z; 
  while (z--) {
    int n; cin >> n;
    vector<array<int, 3>> a(n + 1); 
    vector<int> dis;
    for (int i = 1; i <= n; i++) {
      a[i][0] = i;
      cin >> a[i][1];
      dis.push_back(a[i][1]);
    }
    for (int i = 1; i <= n; i++) {
      cin >> a[i][2];
      dis.push_back(a[i][2]);
    }

    sort(dis.begin(), dis.end()); 
    dis.erase(unique(dis.begin(), dis.end()), dis.end());
    for (int i = 1; i <= n; i++) {
      a[i][1] = lower_bound(dis.begin(), dis.end(), a[i][1]) - dis.begin() + 1;
      a[i][2] = lower_bound(dis.begin(), dis.end(), a[i][2]) - dis.begin() + 1;
    }
    
    vector<int> dp(n + 1, 0);
    BIT T(dis.size());
    function<void(int, int)> CDQ = [&] (int l, int r) {
      if (l == r) {
        dp[l]++;
        return;
      }
      int mid = (l + r) >> 1;
      CDQ(l, mid); 

      sort(a.begin() + l, a.begin() + mid + 1, [&](auto i, auto j) { return i[1] < j[1]; });
      sort(a.begin() + mid + 1, a.begin() + r + 1, [&](auto i, auto j) { return i[1] < j[1]; });

      int p = l;
      for (int i = mid + 1; i <= r; i++) {
        while (p <= mid && a[p][1] < a[i][1]) {
          T.modify(a[p][2], dp[a[p][0]]);
          p++;
        }
        if (a[i][2] != 1) {
          dp[a[i][0]] = max(dp[a[i][0]], T.query(a[i][2] - 1));
        }
      }

      for (int i = l; i < p; i++) {
        T.init(a[i][2]);
      }

      sort(a.begin() + l, a.begin() + mid + 1);
      sort(a.begin() + mid + 1, a.begin() + r + 1);
      CDQ(mid + 1, r);
    };
    
    CDQ(1, n);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      ans = max(ans, dp[i]);
    }
    cout << ans << endl;
  }
  return 0;
}
