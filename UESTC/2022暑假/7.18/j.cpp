//
//  j.cpp
//  2022-07-18 12:39
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;


//#define LOCAL
#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
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


signed main() {
 // file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int z; cin >> z; 
  int tot = 0;

  while (z--) {
    int n; cin >> n; 
//    debug(n);
    vector<vector<int>> G(n + 1);
    vector<int> degree(n + 1, 0);
    
    vector<array<int, 2>> choose; 

    mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> U(1, 1e9);

    for (int i = 1; i <= n; i++) {
      int k; cin >> k;
      for (int j = 1; j <= k; j++) {
        int u; cin >> u;      
        G[u].push_back(i); 
        degree[i]++;
      }
      choose.push_back({U(rng), i});
    }

    sort(choose.begin(), choose.end());
    
    vector<int> vis(n + 1, 0);

    int count = 0;
    auto topo = [&] (queue<int> que) {
      vector<int> add;
      int res = 0;

      int st = que.front();
      
      while (!que.empty()) {
        int x = que.front();
        vis[x]++;
        res++;
        que.pop();
        for (auto &v : G[x]) {
          if (v == st) continue;
          degree[v]--;
          add.push_back(v);
          if ((int) degree[v] == 0) {
            que.push(v);
          }
        }
      }
      count += res;
      for (auto &it : add) degree[it]++;
      return res;
    };

    int ans = 0;
    int cnt = 0;
    for (int i = 0; i < (int) choose.size(); i++) {
      int pos = choose[i][1];
      if (vis[pos]) continue;
      cnt++;
      queue<int> que; que.push(pos);
      auto res = topo(que);
      ans = max(ans, res); 
    }
    cout << "Case #" << ++tot << ": " << ans << endl;
//    debug(count, cnt);
  }
  //Timer();
  return 0;
}
