//
//  d.cpp
//  2022-06-25 23:13
//
//  Created by liznb
//  

#include <bits/stdc++.h>
//#define int long long
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

int START_TIME = -1;
void file() {
#ifndef ONLINE_JUDGE
  START_TIME = clock();
  freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
#endif
}
void Timer() {
#ifndef ONLINE_JUDGE
  if (START_TIME != -1)
    cout << endl << 1.0 * (clock() - START_TIME) / CLOCKS_PER_SEC << "s";
#endif
}

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
    long long sum, maxi, mini; 
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
    res.maxi = max(a.maxi, b.maxi);
    res.mini = min(a.mini, b.mini);
    return res;
  }

  void build(int pos, int l, int r, vector<int> &arr) {
    tl = l; tr = r;    
    lazy[pos] = 0ll;

    int m = l + (r - l) / 2;
    if (l == r) {
      tv.sum = arr[l]; 
      tv.maxi = arr[l];
      tv.mini = arr[l];
      return;
    } 
    build(pos << 1, l, m, arr);
    build(pos << 1 | 1, m + 1, r, arr);
    tv = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  }

  // 对树上一个位置进行修改
  void add(int pos, long long val) {
    lazy[pos] = val;
    tv.sum = (tr - tl + 1) * val;
    tv.maxi = val;
    tv.mini = val;
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
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  
  int z; cin >> z; 
  while (z--) {
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    
    auto sol = [&](vector<int> arr) {
      vector<array<int, 2>> maxn, minn; 
      Segment_Tree dp_max(n), dp_min(n);
      vector<int> b(n + 1, 0x3f3f3f3f);

      dp_max.build(1, 1, n, b);
      dp_min.build(1, 1, n, b);
      
      maxn.push_back({a[1], 1});
      minn.push_back({a[1], 1});
      dp_max.modify(1, 1, 1, 0);
      dp_min.modify(1, 1, 1, 0);

      vector<int> ans(n + 1, 0x3f3f3f3f);
      ans[1] = 0;
      for (int i = 2; i <= n; i++) {
        array<int, 2> nw = {a[i], i};
        while (!maxn.empty() && maxn.back() < nw) {
          dp_max.modify(1, maxn.back()[1], maxn.back()[1], 0x3f3f3f3f);
          maxn.pop_back();
        }
        while (!minn.empty() && minn.back() > nw) {
          dp_min.modify(1, minn.back()[1], minn.back()[1], 0x3f3f3f3f);
          minn.pop_back();
        }
        int l;
        if (minn.empty()) l = 1;
        else l = minn.back()[1] + 1;
        
        if (l <= i - 1) ans[i] = dp_max.query(1, l, i - 1).mini + 1;
        
        if (maxn.empty()) l = 1;
        else l = maxn.back()[1] + 1;

        if (l <= i - 1) ans[i] = dp_min.query(1, l, i - 1).mini + 1;

        maxn.push_back(nw);
        minn.push_back(nw);
        dp_max.modify(1, i, i, ans[i]);
        dp_min.modify(1, i, i, ans[i]);
      }
      return ans[n];
    };
    int res1 = sol(a);
    cout << res1 << endl;
  }


  Timer();
  return 0;
}
