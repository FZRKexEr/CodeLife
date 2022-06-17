//
//  井字棋.cpp
//  2022-06-10 10:42
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

int START_TIME = -1;
void file() {
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
  START_TIME = clock(); 
#endif
}

void Timer() {
#ifndef ONLINE_JUDGE
  if (START_TIME != -1)
    cout << endl << 1.0 * (clock() - START_TIME) / CLOCKS_PER_SEC << "s";
#endif
}

int cnt = 0;
struct Board {
  vector<vector<int>> board;  
  int number;
  
  Board() {
    number = 0;
    board.resize(3, vector<int> (3, -1));
  }

  int evaluate() {
    assert(number == 9);
    auto rotate = [&] () {
      auto temp = board;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          cnt++;
          board[i][j] = temp[j][3 - i - 1];  
        }
      }
    };
    auto check_line = [&] () {
      int val = 0;
      for (int i = 0; i < 3; i++) {
        int cnt_0 = 0, cnt_1 = 0;
        for (int j = 0; j < 3; j++) {
          cnt++;
          if (board[i][j] == 0) cnt_0++; 
          if (board[i][j] == 1) cnt_1++; 
        }
        if (cnt_0 == 3) val += 1; // guapi
        if (cnt_1 == 3) val -= 1; // name
      }
      return val;
    };
    auto check_diagonal = [&] () {
      int cnt_0 = 0, cnt_1 = 0;
      for (int i = 0; i < 3; i++) {
        cnt++;
        if (board[i][i] == 0) cnt_0++;
        if (board[i][i] == 1) cnt_1++;
      }
      if (cnt_0 == 3) return 1;
      if (cnt_1 == 3) return -1;
      return 0;
    };
    int ans = 0;
    ans += check_line();
    ans += check_diagonal();
    rotate();
    ans += check_line();
    ans += check_diagonal();
    rotate(), rotate(), rotate();
    return ans;
  }
};

signed main() {
 // file();
  ios::sync_with_stdio(false); 
  cin.tie(0);

  int z; cin >> z;

  map<vector<vector<int>>, int> vis[2], value[2];
  while (z--) {
    int o; cin >> o; o ^= 1;
    Board T;
    for (int i = 0; i < 3; i++) {
      string s; cin >> s;
      for (int j = 0; j < 3; j++) {
        if (s[j] == '.') T.board[i][j] = -1;
        if (s[j] == 'O') T.board[i][j] = 0, T.number++;
        if (s[j] == 'X') T.board[i][j] = 1, T.number++;
      }
    }
    // 0 guapi, 1 name
    function<int(Board&, int)> dfs = [&] (Board &sta, int o) {
      if (vis[o][sta.board]) return value[o][sta.board];
      vis[o][sta.board] = 1;
      if (sta.number == 9) return value[o][sta.board] = sta.evaluate();
      array<int, 3> goal = {o ? 0x3f3f3f3f : -0x3f3f3f3f, 0, 0};
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          cnt++;
          if (sta.board[i][j] == -1) {
            sta.board[i][j] = o;
            sta.number++;
            if (o == 0) goal = max(goal, (array<int, 3>) {dfs(sta, o ^ 1), i, j});
            if (o == 1) goal = min(goal, (array<int, 3>) {dfs(sta, o ^ 1), i, j});
            sta.board[i][j] = -1;
            sta.number--;
          }
        }
      }
      return value[o][sta.board] = goal[0];
    };
    cout << dfs(T, o) << endl;
  }
  
  Timer();
  return 0;
}
