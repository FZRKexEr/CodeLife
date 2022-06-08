#include <bits/stdc++.h>

using namespace std;

#define pb emplace_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define pii pair<int, int>
#define puu pair<unsigned, unsigned>
#define ll long long
#define mp make_pair
#define ui unsigned
#define ull unsigned long long
#define ld double
#define pld pair<ld, ld>
#define pll pair<ll, ll>

const int INF = 1e9 + 1;
const ll INFLL = 1e18;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &c : a) cin >> c;
    map<int, int> cnt;
    for (auto &c : a) cnt[c]++;
    set<pii> s1, s2;
    int sum1 = 0;
    for (auto &c : cnt) s2.insert(mp(c.se, c.fi));
    int ans = INF;
    int skip = 0;
    for (int x = 0; x <= n; x++) {
        if (s1.find(mp(cnt[x - 1], x - 1)) != s1.end()) {
            sum1 -= cnt[x - 1];
            s1.erase(mp(cnt[x - 1], x - 1));
        }
        if (s2.find(mp(cnt[x - 1], x - 1)) != s2.end()) {
            s2.erase(mp(cnt[x - 1], x - 1));
        }
        while (s2.size() && sum1 + s2.begin()->fi <= k) {
            s1.insert(*s2.begin());
            sum1 += s2.begin()->fi;
            s2.erase(s2.begin());
        }
        if (k < skip) break;
        int now = x + s2.size();
        if (x == 0) {
            now = max(1, (int)s2.size());
        }
        ans = min(ans, now - x);
        if (cnt[x] == 0) skip++;
    }
    cout << ans << "\n";
}

int main() {
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
    #endif
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
