//
//  b.cpp
//  2022-05-04 10:03
//
//  Created by liznb
//  

#include <bits/stdc++.h>
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

#define getchar() (frS==frT&&(frT=(frS=frBB)+fread(frBB,1,1<<15,stdin),frS==frT)?EOF:*frS++)char frBB[1<<15],*frS=frBB,*frT=frBB;template<typename T>inline void read(T &x){    x=0;char c=getchar();    while(!isdigit(c))c=getchar();    while(isdigit(c)){x=x*10+c-'0';c=getchar();}}/*1. 使用 read(x) 读入一个非负整数x2. 由于 fread 方法特性，本地测试时需要从文件读入，或者注释掉前两行，在提交时取消注释。*/


const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
int a[N];
struct ST_table {
    array<int, 2> st[N][25];
    int Log[N];
    
    void Init(int n) {
        Log[1] = 0; // 以2为底
        for (int i = 2; i <= n; i++) {
            Log[i] = Log[i / 2] + 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; (1 << j) <= i; j++) {

              auto a = st[i][j - 1]; 
              auto b = st[i - (1 << (j - 1))][j - 1];
              set<int> temp;
              temp.insert(a[0]);
              temp.insert(a[1]);
              temp.insert(b[0]);
              temp.insert(b[1]);
              auto it = temp.begin();
              auto it2 = it;
              it2++;
              st[i][j] = {*it, *it2};
            }
        }
    }

    void build(int n) {
        for (int i = 1; i <= n; i++) {
          st[i][0][0] = a[i];
          st[i][0][1] = INF;
        }
        Init(n);
    }
    
    array<int, 2> query(int l, int r) {
        int len = Log[r - l + 1];
        auto a = st[r][len]; 
        auto b = st[l + (1 << len) - 1][len];
        set<int> temp;
        temp.insert(a[0]);
        temp.insert(a[1]);
        temp.insert(b[0]);
        temp.insert(b[1]);
        auto it = temp.begin();
        auto it2 = it;
        it2++;
        array<int, 2> ans = {*it, *it2};
        return ans;
    }
} T;

signed main() {
  file();
  int n, m;  
  read(n);
  read(m);
  for (int i = 1; i <= n; i++) {
    read(a[i + 1]);
  }
  a[1] = n;
  a[n + 2] = n + 1;
  n = n + 2;
  T.build(n);

  for (int i = 1; i <= m; i++) {
    int l, r;     
    read(l);
    read(r);
    l++, r++;

    array<int, 2> a = T.query(1, l - 1); 
    array<int, 2> b = T.query(r + 1, n);
    set<int> temp;
    temp.insert(a[0]);
    temp.insert(a[1]);
    temp.insert(b[0]);
    temp.insert(b[1]);
    auto it = temp.begin();
    it++;
    
    cout << (*it) << endl;
  }
   
   
  return 0;
}
