//
//  g.cpp
//  2022-06-07 23:49
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
#endif
}
struct Node {
    int l, r;
    mutable int val;
    Node(const int &a, const int &b, const int &c) : l(a), r(b), val(c) {}
    bool operator < (const Node & oth) const {
        return l < oth.l;
    }
};

struct ODT {
    set<Node> odt;
    int n;
    ODT(int _n) : n(_n) {
      odt.insert({1, _n, 0x3f3f3f3f});
    } 

    auto split(int x) { // n 可以考虑去掉，让ODT可以处理大区间
        if (x > n) return odt.end();
        auto it = --odt.upper_bound((Node) {x, 0, 0});
        if (it->l == x) return it;
        int l = it->l, r = it -> r, val = it->val;
        odt.erase(it);
        odt.insert((Node) {l, x - 1, val});
        return odt.insert((Node) {x, r, val}).first;
    }

    void assign(int l, int r, int val) {
        auto itr = split(r + 1);  // 必须先右后左, 因为split右端点会让已经split的左端点失效
        auto itl = split(l);
        odt.erase(itl, itr);
        odt.insert((Node) {l, r, val});
    }

    int query(int k) {
      auto it = split(k);
      int val = it->val;
      int r = it->r, l;
      if (it == odt.begin()) l = k;
      else {
        it--;
        if (it->val == val) {
          l = it->l;
        } else {
          l = k;
        }
      }
      assign(l, r, val);
      return val;
    }
    void solve(int k, int d) {
      auto itr = split(k);
      int val = itr->val - d; 

      while (itr != odt.end() && itr->val >= val) {
        itr++;
      }

      int l, r; 
      if (itr == odt.end()) {
        l = k, r = n;
      } else {
        l = k, r = itr->l - 1;
      }
      assign(l, r, val);
    }
};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z;  
  while (z--) {
    int n, m; cin >> n >> m;
    ODT T(n);
    const int INF = 0x3f3f3f3f;
    vector<int> init(n + 1, INF), a;
    for (int i = 1; i <= n; i++) cin >> init[i];
    a = init;
    for (int i = 1; i <= n; i++) {
      a[i] = min(a[i - 1], a[i]);
    }
    int last = 1;
    for (int i = 2; i <= n; i++) {
      if (a[i] != a[i - 1]) {
        T.assign(last, i - 1, a[i - 1]);
        last = i;
      }
    }
    T.assign(last, n, a[n]);
    for (int i = 1; i <= m; i++) {
      int k, d; cin >> k >> d;  
      init[k] -= d;
      int val = T.query(k); 
      if (init[k] < val) {
        T.solve(k, val - init[k]);
      } 
      cout << T.odt.size() << " ";
    }
    cout << endl;
  }
   
  return 0;
}
