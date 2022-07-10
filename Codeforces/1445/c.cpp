//
//  c.cpp
//  2022-07-07 22:22
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

// Pollard_Rho 算法
// 期望复杂度 O(n ^ 0.25)
// 来自 Rockdu

namespace NT {
  long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
  }
  long long mul(long long a, long long b, long long m) {
    long long s = a * b - (long long)((long double)a * b / m + 0.5) * m;
    return s < 0 ? s + m : s;
  }
  long long fpow(long long x, long long a, long long m) {
    long long ans = 1;
    while(a) {
      if(a & 1) ans = mul(ans, x, m);
      x = mul(x, x, m), a >>= 1;
    }
    return ans;
  }
}

namespace Miller_Rabin {
  using namespace NT;
  long long p[15] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  int detect(long n, long long a) {
    if(n == a) return 1;
    if(a % n == 0) return 1;
    long long now = n - 1, lst = 1;
    if(fpow(a, now, n) != 1) 
      return 0;
    while(!(now & 1)) {
      now /= 2;
      long long p = fpow(a, now, n);
      if(lst == 1 && p != 1 && p != n - 1)
        return 0;
      lst = p;
    }
    return 1;
  }
  
  long long MR(long long n) {
    if(n < 2) return 0;
    for(int i = 0; i < 7; ++i) {
      if(!detect(n, p[i])) 
        return 0;
    }
    return 1;
  }
}

namespace Pollard_Rho {
  using namespace NT;
  using namespace Miller_Rabin;
  long long f(long long x, long long C, long long p) {
    return (mul(x, x, p) + C) % p;
  }
  long long Rand() {return (rand() << 15) + rand();}
  long long Randll() {return (Rand() << 31) + Rand();}
  
  long long PR(long long n) {
    if(n == 4) return 2;
    if(MR(n)) return n;
    while(1) {
      long long C = Randll() % (n - 1) + 1;
      long long s = 0, t = 0;
      long long acc = 1;
      do {
        for(int i = 1; i <= 128; ++i) {
          t = f(f(t, C, n), C, n);
          s = f(s, C, n);
          long long tmp = mul(acc, abs(t - s), n);
          if(s == t || tmp == 0)
            break;
          acc = tmp;
        }
        long long d = gcd(n, acc);
        if(d > 1) return d;
      } while(s != t);
    }
  }
  
  // 返回的 first 是质因子, second 是质因子个数, 从小到大排序。
  typedef pair<long long, int > pii;
  vector<pii> DCOMP(long long n) {
    vector<pii> ret;
    while(n != 1) {
      long long p = PR(n);
      while(!MR(p)) 
        p = PR(p);
      int c = 0;
      while(n % p == 0) n /= p, ++c;
      ret.push_back(make_pair(p, c));
    }
    sort(ret.begin(), ret.end());
    return ret;
  }
}
signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  
  int z; cin >> z; 
  while (z--) {
    int p, q; cin >> p >> q;
    if (p % q) cout << p << endl;  
    else {
      auto res = Pollard_Rho::DCOMP(q);      
      int ans = 0;
      for (auto &it : res) {
        int val = p;   
        while (val % it.first == 0) val /= it.first;
        for (int i = 1; i < it.second; i++) val *= it.first;
        ans = max(ans, val);
      }
      cout << ans << endl;
    }
  }

  Timer();
  return 0;
}
