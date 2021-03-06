//
//  i.cpp
//  2022-07-08 13:06
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
// ??????:
// 1. ??? int ??????????????????(??????????????????)?????????????????? #define int long long
// 2. ????????????????????? 1 indexed????????? string ??? 0 indexed
// 3. ?????????O(n), ???????????? hash O(1), ??????????????? len ???????????? O(len) 
// 4. ???????????????????????????
// 5. ?????????????????????: ????????? 1e6 ?????????????????? 0.001, ????????? 1e6 ?????????????????? 0.000001  

struct Hash {
  const array<int, 2> MOD = {127657753, 987654319};
  
  const array<int, 2> P = {137, 277};

  int n;
  string s; // 0 - indexed
  vector<array<int, 2>> hs; // 1 - indexed
  vector<array<int, 2>> pw; // 0 - indexed

  Hash(string _s) {
    assert(_s.length());
    n = _s.length(); 
    s = _s; 
    hs.resize(n + 1);
    pw.resize(n + 1);
    
    pw[0] = {1, 1};
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < 2; j++) {
        pw[i][j] = 1ll * pw[i - 1][j] * P[j] % MOD[j];
      }
    }
    hs.resize(n + 1, {0, 0}); 
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 2; j++) {
        hs[i + 1][j] = (1ll * hs[i][j] * P[j] % MOD[j] + s[i]) % MOD[j];
      }
    }
  }

  void add(string _s) {
    assert(_s.length());
    int old_n = n;
    n += _s.length(); 
    s += _s;
    hs.resize(n + 1);
    pw.resize(n + 1);
    for (int i = old_n + 1; i <= n; i++) {
      for (int j = 0; j < 2; j++) {
        pw[i][j] = 1ll * pw[i - 1][j] * P[j] % MOD[j];
      }
    }
    hs.resize(n + 1, {0, 0}); 
    for (int i = old_n; i < n; i++) {
      for (int j = 0; j < 2; j++) {
        hs[i + 1][j] = (1ll * hs[i][j] * P[j] % MOD[j] + s[i]) % MOD[j];
      }
    }
  }

  array<int, 2> get_hash(int l, int r) { // 1 - indexed
    assert(1 <= l && l <= r && r <= n); 
    array<int, 2> ans;
    for (int i = 0; i < 2; i++) {
      ans[i] = (hs[r][i] - 1ll * hs[l - 1][i] * pw[r - l + 1][i] % MOD[i] + MOD[i]) % MOD[i];
    }
    return ans;
  }
};

signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  
  int n, m; cin >> n >> m;   
  string s; cin >> s;
  string t = s;
  reverse(t.begin(), t.end());
  
  Hash S(s), T(t);
  
  auto check = [&] (int l, int r) {
    auto res1 = S.get_hash(l, r);      
    int tl = n - r + 1;
    int tr = n - l + 1;
    auto res2 = T.get_hash(tl, tr);
    if (res1 == res2) return true;
    return false;
  };
  
  for (int i = 1; i <= m; i++) {
    int l, r; cin >> l >> r;
    if (check(l, r)) {
      cout << "Budada" << endl;
    } else if ((r - l + 1) % 2 == 0) {
      cout << "Budada" << endl;
    } else {
      cout << "Putata" << endl;
    }
  }

  Timer();
  return 0;
}
