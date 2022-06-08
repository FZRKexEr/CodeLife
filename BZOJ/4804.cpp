//
//  4804.cpp
//  2022-06-05 19:07
//
//  Created by liznb
//  

#include <bits/stdc++.h>
//#define int long long
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

// 莫比乌斯反演:
// 注意: 一定打开 #define int long long
//
// 两个公式: 
// 1. f(n) = sigma{u(d) * F(n / d)} (d|n)
// 2. f(n) = sigma{u(d / n) * F(d)} (n|d)
//
// 莫比乌斯反演题特点：
// 1. F(n) 要能快速求出来，并且最好是用除法 O(1) 求，这样才能对F(n)用整除分块
// 2. 一般和 GCD，约数有关。 
// 3. 要先构造出合理的 F(n) 和 f(n)
//
// 经典构造:
// 求 gcd(i, j) = k 的对数，其中 i <= n, j <= m
// 设 f(k) 是答案。F(k) 是 i <= n, j <= m 中 k | gcd(i, j) 的对数。
// 显然 F(k) = (n / k) * (m / k) = sigma{f(d)} (k | d);
// 所以 f(k) = sigma{u(d / k) * (n / d) * (m / d)} (k | d);
// 进一步转换，gcd(i, j) = k 与 gcd(i / k, j / k) = 1 等价。
// 所以只需要每次求 f(1), 但 n / k 和 m / k 不同的情况。用整除分块优化成 sqrt(min(n / k, m / k))
//
// 整除分块:
// i 从小到大, n / i 不相等的下一个 i 是 n / (n / i) + 1

struct Mobius {
  vector<int> is, prinum, miu;
  vector<long long> phi;
  vector<long long> vis;

  Mobius(int n) : is(n + 1, 0), miu(n + 1, 1) {
    vis.resize(n + 1, 0);
    prinum.reserve(n + 1);
    phi.resize(n + 1, 0);
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
      if (!is[i]) prinum.push_back(i), miu[i] = -1, phi[i] = i - 1;  
      for (auto &it : prinum) {
        if (it * i > n) break;
        is[it * i] = 1;
        if (i % it == 0) {
          miu[it * i] = 0;
          phi[it * i] = 1ll * it * phi[i];
          break;
        } else {
          phi[it * i] = 1ll * (it - 1) * phi[i];
          miu[it * i] = -1 * miu[i];
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      miu[i] = miu[i - 1] + miu[i];
    }
    for (int i = 1; i <= n; i++) {
      phi[i] = phi[i - 1] + phi[i];
    }
  }

  // gcd(i, j) = k (1 <= i <= n,  1 <= j <= m) 的对数
  // 复杂度 
  // 1. sqrt(min(n / k, m / k)) 单次
  // 2. 如果求 k 从 1 到 t, 复杂度低于 tlogt 
  //
  // 进一步优化策略:
  // 1. 如果 k 从 1 到 t: 外层循环可以再套一个整除分块，因为g函数里开头做了除法。
  // 2. 如果 k 是 质数: 用埃筛把每一个质数的倍数处的 miu 函数贡献累计一下(不再使用整除分块)。复杂度 O(n + nloglogn)
  // 3. 如果 n 和 m 始终一样，可以记忆化 g 函数的结果。
  long long g(int n, int m) {
    if (vis[n]) return vis[n];

    int limit = min(n, m);
    long long ans = 0, nxt;
    for (int i = 1; i <= limit; i = nxt) {
      int nxtn = n / (n / i) + 1;
      int nxtm = m / (m / i) + 1;
      nxt = min({nxtn, nxtm, limit + 1});
      ans += 1ll * (miu[nxt - 1] - miu[i - 1]) * (n / i) * (m / i);
    }
    return vis[n] = ans;
  }
  
};

signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z;  

  Mobius T(1e7);

  while (z--) {
    int n; cin >> n;
    long long ans = 0;
    for (int i = 1; i <= n; i = n / (n / i) + 1) {
      int l = i, r = n / (n / i); 
      ans += 1ll * (T.phi[r] - T.phi[l - 1]) * T.g(n / i, n / i);  
    }
    cout << ans << endl;
  }
  return 0;
}
