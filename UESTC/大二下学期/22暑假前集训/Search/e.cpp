//
//  e.cpp
//  2022-06-10 20:53
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define LOCAL
using namespace std;

#ifdef ONLINE_JUDGE
#ifndef LOCAL_TEST
#pragma GCC optimize("O3","unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif
#endif

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

random_device rd; 
mt19937 seed(rd());
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
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


/*
 * 关于权值线段树:
 * 1. 经典问题：求数列第K大（区间第K大用可持久化线段树）
 * 关于动态开点：
 * 1. 能不用就不用，能离散化就离散化
 * 2. 已知用处：可持久化数据结构，线段树合并，强制在线不能离散化的题。
 * 模板特性：
 * 1. 只支持单点修改，区间查询。(反过来也行，不支持lazy标记)
 * 2. 如果问题能用普通线段树解决，就不要用这个。空间复杂度 Knlogn（K是大常数）
 * 3. 支持负数权值
 * 4. 不用 #define int long long 可以保证 long long 内结果正确
 * 5. !!!!! pos 是 0-indexed !!!!
 * 6. !!!!!! 单点覆盖时，注意这个点存不存在！，存在时才能用 -old_val + new_val 覆盖,否则直接 new_val
 * 优化：
 * 1. 模板内置了 sum，maxn，minn。可以根据题目要求删除一些，减少空间消耗。
 * 2. 还可以进一步优化空间：把 l 和 r 也删掉，直接在函数里传参
 * 3. 参考：逆序对问题：n = 5e5, 数值范围 1e9, 做了1，2优化后消耗 75mb 空间。
 */

const long long INF = 0x3f3f3f3f3f3f3f3f;
struct Segment_Tree {

  struct Info {
    long long maxn, minn; 
    Info () { maxn = 0, minn = 0; }
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
    res.maxn = max(a.maxn, b.maxn);
    res.minn = min(a.minn, b.minn);
    return res;
  }

  void add(int pos, int val) {
    tree[pos].dat.maxn += val;
    tree[pos].dat.minn += val;
  }

  void push_up(int pos) {
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
signed main() {
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, k; cin >> n >> k; 
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  map<int, int> has;
  for (int i = 0; i < k; i++) {
    cin >> b[i];
    has[b[i]] = 1;
  }
  
  Segment_Tree Tl(1, n), Tr(1, n);
  
  vector<int> L(n), R(n);
  for (int i = 0; i < n; i++) {
    if (has[a[i]]) {
      Tl.modify(0, a[i], i);
    } else {
      L[i] = Tl.query(0, 1, a[i]).maxn;
      if (L[i] == -INF) L[i] = -1;
    }
  }
  for (int i = n - 1; i >= 0; i--) {
    if (has[a[i]]) {
      Tr.modify(0, a[i], i);
    } else {
      R[i] = Tr.query(0, 1, a[i]).minn;
      if (R[i] == INF) R[i] = n;
    }
  }
  map<int, int> pos;
  for (int i = 0; i < k; i++) {
    pos[b[i]] = i;  
  }
  int ans = 0;
  int posi = -1;
  for (int i = 0; i < n; i++) {
    if (has[a[i]]) {
      posi++; 
      continue;
    }
    int res = R[i] - 1 - (L[i] + 1) + 1;
    ans += res;
  }
  cout << ans;

   
  return 0;
}
