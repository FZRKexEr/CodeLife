//
//  f.cpp
//  2022-07-08 14:16
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

mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> U(1, 1000000000ll);

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

int START_TIME = -1;
void file() {
#ifndef ONLINE_JUDGE
  START_TIME = clock();
#endif
}
void Timer() {
#ifndef ONLINE_JUDGE
  if (START_TIME != -1)
    cout << endl << 1.0 * (clock() - START_TIME) / CLOCKS_PER_SEC << "s";
#endif
}

struct Segment_Tree3 {
  
  struct Info {
    int sum;  // 一定考虑初始值在 insert 后且不 modify 时是否不影响 query
              // 例如 sum = 0, minn = INF, maxn = -INF
              // 也就是说可持续化线段树里会有废点，不能让这些点影响答案，(权值线段树里不会有, insert 后必 modify)
    int sum_a, sum_b;
    Info () { 
      sum = 0; 
      sum_a = 0;
      sum_b = 0;
    }
  };

  struct Tree {
    int ls, rs; // 左儿子，右儿子 编号
    int l, r; // 左边界，右边界
    Info dat;
    Tree(int a, int b, int c, int d) : ls(a), rs(b), l(c), r(d) {} 
  };

  vector<Tree> tree; 
  vector<int> ver;

  Segment_Tree3(int l, int r) {
    tree.push_back({-1, -1, l, r});
    ver.push_back((int) tree.size() - 1);
  }
 
  int add_ver(int l, int r) {
    tree.push_back({-1, -1, l, r}); 
    ver.push_back((int) tree.size() - 1);
    return (int) tree.size() - 1;
  }

  int insert(int l, int r) {
    tree.push_back({-1, -1, l, r});
    return (int) tree.size() - 1;
  }
 
  Info merge(const Info &a, const Info &b) {
    Info res;
    res.sum = a.sum + b.sum;
    res.sum_a = a.sum_a + b.sum_a;
    res.sum_b = a.sum_b + b.sum_b;
    return res;
  }

  void add(int pos, int goal, int val) {
    tree[pos].dat.sum += val;
    if (val >= 2) tree[pos].dat.sum_a += 1;
    if (val <= 0) tree[pos].dat.sum_b += 1;
  }

  void push_up(int pos) {
    tree[pos].dat.sum = 0; 
    tree[pos].dat.sum_a = 0;
    tree[pos].dat.sum_b = 0;
    if (tree[pos].ls != -1) tree[pos].dat = merge(tree[pos].dat, tree[tree[pos].ls].dat);
    if (tree[pos].rs != -1) tree[pos].dat = merge(tree[pos].dat, tree[tree[pos].rs].dat);
  }

  // 可持续化修改，插入单点  
  void pmodify(int base, int pos, int goal, int val) {
    if (tree[pos].l == tree[pos].r) {
      tree[pos].dat = tree[base].dat;  
      add(pos, goal, val);
      return;        
    }
    int mid = (tree[pos].l + tree[pos].r) >> 1;
    if (goal <= mid) {
      tree[pos].rs = tree[base].rs;
      tree[pos].ls = insert(tree[pos].l, mid);
      if (tree[base].ls == -1) tree[base].ls = insert(tree[base].l, mid); 
      pmodify(tree[base].ls, tree[pos].ls, goal, val);
    } else {
      tree[pos].ls = tree[base].ls;
      tree[pos].rs = insert(mid + 1, tree[pos].r);
      if (tree[base].rs == -1) tree[base].rs = insert(mid + 1, tree[base].r);
      pmodify(tree[base].rs, tree[pos].rs, goal, val);
    }
    push_up(pos);
  }


  Info query(int pos, int l, int r) {
    if (tree[pos].l >= l && tree[pos].r <= r) {
      return tree[pos].dat;
    }
    int mid = (tree[pos].l + tree[pos].r) >> 1;
    Info res;  //注意初始值

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
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n; cin >> n;

  vector<int> a(n + 1), d(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  Segment_Tree3 T3(1, n);
  for (int i = 1; i <= n; i++) {
    T3.add_ver(1, n);
    T3.pmodify(T3.ver[i - 1], T3.ver[i], a[i], 1);
  }

  int ans = 0;

  auto get_A = [&](int pos, int val) {
    if (val == 1) return 0ll;
    if (pos == 1) return 0ll;
    return T3.query(T3.ver[pos - 1], 1, val - 1).sum - T3.query(T3.ver[0], 1, val - 1).sum;
  };
  
  auto get_B = [&](int pos, int val) {
    if (val == 1) return 0ll;
    if (pos == n) return 0ll;
    return T3.query(T3.ver[n], 1, val - 1).sum - T3.query(T3.ver[pos], 1, val - 1).sum;
  };

  vector<int> minAB(n + 1);
  for (int i = 1; i <= n; i++) {
    int A = get_A(i, a[i]), B = get_B(i, a[i]);
    d[i] = A - B;
    minAB[i] = min(A, B);
    ans += minAB[i];
  }

  Segment_Tree3 T1(1, n), T2(1, n);
  for (int i = 1; i <= n; i++) {
    T1.add_ver(1, n);       
    T1.pmodify(T1.ver[i - 1], T1.ver[i], a[i], d[i]);
    T2.add_ver(1, n);
    T2.pmodify(T2.ver[i - 1], T2.ver[i], a[i], -d[i]);
  }

  int q; cin >> q;

  for (int i = 1; i <= q; i++) {
    int l, r; cin >> l >> r;
    if (l > r) swap(l, r);
    if (l == r) {
      cout << ans << endl;
      continue;
    }
    int res = ans;
    res -= minAB[l];
    res -= minAB[r];
    
    if (a[l] < a[r]) { 
      res += min(get_A(r, a[l]), get_B(r, a[l]));    
      res += min(get_A(l, a[r]), get_B(l, a[r]) + 1);
    } else {
      res += min(get_A(r, a[l]) + 1, get_B(r, a[l]));    
      res += min(get_A(l, a[r]), get_B(l, a[r]));
    }
    

    if (l == r - 1 || abs(a[l] - a[r]) == 1) {
      cout << res << endl;
      continue;
    }

    if (a[l] < a[r]) {
      auto rr = T1.query(T1.ver[r - 1], a[l] + 1, a[r] - 1);
      auto ll = T1.query(T1.ver[l], a[l] + 1, a[r] - 1);
      int sum_a = rr.sum_a - ll.sum_a;
      int sum_b = rr.sum_b - ll.sum_b;
      res += sum_a; 
      res -= sum_b;
    } else {
      auto rr = T2.query(T2.ver[r - 1], a[r] + 1, a[l] - 1);
      auto ll = T2.query(T2.ver[l], a[r] + 1, a[l] - 1);
      int sum_a = rr.sum_a - ll.sum_a;
      int sum_b = rr.sum_b - ll.sum_b;
      res += sum_a; 
      res -= sum_b;
    }
    cout << res << endl;
  }

  Timer();
  return 0;
}
