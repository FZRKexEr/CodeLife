//
//  g2.cpp
//  2022-05-03 18:51
//
//  Created by liznb
//  

#ifdef ONLINE_JUDGE
#ifndef LOCAL_TEST
#pragma GCC optimize("O3","unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif
#endif

#include <string>
#include <bits/functexcept.h>
#include <iosfwd>
#include <bits/cxxabi_forced.h>
#include <bits/functional_hash.h>


#pragma push_macro("__SIZEOF_LONG__")
#pragma push_macro("__cplusplus")
#define __SIZEOF_LONG__ __SIZEOF_LONG_LONG__
#define unsigned unsigned long
#define __cplusplus 201102L

#define __builtin_popcountl __builtin_popcountll
#define __builtin_ctzl __builtin_ctzll

#include <bitset>

#pragma pop_macro("__cplusplus")
#pragma pop_macro("__SIZEOF_LONG__")
#undef unsigned
#undef __builtin_popcountl
#undef __builtin_ctzl


#include <bits/stdc++.h>


#define int long long
#define endl '\n'
using namespace std;

void file() {
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
#endif
}


signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);

  const int N = 2e5 + 10;
  bitset<N> colo[101];

  int n; cin >> n; 
//  for (int i = 1; i <= 100; i++) colo[i].reset();
  for (int i = 1; i <= n; i++) {
    int val; cin >> val;
    colo[val][i] = 1;    
  }
  int m; cin >> m;

  // 得到一个只在 [l, r] 为 1 的 bitset<N>
  auto get = [&] (bitset<N> &temp, int l, int r) {
    temp.set();
    temp <<= N - 1 - r; 
    temp >>= N - 1 - r;
    temp >>= l;
    temp <<= l; 
  };
  

  for (int i = 1; i <= m; i++) {
    int l, r, x, y; cin >> l >> r >> x >> y;
    bitset<N> temp; 
    if (x == y) continue;
    get(temp, l, r); 
    colo[y] |= colo[x] & temp;
    colo[x] &= (~temp); 
  } 

  vector<int> ans(n + 1);

  for (int i = 1; i <= 100; i++) {
    for (int j = colo[i]._Find_first(); j != N; j = colo[i]._Find_next(j)) {
      ans[j] = i;
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " ";
  }
  return 0;
}
