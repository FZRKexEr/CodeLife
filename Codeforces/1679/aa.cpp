//
//  aa.cpp
//  2022-05-19 15:20
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

// 用线段辅助理解
// ------------
// --------------------

// gcd 性质：
// 1. gcd(a, b) 是 ax + by 能得到的最小的正整数
// 2. 在 ax + by = c 中，如果 c 不是 gcd(a, b) 的倍数，则无解
// 3. gcd(a, b) = gcd(b, a % b)

// 功能说明：
// ax + by = c
// 1. 求出 x > 0, y > 0 解的数量
// 2. 求出 x > 0, y > 0 解中 x 的最大值，y 的最大值
//
// 注意:
// 1. g = -1 说明无解
// 2. dx, dy 大于 0
// 3. 必须用 long long，值域极限是 max(a, b) * c

struct GCD {
  int a, b, c, g;
  int x, y, dx, dy; // dx 和 dy 是一次移动最小的距离，dx, dy > 0

  void exgcd(int a, int b, int &d, int &x, int &y) {
    if (!b) {
      d = a; x = 1; y = 0;
    } else {
      exgcd(b, a % b, d, y, x); y -= x * (a / b); // 注意括号！
    }
  }

  GCD(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {
    exgcd(a, b, g, x, y);
    if (c % g != 0) {
      g = -1;
      dx = dy = 0;
    } else {
      x *= c / g;
      y *= c / g;
      dx = abs(b / g);
      dy = abs(a / g);
    }
  }
  
  // 从 s 移动到超过 t 每次移动 d，需要的次数
  // s, t, d 可正可负 d 不能为 0
  int cnt(int s, int t, int d) {
    if (d < 0) d *= -1, swap(s, t);
    if (s < t) {
      if ((t - s) % d == 0) return (t - s) / d;
      return (t - s) / d + 1;
    } else {
      if ((t - s) % d == 0) return (t - s) / d;
      return (t - s) / d - 1;
    }
  }
    
  // 把 x 移动到最小正整数
  void move_x() {
    if (x > 0) {
      int cntx = cnt(x, 0, -dx);
      cntx--;
      x -= cntx * dx;
      y += cntx * dy;
    } else {
      int cntx = cnt(x, 1, dx);
      x += cntx * dx;
      y -= cntx * dy; 
    }
  }

  // 把 y 移动到最小正整数
  void move_y() {
    if (y > 0) {
      int cnty = cnt(y, 0, -dy);
      cnty--;
      y -= cnty * dy;
      x += cnty * dx;
    } else {
      int cnty = cnt(y, 1, dy);
      y += cnty * dy;
      x -= cnty * dx;
    }
  }
  
  // x > 0 并且 y > 0 的解的数量
  int count() { 
    move_x();   
    if (y <= 0) return 0; 
    int cnty = cnt(y, 0, -dy); 
    return cnty;
  }
   
};


signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z;  
  while (z--) {
    int n; cin >> n;
    // 4x + 6y = n
    GCD T(4, 6, n);
    if (T.g == -1) {
      cout << -1 << endl;
    } else {
      T.move_y();
      if (T.y - T.dy == 0) {
        T.y -= T.dy;
        T.x += T.dx;
      }
      int flag = true;
      if (T.x < 0 || T.y < 0) flag = false;
      int x = T.x + T.y;
      T.move_x();
      if (T.x - T.dx == 0) {
        T.x -= T.dx;
        T.y += T.dy;
      }
      if (T.x < 0 || T.y < 0) flag = false;
      int y = T.y + T.x;
      if (flag) cout << y << " " << x << endl;
      else cout << -1 << endl;
    }
  }
   
  return 0;
}
