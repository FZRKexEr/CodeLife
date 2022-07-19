//
//  P3960.cpp
//  2022-07-18 00:24
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#define LOCAL
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

struct BIT2d{
  vector<vector<array<long long, 4>>> tree;
  int maxn, maxm;

  BIT2d(int n, int m) : tree(n + 1, vector<array<long long, 4>> (m + 1, {0ll, 0ll, 0ll, 0ll})), maxn(n), maxm(m){}

  inline int lowbit(int x) {
    return x & (-x);
  }

  void modify(int x, int y, long long val) {
    assert(x > 0 && y > 0);
    for (int k = x; k <= maxn; k += lowbit(k)) {
      for (int l = y; l <= maxm; l += lowbit(l)) {
        tree[k][l][0] += val;
        tree[k][l][1] += x * val;
        tree[k][l][2] += y * val;
        tree[k][l][3] += x * y * val;
      }
    }
  }

  long long query(int x, int y) {
    assert(x >= 0 && y >= 0);
    long long ans = 0ll;
    for (int i = x; i > 0; i -= lowbit(i)) {
      for (int j = y; j > 0; j -= lowbit(j)) {
        ans += 1ll * (x + 1) * (y + 1) * tree[i][j][0];
        ans -= 1ll * (y + 1) * tree[i][j][1];
        ans -= 1ll * (x + 1) * tree[i][j][2];
        ans += 1ll * tree[i][j][3];
      }
    }
    return ans;
  }
  // 左上 右下
  void add(int x1, int y1, int x2, int y2, long long val) {
    modify(x1, y1, val);  
    modify(x2 + 1, y1, -val);
    modify(x1, y2 + 1, -val);
    modify(x2 + 1, y2 + 1, val);
  }

  // 左上 右下
  long long get_sum(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
  }
};

struct Treap {
  struct Node {
    int l, r; 
    int key, pri, size;
    int lazy;
    Node (int a, int b) : key(a), pri(b) { 
      l = r = -1, size = 1, lazy = 0; 
    }
  };

  vector<Node> tree; 
  vector<int> root; 
  int seed = 1;
  
  Treap(int n) : root(n + 1, -1) {} 

  void push_down(int pos) {
    
  }
  
  array<int, 2> split(int pos, int key) {
    if (pos == -1) return {-1, -1};
    push_down(pos);
    if (tree[pos].key <= key) {
      array<int, 2> res = split(tree[pos].r, key);
      tree[pos].r = res[0];
      update(pos);
      return {pos, res[1]};
    } else {
      array<int, 2> res = split(tree[pos].l, key);
      tree[pos].l = res[1]; 
      update(pos);
      return {res[0], pos};
    }
  }

  array<int, 2> split_sz(int pos, int sz) {
    if (pos == -1) return {-1, -1};
    push_down(pos);
    int lsize = tree[pos].l == -1 ? 1 : tree[tree[pos].l].size + 1;
    if (lsize <= sz) {
      array<int, 2> res = split_sz(tree[pos].r, sz - lsize);
      tree[pos].r = res[0];
      update(pos);
      return {pos, res[1]};
    } else {
      array<int, 2> res = split_sz(tree[pos].l, sz); 
      tree[pos].l = res[1];
      update(pos);
      return {res[0], pos};
    }
  }

  int merge(int x, int y) {
    if (x == -1) return y;
    if (y == -1) return x;
    if (tree[x].pri < tree[y].pri) {
      push_down(x);
      tree[x].r = merge(tree[x].r, y);  
      update(x);
      return x;
    } else {
      push_down(y);
      tree[y].l = merge(x, tree[y].l); 
      update(y);
      return y;
    }
  }

  int merge_treap(int x, int y) {
    if (x == -1) return y;
    if (y == -1) return x;
    push_down(x), push_down(y);
    if (tree[x].pri > tree[y].pri) swap(x, y);
    array<int, 2> res = split(y, tree[x].key);
    tree[x].l = merge_treap(tree[x].l, res[0]);
    tree[x].r = merge_treap(tree[x].r, res[1]);
    update(x);
    return x;
  }

  vector<int> output(int pos) {
    if (pos == -1) return {};
    push_down(pos);
    vector<int> res;
    vector<int> l = output(tree[pos].l), r = output(tree[pos].r);
    res.insert(res.end(), l.begin(), l.end());
    res.push_back(tree[pos].key);
    res.insert(res.end(), r.begin(), r.end());
    return res;
  }

  void update(int pos) {
    if (pos == -1) return;
    tree[pos].size = 1;
    if (tree[pos].l != -1) tree[pos].size += tree[tree[pos].l].size;
    if (tree[pos].r != -1) tree[pos].size += tree[tree[pos].r].size;
  }

  int func_rand() {
    return seed *= 19260817;
  }

  int create(int key) {
    tree.emplace_back(key, func_rand());
    return (int) tree.size() - 1;
  }
  
  void insert(int &pos, int key) {
    int o = create(key);
    array<int, 2> res = split(pos, key);
    pos = merge(merge(res[0], o), res[1]); 
  }

  int rank(int &pos, int key) {
    array<int, 2> res = split(pos, key - 1);
    int rk = (res[0] == -1) ? 1 : tree[res[0]].size + 1;
    pos = merge(res[0], res[1]);
    return rk;
  }

  int kth(int pos, int k) {
    while (pos != -1) {
      int lsize = tree[pos].l == -1 ? 1 : tree[tree[pos].l].size + 1;
      if (lsize == k) return tree[pos].key; 
      if (k < lsize) pos = tree[pos].l;
      if (k > lsize) pos = tree[pos].r, k -= lsize;
    }
    assert(0);
  }

  void erase(int &pos, int key) {
    array<int, 2> res1 = split(pos, key); 
    array<int, 2> res2 = split(res1[0], key - 1); 
    if (res2[1] != -1) {
      res2[1] = merge(tree[res2[1]].l, tree[res2[1]].r);
    }
    pos = merge(merge(res2[0], res2[1]), res1[1]);
  }

  int pre(int &pos, int key) {
    array<int, 2> res = split(pos, key - 1); 
    if (res[0] == -1) return -1;
    int ans = kth(res[0], tree[res[0]].size);
    pos = merge(res[0], res[1]);
    return ans;
  }

  int nxt(int &pos, int key) {
    array<int, 2> res = split(pos, key);
    if (res[1] == -1) return -1;
    int ans = kth(res[1], 1);
    pos = merge(res[0], res[1]);
    return ans;
  }

  int count(int &pos, int key) {
    array<int, 2> res1 = split(pos, key);
    array<int, 2> res2 = split(res1[0], key - 1);
    int ans = res2[1] == -1 ? 0 : tree[res2[1]].size;
    pos = merge(merge(res2[0], res2[1]), res1[1]);
    return ans;
  }
};

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
    if (r < l) return 0;
    return query(r) - query(l - 1);
  }
};

signed main() {
  freopen("in.txt", "r", stdin);
  ios::sync_with_stdio(false); 
  cin.tie(0);
     
  int n, m, q; cin >> n >> m >> q;

  vector<array<int, 2>> ask(q + 1);
  vector<vector<array<int, 2>>> div(n + 1);
  vector<int> res(q + 1, 0);

  for (int i = 1; i <= q; i++) {
    cin >> ask[i][0] >> ask[i][1];
    div[ask[i][0]].push_back({ask[i][1], i});
  }
  
  for (int i = 1; i <= n; i++) {
    vector<int> dis;  
    for (int j = 0; j < (int) div[i].size(); j++) {
      dis.push_back(div[i][j][0]);
    }
    sort(dis.begin(), dis.end());
    dis.erase(unique(dis.begin(), dis.end()), dis.end()); 
    BIT T((int) dis.size() + 1);
    for (int j = 0; j < (int) div[i].size(); j++) {
      int o1 = lower_bound(dis.begin(), dis.end(), div[i][j][0]) - dis.begin() + 1;      
      int val1 = T.get_sum(1, o1);
      int o2 = upper_bound(dis.begin(), dis.end(), div[i][j][0] + val1) - dis.begin() - 1 + 1;
      int val2 = T.get_sum(o1 + 1, o2);
      res[div[i][j][1]] = val1 + val2;
      T.add(o1, o1, 1);
    }
  }

  Treap T(1);

  auto get_num = [&](int x, int y) {
    return (x - 1) * m + y;
  };

  vector<int> add = {-1};
  vector<vector<int>> que(n + 1); 

  for (int i = 1; i <= n; i++) {
    T.insert(T.root[1], i);
    add.push_back(get_num(i, m));
  }

  for (int i = 1; i <= q; i++) {
    que[ask[i][0]].push_back(add[T.kth(T.root[1], ask[i][0])]);

    int pos = ask[i][1] + res[i];
    debug(pos);

    int ans;
    if (pos <= m - 1) {
      ans = get_num(ask[i][0], pos);
    } else {
      ans = que[ask[i][0]][pos - m];
    }

    int ord = T.kth(T.root[1], ask[i][0]);

    T.erase(T.root[1], ord);
    T.insert(T.root[1], (int) add.size());
    add.push_back(ans);
    cout << ans << endl;
  }
  return 0;
}
