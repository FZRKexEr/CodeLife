//
//  main.cpp
//  2022-06-05 13:51
//
//  Created by liznb
//  
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1ll << 31;
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
  vector<int> is, prinum, miu, sum;

  Mobius(int n) : is(n + 1, 0), miu(n + 1, 1), sum(n + 1, 0) {
    prinum.reserve(n + 1);
    for (int i = 2; i <= n; i++) {
      if (!is[i]) prinum.push_back(i), miu[i] = -1;  
      for (auto &it : prinum) {
        if (it * i > n) break;
        is[it * i] = 1;
        if (i % it == 0) {
          miu[it * i] = 0;
          break;
        } else {
          miu[it * i] = -1 * miu[i];
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      sum[i] = sum[i - 1] + miu[i];
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
  // 3. 如果 n 和 m 始终一样，可以记忆化。
  
  int g(int n, int m) {
    int limit = min(n, m);
    int ans = 0, nxt;
    for (int i = 1; i <= limit; i = nxt) {
      int nxtn = n / (n / i) + 1;
      int nxtm = m / (m / i) + 1;
      nxt = min({nxtn, nxtm, limit + 1});
      ans += (sum[nxt - 1] - sum[i - 1]) * (n / i) * (m / i);
    }
    return ans;
  }
  
};
const int N = 1e5 + 10;

long long sigma1[N];

long long power(long long a, long long b) {
    long long base = a, ans = 1ll;
    while(b) {
        if (b & 1) {
            ans *= base;
        }
        base *= base;
        b >>= 1;
    }
    return ans;
}

void Sigma1(int n, int *pri) {
    for (int i = 1; i <= n; i++) pri[i] = 0, sigma1[i] = 1ll;
    for (int i = 2; i <= n; i++) {
        if (pri[i]) continue;
        sigma1[i] = 1ll + i;
        for (int j = i * 2; j <= n; j += i) {
            int cnt = 0, val = j;
            while (val % i == 0) {
                cnt++; // k
                val /= i;
            }
            pri[j] = 1;//用快速幂！！！
            sigma1[j] *= 1ll * (power(i, cnt + 1) - 1) / (i - 1); // (p ^ {k + 1} - 1) / (p - 1)
            assert(sigma1[j] > 0);
        }
    }

}

int pri[N];


// 二元索引树, Binary Indexed Tree, Fenwick树, 树状数组
// 特性:
// 1. 只能处理具有前缀和性质数组。
// 2. 下标绝对不能为 0
struct BIT {
  vector<int> tree;
  int limit;
  BIT (int n) : tree(n + 1, 0), limit(n) {}

  inline int lowbit(int x) { return x & (-x); }

  void modify(int x, int val) { // 单点修改
    assert(x >= 1);
    while (x <= limit) {
      tree[x] += val;     
      tree[x] %= MOD;
      x += lowbit(x);
    }
  }

  int query(int x) {
    assert(x >= 0);
    int ans = 0;
    while (x) {
      ans += tree[x];
      ans %= MOD;
      x -= lowbit(x);
    }
    return ans;
  }

  int sum(int l, int r) {
    if (r < l) return 0;
    assert(l >= 1 && r >= 1);
    return (query(r) - query(l - 1) + MOD) % MOD; 
  }
};

signed main() {
  freopen("in.txt", "r", stdin);
  ios::sync_with_stdio(false); 
  cin.tie(0); 

  Sigma1(1e5, pri);
  Mobius T(1e5);

  int z; cin >> z;
  vector<array<int, 4>> a(z + 1, {0, 0, 0, 0});
  for (int i = 1; i <= z; i++) {
    cin >> a[i][2] >> a[i][3];
    cin >> a[i][0];
    a[i][1] = i;
  }
  sort(a.begin(), a.end());

  vector<array<int, 2>> add(1e5 + 1);
  for (int i = 1; i <= 1e5; i++) {
    add[i] = {sigma1[i], i};
  }
  sort(add.begin() + 1, add.end());

  vector<int> ans(z + 1, 0);
  const int INF = 0x3f3f3f3f;
  BIT Tree(1e5);

  for (int i = 1; i <= z; i++) {
    auto [limit, ord, n, m] = a[i];
    int l = upper_bound(add.begin() + 1, add.end(),(array<int, 2>){a[i - 1][0], INF}) - add.begin();
    int r = upper_bound(add.begin() + 1, add.end(), (array<int, 2>){a[i][0], INF}) - add.begin() - 1;
    while (l <= r) {
      int d = add[l][1];       
      for (int j = 1; j * d <= 1e5; j++) {
        Tree.modify(j * d, sigma1[d] * T.miu[j] % MOD);    
      }
      l++;
    }
    for (int t = 1, nxt; t <= min(n, m); t = nxt) {
      int nxtn = n / (n / t) + 1;
      int nxtm = m / (m / t) + 1;
      nxt = min(nxtn, nxtm);
      int l = t, r = nxt - 1;
      ans[ord] += (n / t) * (m / t) % MOD * Tree.sum(l, r) % MOD; 
      ans[ord] %= MOD;
    }
  }
  for (int i = 1; i <= z; i++) cout << ans[i] << endl;
  

  return 0;
}
