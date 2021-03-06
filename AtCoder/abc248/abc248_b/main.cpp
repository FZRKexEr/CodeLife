#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#define REP(i, n) for (int i = 0; (i) < (int)(n); ++ (i))
#define REP3(i, m, n) for (int i = (m); (i) < (int)(n); ++ (i))
#define REP_R(i, n) for (int i = (int)(n) - 1; (i) >= 0; -- (i))
#define REP3R(i, m, n) for (int i = (int)(n) - 1; (i) >= (int)(m); -- (i))
#define ALL(x) ::std::begin(x), ::std::end(x)
using namespace std;


int64_t solve(int64_t A, int64_t B, int64_t K) {
  long long ans = 0;
  while (A < B) {
    ans++;
    A = A * K;
  }
  return ans;
}

// generated by oj-template v4.8.1 (https://github.com/online-judge-tools/template-generator)
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t A, B, K;
    std::cin >> A >> B >> K;
    auto ans = solve(A, B, K);
    std::cout << ans << '\n';
    return 0;
}
