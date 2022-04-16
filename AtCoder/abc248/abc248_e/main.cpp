//
//  main.cpp
//  2022-04-16 20:51
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define LOCAL
using namespace std;

#ifdef ONLINE_JUDGE
#ifndef LOCAL_TEST
#pragma GCC optimize("O3","unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif
#endif

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

random_device rd; // 使用硬件熵源的随机数生成器
mt19937 seed(rd());
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

struct Node {
    int x, y;
};

struct Frac {
    int x, y;
    // (y / x)
    /*
     1. 对斜率的保存很友好，可以处理斜率为0，斜率不存在的情况
     2. 可以求出与这一斜率垂直的斜率，包括斜率为0，和斜率不存在
     3. 可以自动读入两点，求斜率，无需再次特判
     4. 支持判重，不支持比较分数大小
     */

    long long gcd(long long a, long long b) {
        if (!b) return a;
        return gcd(b, a % b);
    }

    void calc() { // 规范分数表达式
        if (x == 0) {y = 1; return;}
        if (y == 0) {x = 1; return;}

        long long GCD = gcd(x, y);
        x /= GCD;
        y /= GCD;
        if (x < 0) y *= -1, x *= -1;
    }

    void in(Node a, Node b) { // 从node输入斜率
        x = a.x - b.x;
        y = a.y - b.y;
        calc();
    }

    Frac vertical() { // 求垂直的斜率
        Frac res = (Frac) {y, -1 * x};
        res.calc();
        return res;
    }

    bool operator < (const Frac & oth) const { // 只能用于判重（判重只能这样判！），不能比较分数大小
        if (x != oth.x) return x < oth.x;
        return y < oth.y;
    }
    
    bool operator == (const Frac & oth) const {
        if (x == oth.x && y == oth.y) return true;
        return false;
    }
};

struct Lines {
    Frac k; // 斜率，判断相交
    int a, b, c; // 一般式，用于判重

    long long gcd(long long a, long long b) {
        if (!b) return a;
        return gcd(b, a % b);
    }

    void in(Node u, Node v) {
        k.in(u, v);
        a = -k.y;
        b = k.x;
        c = -1 * a * u.x - b * u.y;
    }

    bool operator < (const Lines &oth) const { // 判重
        if (a != oth.a) return a < oth.a;
        if (b != oth.b) return b < oth.b;
        return c < oth.c;
    }

    bool operator == (const Lines &oth) const {
      if (!(k == oth.k)) return false;
      if (a != oth.a || b != oth.b || c != oth.c) return false;
      return true;
    }
};

Lines lines[300 * 300 + 10];
Node a[300 * 300 + 10];
signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, k; cin >> n >> k; 

  
  for (int i = 1; i <= n; i++) {
    cin >> a[i - 1].x >> a[i - 1].y;
  }
  if (k == 1) {
    cout << "Infinity" << endl;
    return 0;
  }
  int tot = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      Lines res; res.in(a[i], a[j]);
      lines[tot++] = res;
    }
  }
  sort(lines, lines + tot);
  tot = unique(lines, lines + tot) - lines;
  vector<int> cnt(tot); 

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < tot; j++) {
      auto it = lines[j];
      if (it.a * a[i].x + it.b * a[i].y + it.c == 0) {
        cnt[j]++; 
      }
    }
  }
  int ans = 0; 
  for (int i = 0; i < tot; i++) {
    if (cnt[i] >= k) ans++;
  }
  cout << ans << endl;
  return 0;
}
