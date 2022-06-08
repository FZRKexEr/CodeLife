//
//  d.cpp
//  2022-05-26 02:01
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

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z; 
  while (z--) {
    int a, b;
    array<int, 2> need; 
    cin >> a >> b;
    cin >> need[0] >> need[1];

    string s; cin >> s;
    int cnt_a = 0, cnt_b = 0;

    for (auto &it : s) {
      if (it == 'A') cnt_a++;
      else cnt_b++;
    }
    if (cnt_a - need[0] - need[1] != a) {
      cout << "NO" << endl;
      continue;
    }
    if (cnt_b - need[0] - need[1] != b) {
      cout << "NO" << endl;
      continue;
    }

    int p = 0; 
    vector<int> arr[3];
    arr[0].clear(); arr[1].clear(); arr[2].clear();

    while (p < (int) s.length() - 1) {
      if (s[p + 1] == s[p]) {
        p++;
        continue;
      }
      int cnt = 0;
      for (int i = p + 2; i < (int) s.length() - 1; i += 2) {
        if (s[i] == s[p] && s[i + 1] == s[p + 1]) {
          cnt++;
        } else break;
      }
      int flag = false; 
      if (p + (cnt + 1) * 2 < (int) s.length() && s[p + (cnt + 1) * 2] == s[p]) flag = true;

      if (flag) {
        p = p + (cnt + 1) * 2 + 1;
        arr[2].push_back(cnt + 1);
        continue;
      }

      if (s[p] == 'A' && s[p + 1] == 'B') arr[0].push_back(cnt + 1);
      else arr[1].push_back(cnt + 1);
      p = p + (cnt + 1) * 2;
    }
    array<int, 3> tot = {0, 0, 0};
    for (int i = 0; i <= 2; i++) {
      sort(arr[i].begin(), arr[i].end());
      for (auto &it : arr[i]) tot[i] += it;
    }
    
    if (tot[0] < need[0] && tot[1] < need[1]) {
      int val = need[0] - tot[0] + need[1] - tot[1];      
      if (val <= tot[2]) cout << "YES" << endl;
      else cout << "NO" << endl;
    } else if (tot[0] >= need[0] && tot[1] < need[1]) {
      tot[1] += tot[2]; 
      if (tot[1] >= need[1]) {
        cout << "YES" << endl;
      } else {
        swap(arr[0], arr[1]);           
        swap(tot[0], tot[1]);
        swap(need[0], need[1]);
        int re = need[0] - tot[0];
        assert(re > 0);
        for (int i = (int) arr[1].size() - 1; i >= 0; i--) {
          int val = arr[1][i];
          if (val - 1 >= re) {
            tot[1] -= re + 1;
            re = 0;      
            break;
          } else {
            re -= (val - 1); 
            tot[1] -= val;
          }
        }
        if (re != 0 || tot[1] < need[1]) {
          cout << "NO" << endl;
        } else {
          cout << "YES" << endl;
        }
      }
    } else if (tot[0] < need[0] && tot[1] >= need[1]) {
      tot[0] += tot[2];
      if (tot[0] >= need[0]) {
        cout << "YES" << endl;
      } else {
        int re = need[0] - tot[0];
        assert(re > 0);
        for (int i = (int) arr[1].size() - 1; i >= 0; i--) {
          int val = arr[1][i];
          if (val - 1 >= re) {
            tot[1] -= re + 1;
            re = 0;      
            break;
          } else {
            re -= (val - 1); 
            tot[1] -= val;
          }
        }
        if (re != 0 || tot[1] < need[1]) {
          cout << "NO" << endl;
        } else {
          cout << "YES" << endl;
        }
      }
    } else if (tot[0] >= need[0] && tot[1] >= need[1]) {
      cout << "YES" << endl;
    }
 }
   
  return 0;
}
