#include <algorithm>
#include <cstdio>

long long dp[32][32];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d %d", &n, &m);
    --n;
    --m;
    dp[0][0] = 0;
    for (int i = 0; i < 32; ++i) {
      for (int j = 0; j < 32; ++j) {
        if (i | j) {
          dp[i][j] = 1ll << 62;
        }
        if (i) {
          dp[i][j] = std::min(
              dp[i][j], dp[i - 1][j] | ((n >> (i - 1) & 1ll) << (i + j - 1)));
        }
        if (j) {
          dp[i][j] = std::min(
              dp[i][j], dp[i][j - 1] | ((m >> (j - 1) & 1ll) << (i + j - 1)));
        }
      }
    }
    printf("%lld\n", dp[31][31]);
  }
  return 0;
}
